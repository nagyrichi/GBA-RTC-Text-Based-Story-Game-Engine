#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"

#include "game_state.h"
#include "ui_text.h"
#include "log.h"
#include "story.h"

#include "../external/butano/common/include/common_fixed_8x8_sprite_font.h"

namespace
{
    constexpr int MAX_SPRITES = 128;
    int global_frame = 0;
}

int main()
{
    bn::core::init();

    bn::sprite_text_generator tg(common::fixed_8x8_sprite_font);
    bn::vector<bn::sprite_ptr, MAX_SPRITES> sprites;

    SaveData state = load_save();

    bool in_title = true;
    bool in_log = false;

    int visible = 0;
    int tick = 0;
    bool finished = false;

    int log_scroll = 0;

    const Node* node = &nodes[state.current_node];

    while(true)
    {
        sprites.clear();
        tg.set_left_alignment();

        node = &nodes[state.current_node];

        // ---------------- TITLE ----------------
        if(in_title)
        {
            render_title(state.real_time_mode, tg, sprites);

            if(bn::keypad::a_pressed() && state.valid)
            {
                in_title = false;
                visible = 0;
                finished = false;
            }

            if(bn::keypad::b_pressed())
            {
                state = SaveData();
                state.valid = true;
                save_game(state);

                in_title = false;
                visible = 0;
                finished = false;
            }
        }

        // ---------------- LOG ----------------
        else if(in_log)
        {
            render_log(tg, sprites, log_scroll);
            update_log(in_log, in_title, log_scroll);
        }

        // ---------------- GAME ----------------
        else
        {
            if(!state.waiting && !finished)
            {
                tick++;

                if(tick > 1)
                {
                    tick = 0;
                    visible++;

                    int len = 0;
                    for(int i = 0; i < node->line_count; ++i)
                    {
                        len += strlen(node->lines[i]);
                    }

                    if(visible >= len + node->line_count)
                    {
                        finished = true;

                        // ✔ FULL MESSAGE LOG (minden sor)
                        bn::string<128> full;

                        for(int i = 0; i < node->line_count; ++i)
                        {
                            full += node->lines[i];

                            if(i < node->line_count - 1)
                                full += " ";
                        }

                        log_message(node->speaker, full.c_str());
                    }
                }
            }

            render_node(*node, visible, finished, tg, sprites);

            if(bn::keypad::select_pressed())
            {
                in_log = true;
                log_scroll = 0;
            }

            if(bn::keypad::start_pressed())
            {
                in_title = true;
                in_log = false;
            }

            // ---------------- CHOICE A ----------------
            if(bn::keypad::a_pressed() && finished && !node->ending)
            {
                state.history[state.history_count++] = state.current_node;

                log_choice(node->option_a);

                state.current_node = node->next_a;

                visible = 0;
                finished = false;

                save_game(state);
            }

            // ---------------- CHOICE B ----------------
            if(bn::keypad::b_pressed() && finished && !node->ending)
            {
                state.history[state.history_count++] = state.current_node;

                log_choice(node->option_b);

                state.current_node = node->next_b;

                visible = 0;
                finished = false;

                save_game(state);
            }
        }

        ++global_frame;
        bn::core::update();
    }
}