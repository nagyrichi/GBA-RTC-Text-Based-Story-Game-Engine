#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "story.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

void render_title(bool real_time_mode, bn::sprite_text_generator& tg,
    bn::vector<bn::sprite_ptr, 128>& sprites);

void render_node(const Node& node, int visible, bool finished,
    bn::sprite_text_generator& tg, bn::vector<bn::sprite_ptr, 128>& sprites);

#endif // UI_TEXT_H
