#include "test.h"
#include "sandbox.h"

int main() {
    int success;

    success = sandbox_check_path("/absolute/path.c");
    assert_eq("Absolute path /absolute/path.c must fail", -1, success);

    return 0;
}

