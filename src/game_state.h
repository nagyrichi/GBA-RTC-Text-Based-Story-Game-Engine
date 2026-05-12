#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "story.h"
#include "bn_time.h"
#include "bn_string.h"
#include <cstddef>

extern "C" size_t strlen(const char* s);

struct SaveData
{
    uint32_t magic = 0;
    uint16_t version = 0;

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

SaveData load_save();
void save_game(const SaveData& s);

bn::time add_seconds(const bn::time& t, int sec, bool& wrap);
bool wait_finished(const bn::time& now, const bn::time& target, bool wrap);
bn::string<64> format_time(const bn::time& t);

#endif // GAME_STATE_H
