all: hexdump copy cmp size
	@echo "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"

hexdump:
	cc -std=c99 -pedantic -Wall -Wextra -Werror -o bin/hexdump tools/hexdump.c

copy:
	cc -std=c99 -pedantic -Wall -Wextra -Werror -o bin/copy tools/copy.c lib/sandbox.c

cmp:
	cc -std=c99 -pedantic -Wall -Wextra -Werror -o bin/cmp tools/cmp.c

size:
	cc -std=c99 -pedantic -Wall -Wextra -Werror -o bin/size tools/size.c

clean:
	rm -rf bin/hexdump bin/cmp bin/size bin/copy
