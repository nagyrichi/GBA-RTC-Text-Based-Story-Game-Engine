#pragma once

#include "bn_string.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

constexpr int MAX_LOG = 128;

struct LogEntry
{
    bn::string<32> speaker;
    bn::string<64> text;
};

void log_message(const char* speaker, const char* text);
void log_choice(const char* choice_text);

void render_log(bn::sprite_text_generator& tg,
    bn::vector<bn::sprite_ptr, 128>& sprites,
    int scroll);

void update_log(bool& in_log, bool& in_title, int& scroll);