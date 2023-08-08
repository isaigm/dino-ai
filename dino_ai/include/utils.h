#include <cstdlib>
#ifndef UTILS_H
#define UTILS_H
static int get_random_number(int x, int y)
{
    return rand() % (y + 1 - x) + x;
}
#endif
