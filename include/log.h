#pragma once

#include "bn_string.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

constexpr int MAX_LOG = 32;
constexpr int MAX_LOG_LINES = 4;

struct LogEntry
{
    bn::string<16> speaker;

    bn::vector<bn::string<48>, MAX_LOG_LINES> lines;

    bn::string<8> time;

    bool is_player = false;
};

void log_message(
    const char* speaker,
    const bn::vector<bn::string<48>, MAX_LOG_LINES>& lines,
    const char* time,
    bool is_player);

void log_choice(const char* choice_text, const char* time);

void render_log(
    bn::sprite_text_generator& tg,
    bn::vector<bn::sprite_ptr, 128>& sprites,
    int scroll);

void update_log(bool& in_log, bool& in_title, int& scroll);
