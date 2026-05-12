#include "log.h"
#include "bn_format.h"
#include "bn_keypad.h"

void render_log(const SaveData& state, const Node nodes[], bn::sprite_text_generator& tg,
    bn::vector<bn::sprite_ptr, 128>& sprites, int log_scroll)
{
    tg.generate(-108, -56, "MESSAGE LOG", sprites);

    int y = -32;

    for(int i = log_scroll; i < state.history_count && y < 56; ++i)
    {
        const Node& n = nodes[state.history[i]];

        tg.generate(-108, y, n.speaker, sprites);
        y += 10;

        for(int l = 0; l < n.line_count && y < 56; ++l)
        {
            tg.generate(-96, y, n.lines[l], sprites);
            y += 10;
        }

        y += 6;
    }

    tg.generate(-108, 52,
        bn::format<64>("LOG {}/{}", log_scroll + 1, state.history_count),
        sprites);
}

void update_log(bool& in_log, bool& in_title, int& log_scroll, const SaveData& state)
{
    if(bn::keypad::up_pressed() && log_scroll > 0)
    {
        --log_scroll;
    }

    if(bn::keypad::down_pressed() && log_scroll < state.history_count - 1)
    {
        ++log_scroll;
    }

    if(bn::keypad::select_pressed())
    {
        in_log = false;
    }

    if(bn::keypad::start_pressed())
    {
        in_title = true;
        in_log = false;
    }
}
