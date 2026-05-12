#include "ui_text.h"
#include "game_state.h"
#include "bn_format.h"

void render_title(bool real_time_mode, bn::sprite_text_generator& tg,
    bn::vector<bn::sprite_ptr, 128>& sprites)
{
    tg.generate(-108, -56, "LIFELINE: ORBIT", sprites);
    tg.generate(-108, -32, real_time_mode ? "REAL TIME" : "QUICK PLAY", sprites);

    tg.generate(-108, -4, "A: CONTINUE", sprites);
    tg.generate(-108, 12, "B: NEW GAME", sprites);
}

void render_node(const Node& node, int visible, bool finished,
    bn::sprite_text_generator& tg, bn::vector<bn::sprite_ptr, 128>& sprites)
{
    tg.generate(-108, -56, node.speaker, sprites);

    int y = -32;
    int rem = visible;

    for(int i = 0; i < node.line_count; ++i)
    {
        const char* l = node.lines[i];
        int len = strlen(l);
        bn::string<64> part;

        int show = rem;
        if(show > len)
        {
            show = len;
        }

        for(int c = 0; c < show; ++c)
        {
            part += l[c];
        }

        tg.generate(-108, y, part, sprites);

        rem -= len;
        if(rem < 0)
        {
            rem = 0;
        }

        y += 12;
    }

    if(!finished)
    {
        tg.generate(-108, 52, "RECEIVING...", sprites);
    }

    if(finished && !node.ending)
    {
        tg.generate(-108, 36, bn::format<64>("A: {}", node.option_a), sprites);
        tg.generate(-108, 52, bn::format<64>("B: {}", node.option_b), sprites);
    }
}
