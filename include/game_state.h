#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "story.h"
#include <cstdint>
#include <cstddef>

struct SaveData
{
    uint32_t magic;
    uint16_t version;

    int current_node;

    bool real_time_mode;

    bool waiting;

    int wait_end_seconds;   // 0–86399
    bool wait_wrap;

    bool valid;

    int history[64];
    int history_count;

    SaveData();
};

SaveData load_save();
void save_game(const SaveData& s);

#endif