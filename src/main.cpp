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
}

static int get_current_seconds()
{
    bn::optional<bn::time> t = bn::time::current();
    if(!t) return 0;
    return (t->hour() * 3600) + (t->minute() * 60) + t->second();
}

static bn::string<8> get_time_string()
{
    bn::optional<bn::time> t = bn::time::current();
    if(!t) return "00:00";

    bn::string<8> out;

    if(t->hour() < 10) out += "0";
    out += bn::to_string<2>(t->hour());
    out += ":";

    if(t->minute() < 10) out += "0";
    out += bn::to_string<2>(t->minute());

    return out;
}

static void start_wait(SaveData& state, int seconds)
{
    if(!state.real_time_mode)
    {
        state.waiting = false;
        state.wait_end_seconds = 0;
        state.wait_wrap = false;
        return;
    }

    int now = get_current_seconds();
    int target = now + seconds;

    state.wait_wrap = false;

    if(target >= 86400)
    {
        target -= 86400;
        state.wait_wrap = true;
    }

    state.wait_end_seconds = target;
    state.waiting = true;
}

static bool is_wait_done(const SaveData& state)
{
    if(!state.real_time_mode) return true;
    if(!state.waiting) return true;

    int now = get_current_seconds();

    if(!state.wait_wrap)
    {
        return now >= state.wait_end_seconds;
    }

    return now < state.wait_end_seconds;
}

static int get_remaining_seconds(const SaveData& state)
{
    if(!state.real_time_mode || !state.waiting) return 0;

    int now = get_current_seconds();

    if(!state.wait_wrap)
    {
        int r = state.wait_end_seconds - now;
        return (r > 0) ? r : 0;
    }

    if(now < state.wait_end_seconds)
    {
        return state.wait_end_seconds - now;
    }

    return (86400 - now) + state.wait_end_seconds;
}

static bool can_progress(const SaveData& state)
{
    if(!state.real_time_mode) return true;
    if(!state.waiting) return true;
    return is_wait_done(state);
}

int main()
{
    bn::core::init();

    bn::sprite_text_generator tg(common::fixed_8x8_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> sprites;

    SaveData state = load_save();

    if(!state.valid)
    {
        state = SaveData();
        state.valid = true;
        state.real_time_mode = true;
    }

    bool in_title = true;
    bool in_log = false;
    bool continue_game = false;

    int visible_chars = 0;
    int tick_counter = 0;
    bool is_text_finished = false;

    int log_scroll_index = 0;

    const Node* current_node = nullptr;

    while(true)
    {
        sprites.clear();
        tg.set_left_alignment();

        current_node = &nodes[state.current_node];

        // Ha lejart a varakozas, toroljuk a waiting flagot
        if(state.waiting && is_wait_done(state))
        {
            state.waiting = false;
            save_game(state);
        }

        // Varakozas aktiv-e meg mindig
        bool waiting_block = state.real_time_mode &&
                             state.waiting &&
                             !is_wait_done(state);

        // HUD
        {
            bn::string<32> hud;

            hud += state.real_time_mode ? "RT " : "QP ";

            // WAIT + countdown csak ha nem a waiting screen van eppen,
            // ott ugyanez mar ki van irva, ne duplikaljuk
            if(state.real_time_mode && state.waiting && !waiting_block)
            {
                hud += "WAIT ";
            }

            hud += get_time_string();

            tg.set_right_alignment();
            tg.generate(110, -72, hud, sprites);
            tg.set_left_alignment();

            if(state.real_time_mode && state.waiting && !waiting_block)
            {
                bn::string<16> w = "W:";
                w += bn::to_string<4>(get_remaining_seconds(state));
                tg.generate(110, -52, w, sprites);
            }
        }

        if(in_title)
        {
            render_title(state.real_time_mode, tg, sprites);

            if(bn::keypad::a_pressed() && state.valid)
            {
                in_title = false;
            }

            if(bn::keypad::b_pressed())
            {
                state = SaveData();
                state.valid = true;
                state.real_time_mode = true;
                state.current_node = 0;
                save_game(state);
                in_title = false;
            }

            if(bn::keypad::l_held() && bn::keypad::r_pressed())
            {
                state.real_time_mode = !state.real_time_mode;
                save_game(state);
            }
        }
        else if(in_log)
        {
            render_log(tg, sprites, log_scroll_index);
            update_log(in_log, in_title, log_scroll_index);
        }
        else
        {
            // Waiting screen: csak a story rendering valtozik,
            // a SELECT/START input lejjebb mindig fut
            if(waiting_block)
            {
                tg.set_left_alignment();

                bn::string<32> msg = "WAIT";
                tg.generate(-60, 0, msg, sprites);

                bn::string<16> t = get_time_string();
                tg.generate(-60, 20, t, sprites);

                bn::string<16> r = "W:";
                r += bn::to_string<4>(get_remaining_seconds(state));
                tg.generate(-60, 40, r, sprites);
            }
            else
            {
                // Normalis story ag
                if(continue_game)
                {
                    visible_chars = 0;
                    tick_counter = 0;
                    is_text_finished = false;
                    continue_game = false;
                }

                if(!is_text_finished)
                {
                    tick_counter++;

                    if(tick_counter > 1)
                    {
                        tick_counter = 0;
                        visible_chars++;

                        int total_len = 0;

                        for(int i = 0; i < current_node->line_count; i++)
                        {
                            total_len += strlen(current_node->lines[i]);
                        }

                        if(visible_chars >= total_len + current_node->line_count)
                        {
                            is_text_finished = true;

                            bn::vector<bn::string<48>, MAX_LOG_LINES> log_lines;

                            for(int i = 0; i < current_node->line_count; i++)
                            {
                                log_lines.push_back(current_node->lines[i]);
                            }

                            log_message(
                                current_node->speaker,
                                log_lines,
                                get_time_string().c_str(),
                                false
                            );
                        }
                    }
                }

                render_node(*current_node, visible_chars, is_text_finished, tg, sprites);

                // A/B csak ha nincs varakozas
                if(bn::keypad::a_pressed()
                    && is_text_finished
                    && !current_node->ending
                    && can_progress(state))
                {
                    state.history[state.history_count++] = state.current_node;

                    log_choice(current_node->option_a, get_time_string().c_str());

                    state.current_node = current_node->next_a;

                    start_wait(state,
                        state.real_time_mode ? current_node->wait_seconds : 0
                    );

                    visible_chars = 0;
                    is_text_finished = false;

                    save_game(state);
                }

                if(bn::keypad::b_pressed()
                    && is_text_finished
                    && !current_node->ending
                    && can_progress(state))
                {
                    state.history[state.history_count++] = state.current_node;

                    log_choice(current_node->option_b, get_time_string().c_str());

                    state.current_node = current_node->next_b;

                    start_wait(state,
                        state.real_time_mode ? current_node->wait_seconds : 0
                    );

                    visible_chars = 0;
                    is_text_finished = false;

                    save_game(state);
                }
            }

            // SELECT es START mindig elerheto, varakozas alatt is
            if(bn::keypad::select_pressed())
            {
                in_log = true;
                log_scroll_index = 0;
            }

            if(bn::keypad::start_pressed())
            {
                in_title = true;
                in_log = false;
            }
        }

        bn::core::update();
    }
}