#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "image.h"

struct image rotate_cw90(const struct image *source);
struct image rotate_ccw90(const struct image *source);
struct image flip_h(const struct image *source);
struct image flip_v(const struct image *source);
#endif //TRANSFORM_H
