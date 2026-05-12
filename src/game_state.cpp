#include "game_state.h"
#include "bn_sram.h"
#include "story.h"

constexpr uint32_t SAVE_MAGIC = 0x4C494645;
constexpr uint16_t SAVE_VERSION = 1;

SaveData::SaveData()
{
    magic = SAVE_MAGIC;
    version = SAVE_VERSION;

    current_node = 0;

    real_time_mode = false;

    waiting = false;
    wait_end_seconds = 0;
    wait_wrap = false;

    valid = false;

    history_count = 0;
}

SaveData load_save()
{
    SaveData s;
    bn::sram::read(s);

    if(s.magic != SAVE_MAGIC || s.version != SAVE_VERSION)
    {
        return SaveData();
    }

    if(s.current_node < 0 || s.current_node >= node_count)
    {
        return SaveData();
    }

    s.valid = true;
    return s;
}

void save_game(const SaveData& s)
{
    SaveData copy = s;

    copy.magic = SAVE_MAGIC;
    copy.version = SAVE_VERSION;

    bn::sram::write(copy);
}