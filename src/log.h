#ifndef LOG_H
#define LOG_H

#include "game_state.h"
#include "story.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

void render_log(const SaveData& state, const Node nodes[], bn::sprite_text_generator& tg,
    bn::vector<bn::sprite_ptr, 128>& sprites, int log_scroll);

void update_log(bool& in_log, bool& in_title, int& log_scroll, const SaveData& state);

#endif // LOG_H
