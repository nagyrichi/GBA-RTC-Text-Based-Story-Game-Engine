#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_time.h"
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

    while(true)
    {
        sprites.clear();
        tg.set_left_alignment();

        const Node& node = nodes[state.current_node];

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
            render_log(state, nodes, tg, sprites, log_scroll);
            update_log(in_log, in_title, log_scroll, state);
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
                    for(int i = 0; i < node.line_count; ++i)
                    {
                        len += strlen(node.lines[i]);
                    }

                    if(visible >= len + node.line_count)
                    {
                        finished = true;
                    }
                }
            }

            render_node(node, visible, finished, tg, sprites);

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

            if(bn::keypad::a_pressed() && finished && !node.ending)
            {
                state.history[state.history_count++] = state.current_node;
                state.current_node = node.next_a;

                visible = 0;
                finished = false;

                save_game(state);
            }

            if(bn::keypad::b_pressed() && finished && !node.ending)
            {
                state.history[state.history_count++] = state.current_node;
                state.current_node = node.next_b;

                visible = 0;
                finished = false;

                save_game(state);
            }
        }

        ++global_frame;
        bn::core::update();
    }
}
