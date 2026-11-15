/* sandbox.c */

#include "sandbox.h"

#include <stddef.h>
#include <string.h>

static int has_prefix(const char *s, const char *prefix) {
    size_t n = strlen(prefix);
    return strncmp(s, prefix, n) == 0;
}

static int contains_dotdot(const char *s) {
    /* Reject any path containing a ".." component */
    const char *p = s;
    while((p = strstr(p, "..")) != NULL) {
        int at_start = (p == s) || (p[2] == '/');
        int at_end = (p[2] == '\0') || (p[2] == '/');
        if(at_start && at_end) {
            return 1;
        }
        p += 2;
    }
    return 0;
}

static int contains_foreign_separator(const char *s) {
    /* Reject windows-style paths; this book uses POSIX-style paths. */
    return strchr(s, '\\') != NULL || strchr(s, ':') != NULL;
}

int sandbox_check_path(const char *path) {
    if(path == NULL) {
        return -1;
    }
    /* Absolute paths are never under sandbox/ */
    if(path[0] == '/') {
        return -1;
    }
    if(contains_foreign_separator(path)) {
        return -1;
    }
    if(contains_dotdot(path)) {
        return -1;
    }
    if(has_prefix(path, "sandbox/")) {
        return 0;
    }
    return -1;
}

