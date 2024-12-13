#include "transform.h"

static struct pixel get_pixel(const struct image *img, uint64_t x, uint64_t y){
    return *get_pixel_address((struct image *)img, x, y);
}
static void set_pixel(struct image *img, uint64_t x, uint64_t y, struct pixel p){
    *get_pixel_address(img, x, y) = p;
}
struct image rotate_cw90(const struct image *source){
    struct image result = create_image(source->height, source->width);
    for (uint64_t y = 0; y < source->height; ++y)
        for (uint64_t x = 0; x < source->width; ++x)
            set_pixel(&result, y, result.height - x - 1, get_pixel(source, x, y));
    return result;
}
struct image rotate_ccw90(const struct image *source){
    struct image result = create_image(source->height, source->width);
    for (uint64_t y = 0; y < source->height; ++y)
        for (uint64_t x = 0; x < source->width; ++x)
            set_pixel(&result, result.width - 1 - y, x, get_pixel(source, x, y));
    return result;
}
struct image flip_h(const struct image *source){
    struct image result = create_image(source->width, source->height);
    for (uint64_t y = 0; y < source->height; ++y) {
        for (uint64_t x = 0; x < source->width; ++x) {
            set_pixel(&result, source->width - x - 1, y, get_pixel(source, x, y));
        }
    }
    return result;
}
struct image flip_v(const struct image *source){
    struct image result = create_image(source->width, source->height);
    for (uint64_t y = 0; y < source->height; ++y) {
        for (uint64_t x = 0; x < source->width; ++x) {
            set_pixel(&result, x, source->height - y - 1, get_pixel(source, x, y));
        }
    }
    return result;
}
