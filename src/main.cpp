/**
 * @file main.cpp
 * @brief Butano GBA Story Engine Logic
 * 
 * This file handles the main game loop, real-time waiting mechanics,
 * and story node transitions for a GBA visual novel.
 */

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_time.h"
#include "game_state.h"
#include "ui_text.h"
#include "log.h"
#include "story.h"
#include "utils.h"
#include "../external/butano/common/include/common_fixed_8x8_sprite_font.h"

namespace {
    constexpr int MAX_SPRITES = 128;
    int global_frame = 0;
}

/**
 * @brief Formats current time into a HH:MM string.
 */
static bn::string<8> get_time_string() {
    bn::optional<bn::time> t = bn::time::current();
    if (!t) {
        return "00:00";
    }

    bn::string<8> out;
    if (t->hour() < 10) out += "0";
    out += bn::to_string<2>(t->hour());
    out += ":";
    
    if (t->minute() < 10) out += "0";
    out += bn::to_string<2>(t->minute());
    
    return out;
}

// -----------------------------------------------------------------------------
// WAITING MECHANICS
// -----------------------------------------------------------------------------

/**
 * @brief Calculates remaining seconds for real-time wait logic.
 */
static int get_remaining_seconds(const SaveData& state) {
    if (!state.real_time_mode || !state.waiting) {
        return 0;
    }

    bn::optional<bn::time> t = bn::time::current();
    if (!t) return 0;

    int now_sec = t->hour() * 3600 + t->minute() * 60 + t->second();

    if (!state.wait_wrap) {
        return (now_sec >= state.wait_end_seconds) ? 0 : (state.wait_end_seconds - now_sec);
    }

    if (now_sec < state.wait_end_seconds) {
        return state.wait_end_seconds - now_sec;
    }

    return (86400 - now_sec) + state.wait_end_seconds;
}

/**
 * @brief Starts a real-time waiting period.
 */
static void start_wait(SaveData& state, int seconds) {
    if (!state.real_time_mode) {
        state.waiting = false;
        return;
    }

    bn::optional<bn::time> t = bn::time::current();
    if (!t) return;

    int now_sec = t->hour() * 3600 + t->minute() * 60 + t->second();
    int total = now_sec + seconds;

    state.wait_wrap = false;
    if (total >= 86400) {
        total -= 86400;
        state.wait_wrap = true;
    }

    state.wait_end_seconds = total;
    state.waiting = true;
}

/**
 * @brief Checks if a waiting period has concluded.
 */
static bool is_wait_done(const SaveData& state) {
    if (!state.real_time_mode) {
        return true;
    }

    bn::optional<bn::time> t = bn::time::current();
    if (!t) return true;

    int now_sec = t->hour() * 3600 + t->minute() * 60 + t->second();

    if (!state.wait_wrap) {
        return now_sec >= state.wait_end_seconds;
    }

    return now_sec < state.wait_end_seconds;
}

// -----------------------------------------------------------------------------
// MAIN GAME LOOP
// -----------------------------------------------------------------------------

int main() {
    bn::core::init();

    bn::sprite_text_generator tg(common::fixed_8x8_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> sprites;

    // Load initial state
    SaveData state = load_save();
    if (!state.valid) {
        state = SaveData();
        state.valid = true;
    }

    bool in_title = true;
    bool in_log = false;
    bool continue_game = false;
    int visible_chars = 0;
    int tick_counter = 0;
    bool is_text_finished = false;
    int log_scroll_index = 0;
    const Node* current_node = nullptr;

    while (true) {
        sprites.clear();
        tg.set_left_alignment();
        current_node = &nodes[state.current_node];

        // --- HUD Overlay ---
        {
            bn::string<32> hud_text;
            hud_text = state.real_time_mode ? "RT " : "QP ";
            hud_text += get_time_string();
            
            tg.set_right_alignment();
            tg.generate(110, -72, hud_text, sprites);
            tg.set_left_alignment();
        }

        // --- Background Processing ---
        if (state.waiting && is_wait_done(state)) {
            state.waiting = false;
            save_game(state);
        }

        // --- State: Title Screen ---
        if (in_title) {
            render_title(state.real_time_mode, tg, sprites);

            // Continue current progress
            if (bn::keypad::a_pressed() && state.valid) {
                continue_game = true;
                in_title = false;
            }

            // Start new game
            if (bn::keypad::b_pressed()) {
                state.current_node = 0;
                state.history_count = 0;
                state.waiting = false;
                continue_game = true;
                in_title = false;
                save_game(state);
            }

            // Debug/Mode toggle
            if (bn::keypad::l_held() && bn::keypad::r_pressed()) {
                state.real_time_mode = !state.real_time_mode;
                save_game(state);
            }
        }
        // --- State: History Log ---
        else if (in_log) {
            render_log(tg, sprites, log_scroll_index);
            update_log(in_log, in_title, log_scroll_index);
        }
        // --- State: Active Gameplay ---
        else {
            if (continue_game) {
                visible_chars = 0;
                tick_counter = 0;
                is_text_finished = false;
                continue_game = false;
            }

            // --- Text Progressive Reveal ---
            if (!is_text_finished) {
                tick_counter++;
                if (tick_counter > 1) {
                    tick_counter = 0;
                    visible_chars++;

                    int total_node_len = 0;
                    for (int i = 0; i < current_node->line_count; ++i) {
                        total_node_len += strlen(current_node->lines[i]);
                    }

                    if (visible_chars >= total_node_len + current_node->line_count) {
                        is_text_finished = true;
                        
                        // Push to persistent log
                        bn::vector<bn::string<48>, MAX_LOG_LINES> log_lines;
                        for (int i = 0; i < current_node->line_count; ++i) {
                            log_lines.push_back(current_node->lines[i]);
                        }
                        log_message(current_node->speaker, log_lines, get_time_string().c_str(), false);
                    }
                }
            }

            render_node(*current_node, visible_chars, is_text_finished, tg, sprites);

            // --- Story Input Handling ---
            if (bn::keypad::select_pressed()) {
                in_log = true;
                log_scroll_index = 0;
            }

            if (bn::keypad::start_pressed()) {
                in_title = true;
                in_log = false;
            }

            // Choice A
            if (bn::keypad::a_pressed() && is_text_finished && !current_node->ending) {
                state.history[state.history_count++] = state.current_node;
                log_choice(current_node->option_a, get_time_string().c_str());
                
                state.current_node = current_node->next_a;
                if (current_node->wait_a) {
                    start_wait(state, current_node->wait_seconds);
                }
                
                visible_chars = 0;
                is_text_finished = false;
                save_game(state);
            }

            // Choice B
            if (bn::keypad::b_pressed() && is_text_finished && !current_node->ending) {
                state.history[state.history_count++] = state.current_node;
                log_choice(current_node->option_b, get_time_string().c_str());
                
                state.current_node = current_node->next_b;
                visible_chars = 0;
                is_text_finished = false;
                save_game(state);
            }
        }

        global_frame++;
        bn::core::update();
    }
}
