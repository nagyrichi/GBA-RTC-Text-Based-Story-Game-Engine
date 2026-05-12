#include "log.h"
#include "bn_keypad.h"
#include "bn_format.h"

namespace
{
    LogEntry entries[MAX_LOG];
    int count = 0;

    constexpr int MAX_VISIBLE_UNITS = 6; // "line budget"
    constexpr int MAX_CHARS_PER_LINE = 24;
}

void push(const char* speaker, const char* text)
{
    if(count >= MAX_LOG)
    {
        for(int i = 1; i < MAX_LOG; ++i)
        {
            entries[i - 1] = entries[i];
        }
        count = MAX_LOG - 1;
    }

    LogEntry& e = entries[count++];
    e.speaker = speaker;
    e.text = text;
}

void log_message(const char* speaker, const char* text)
{
    push(speaker, text);
}

void log_choice(const char* choice_text)
{
    bn::string<64> t = "    > ";
    t += choice_text;
    push("", t.c_str());
}

bn::vector<bn::string<64>, 6> wrap_text(const bn::string<64>& text)
{
    bn::vector<bn::string<64>, 6> lines;

    bn::string<64> current;
    int count_chars = 0;

    for(char c : text)
    {
        current += c;
        ++count_chars;

        if(count_chars >= MAX_CHARS_PER_LINE && c == ' ')
        {
            lines.push_back(current);
            current.clear();
            count_chars = 0;
        }
    }

    if(current.length() > 0)
    {
        lines.push_back(current);
    }

    return lines;
}

int entry_height(const LogEntry& e)
{
    auto lines = wrap_text(e.text);

    int h = lines.size();

    if(e.speaker.length() > 0)
        h += 1;

    return h;
}

void render_log(bn::sprite_text_generator& tg,
    bn::vector<bn::sprite_ptr, 128>& sprites,
    int scroll)
{
    tg.generate(-108, -56, "MESSAGE LOG", sprites);

    int y = -32;
    int used_units = 0;

    for(int i = scroll; i < count; ++i)
    {
        const LogEntry& e = entries[i];

        int entry_units = entry_height(e);

        if(used_units + entry_units > MAX_VISIBLE_UNITS)
            break;

        if(e.speaker.length() > 0)
        {
            tg.generate(-108, y, e.speaker, sprites);
            y += 10;
            ++used_units;
        }

        auto lines = wrap_text(e.text);

        for(int l = 0; l < lines.size(); ++l)
        {
            tg.generate(-96, y, lines[l], sprites);
            y += 12;
            ++used_units;
        }
    }

    tg.generate(-108, 64,
        bn::format<64>("LOG {}/{}", scroll + 1, count),
        sprites);
}

void update_log(bool& in_log, bool& in_title, int& scroll)
{
    if(bn::keypad::up_pressed() && scroll > 0)
        --scroll;

    if(bn::keypad::down_pressed() && scroll < count - 1)
        ++scroll;

    if(bn::keypad::select_pressed())
        in_log = false;

    if(bn::keypad::start_pressed())
    {
        in_log = false;
        in_title = true;
    }
}