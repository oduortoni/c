/* sandbox.h */
#ifndef SANDBOX_H
#define SANDBOX_H

#include <stddef.h>

/*
 * Returns 0 if path is under sandbox/, nonzero otherwise.
 * A path is under sandbox/ if it begins with "sandbox/".
 * Absolute pathes, paths that climb out with "..",
 * and paths containing backslashes or colons (Window-style) are rejected
 * This is a lexical check, not a filesystem check; it does not:
 * resolve symlink, and it does not require the directory to exist.
 * It accepts POSIX-style paths only.
 */

int sandbox_check_path(const char *path);

#endif

