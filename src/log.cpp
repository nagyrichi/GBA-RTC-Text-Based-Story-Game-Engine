#include "log.h"

#include "bn_keypad.h"
#include "bn_format.h"

namespace
{
    LogEntry entries[MAX_LOG];
    int count = 0;

    constexpr int MAX_VISIBLE_LINES = 9;
    constexpr int PLAYER_WRAP = 18;
}

static void push_entry(const LogEntry& src)
{
    if(count >= MAX_LOG)
    {
        for(int i = 1; i < MAX_LOG; ++i)
        {
            entries[i - 1] = entries[i];
        }

        count = MAX_LOG - 1;
    }

    entries[count++] = src;
}

void log_message(
    const char* speaker,
    const bn::vector<bn::string<48>, MAX_LOG_LINES>& lines,
    const char* time,
    bool is_player)
{
    LogEntry e;

    e.speaker = speaker;
    e.time = time;
    e.is_player = is_player;

    for(const auto& l : lines)
    {
        e.lines.push_back(l);
    }

    push_entry(e);
}

void log_choice(const char* choice_text, const char* time)
{
    LogEntry e;

    e.speaker = "YOU";
    e.time = time;
    e.is_player = true;

    bn::string<48> text = choice_text;

    while(text.length() > PLAYER_WRAP)
    {
        bn::string<48> part;

        int split = PLAYER_WRAP;

        while(split > 0 && text[split] != ' ')
        {
            --split;
        }

        if(split <= 0)
        {
            split = PLAYER_WRAP;
        }

        for(int i = 0; i < split; ++i)
        {
            part += text[i];
        }

        if(e.lines.empty())
        {
            bn::string<48> first = "> ";
            first += part;
            e.lines.push_back(first);
        }
        else
        {
            e.lines.push_back(part);
        }

        bn::string<48> remain;

        for(int i = split + 1; i < text.length(); ++i)
        {
            remain += text[i];
        }

        text = remain;
    }

    if(text.length() > 0)
    {
        if(e.lines.empty())
        {
            bn::string<48> first = "> ";
            first += text;
            e.lines.push_back(first);
        }
        else
        {
            e.lines.push_back(text);
        }
    }

    push_entry(e);
}

static int entry_height(const LogEntry& e)
{
    int h = e.lines.size();

    if(e.speaker.length() > 0)
    {
        ++h;
    }

    return h;
}

void render_log(
    bn::sprite_text_generator& tg,
    bn::vector<bn::sprite_ptr, 128>& sprites,
    int scroll)
{
    tg.generate(-108, -72, "MESSAGE LOG", sprites);

    int y = -52;
    int used = 0;

    for(int i = scroll; i < count; ++i)
    {
        const LogEntry& e = entries[i];

        int h = entry_height(e);

        if(used + h > MAX_VISIBLE_LINES)
        {
            break;
        }

        bn::string<48> header;

        header += "[";
        header += e.time;
        header += "] ";

        header += e.speaker;

        int hx;

        if(e.is_player)
        {
            int width = header.length() * 8;
            hx = 104 - width;
        }
        else
        {
            hx = -108;
        }

        tg.generate(hx, y, header, sprites);

        y += 10;
        ++used;

        for(const auto& line : e.lines)
        {
            int lx;

            if(e.is_player)
            {
                int width = line.length() * 8;
                lx = 104 - width;
            }
            else
            {
                lx = -96;
            }

            tg.generate(lx, y, line, sprites);

            y += 12;
            ++used;
        }

        y += 4;
    }

    tg.generate(
        -108,
        64,
        bn::format<48>("LOG {}/{}", scroll + 1, count),
        sprites);
}

void update_log(bool& in_log, bool& in_title, int& scroll)
{
    if(bn::keypad::up_pressed() && scroll > 0)
    {
        --scroll;
    }

    if(bn::keypad::down_pressed() && scroll < count - 1)
    {
        ++scroll;
    }

    if(bn::keypad::select_pressed())
    {
        in_log = false;
    }

    if(bn::keypad::start_pressed())
    {
        in_log = false;
        in_title = true;
    }
}
