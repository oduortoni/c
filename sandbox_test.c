/*
 * sandbox_test.c
 *
 * Compilation command:
 *      cc -o sandbox_test sandbox_test.c test.h  sandbox.c
 *
*/

#include "test.h"
#include "sandbox.h"

int main() {
    int success;

    success = sandbox_check_path("/absolute/path.c");
    assert_eq("Absolute path /absolute/path.c must fail", -1, success);
    
    success = sandbox_check_path("C:\\windows\\style\\path.c");
    assert_eq("Windows style path must fail", -1, success);

    return 0;
}

