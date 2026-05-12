#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_string.h"
#include "bn_time.h"
#include "bn_sram.h"
#include "bn_format.h"
#include "bn_vector.h"
#include "story.h"
#include "../external/butano/common/include/common_fixed_8x8_sprite_font.h"
#include <cstddef>

extern "C" size_t strlen(const char* s)
{
    const char* p = s;
    while(*p != '\0') ++p;
    return (size_t)(p - s);
}

namespace
{
    constexpr int MAX_SPRITES = 128;
    constexpr uint32_t SAVE_MAGIC = 0x4C494645;
    constexpr uint16_t SAVE_VERSION = 1;

    int global_frame = 0;

    struct SaveData
    {
        uint32_t magic = SAVE_MAGIC;
        uint16_t version = SAVE_VERSION;

        int current_node = 0;

        bool real_time_mode = false;

        bool waiting = false;
        int wait_target_node = 0;

        bn::time event_time = bn::time(0, 0, 0);
        bool event_wrap_next_day = false;

        bool valid = false;

        int history[64] = {};
        int history_count = 0;
    };

    SaveData load_save()
    {
        SaveData s;
        bn::sram::read(s);

        if(s.magic == SAVE_MAGIC &&
           s.version == SAVE_VERSION &&
           s.current_node >= 0 &&
           s.current_node < node_count)
        {
            s.valid = true;
        }
        else
        {
            s = SaveData();
        }

        return s;
    }

    void save_game(const SaveData& s)
    {
        bn::sram::write(s);
    }

    bn::time add_seconds(const bn::time& t, int sec, bool& wrap)
    {
        int total =
            t.hour()*3600 +
            t.minute()*60 +
            t.second() + sec;

        wrap = false;

        if(total >= 86400)
        {
            total -= 86400;
            wrap = true;
        }

        return bn::time(
            total / 3600,
            (total % 3600) / 60,
            total % 60
        );
    }

    bool wait_finished(const bn::time& now,
                       const bn::time& target,
                       bool wrap)
    {
        if(!wrap)
            return now >= target;

        return now < target;
    }

    bn::string<64> format_time(const bn::time& t)
    {
        bn::string<64> r;

        if(t.hour() < 10) r += "0";
        r += bn::to_string<8>(t.hour());
        r += ":";

        if(t.minute() < 10) r += "0";
        r += bn::to_string<8>(t.minute());
        r += ":";

        if(t.second() < 10) r += "0";
        r += bn::to_string<8>(t.second());

        return r;
    }
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

        bool rtc = bn::time::active();
        auto now = rtc ? bn::time::current() : bn::optional<bn::time>();

        const Node& node = nodes[state.current_node];

        // ---------------- TITLE ----------------
        if(in_title)
        {
            tg.generate(-108, -56, "LIFELINE: ORBIT", sprites);
            tg.generate(-108, -32, state.real_time_mode ? "REAL TIME" : "QUICK PLAY", sprites);

            tg.generate(-108, -4, "A: CONTINUE", sprites);
            tg.generate(-108, 12, "B: NEW GAME", sprites);

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
            tg.generate(-108, -56, "MESSAGE LOG", sprites);

            if(bn::keypad::up_pressed() && log_scroll > 0)
                --log_scroll;

            if(bn::keypad::down_pressed() && log_scroll < state.history_count - 1)
                ++log_scroll;

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
                bn::format<64>("LOG {}/{}", log_scroll+1, state.history_count),
                sprites);

            if(bn::keypad::select_pressed())
                in_log = false;

            if(bn::keypad::start_pressed())
                in_title = true;
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
                        len += strlen(node.lines[i]);

                    if(visible >= len + node.line_count)
                        finished = true;
                }
            }

            tg.generate(-108, -56, node.speaker, sprites);

            int y = -32;
            int rem = visible;

            for(int i = 0; i < node.line_count; ++i)
            {
                const char* l = node.lines[i];

                int len = strlen(l);
                bn::string<64> part;

                int show = rem;
                if(show > len) show = len;

                for(int c = 0; c < show; ++c)
                    part += l[c];

                tg.generate(-108, y, part, sprites);

                rem -= len;
                if(rem < 0) rem = 0;

                y += 12;
            }

            if(!finished)
                tg.generate(-108, 52, "RECEIVING...", sprites);

            if(finished && !node.ending)
            {
                tg.generate(-108, 36, bn::format<64>("A: {}", node.option_a), sprites);
                tg.generate(-108, 52, bn::format<64>("B: {}", node.option_b), sprites);
            }

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