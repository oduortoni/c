#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#undef NDEBUG
#include <assert.h>

// Helper to pick the right format specifier based on type
#define FMT_SPEC(x) _Generic((x), \
    int: "%d", \
    unsigned int: "%u", \
    long: "%ld", \
    double: "%f", \
    char *: "\"%s\"", \
    const char *: "\"%s\"", \
    default: "%p" \
)

#define assert_eq(msg, value1, value2) do { \
    __typeof__(value1) _v1 = (value1); \
    __typeof__(value2) _v2 = (value2); \
    if (_v1 != _v2) { \
        fprintf(stderr, "Assertion failed: %s\n", (msg)); \
        fprintf(stderr, "  Expected: "); \
        fprintf(stderr, FMT_SPEC(_v1), _v1); \
        fprintf(stderr, "\n  Actual:   "); \
        fprintf(stderr, FMT_SPEC(_v2), _v2); \
        fprintf(stderr, "\n"); \
        assert(0); \
    } \
} while (0)

#endif

