#include "game_state.h"
#include "bn_sram.h"
#include "bn_format.h"
#include <cstddef>

extern "C" size_t strlen(const char* s)
{
    const char* p = s;
    while(*p != '\0') ++p;
    return (size_t)(p - s);
}

namespace
{
    constexpr uint32_t SAVE_MAGIC = 0x4C494645;
    constexpr uint16_t SAVE_VERSION = 1;
}

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
    {
        return now >= target;
    }

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
