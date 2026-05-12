#ifndef STORY_H
#define STORY_H

struct Node
{
    const char* speaker;

    const char* lines[5];
    int line_count;

    const char* option_a;
    const char* option_b;

    int next_a;
    int next_b;

    bool wait_a;
    int wait_seconds;

    bool ending;
    bool success;
};

extern const Node nodes[];
extern const int node_count;

#endif
