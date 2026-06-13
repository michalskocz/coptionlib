# C option lib

A simple implementation of the option contained in a single header `coption.h`

## Usage
The library automatically generates option types for the specified type and implements the required methods:
```c
#include "coption.h"
#include <stdio.h>
#include <stdbool.h>


GENERATE_OPTION(int)


static option_int_t *option_case(bool test) {
    if (test) {
        int *value = malloc(sizeof(int));
        *value = 5;

        option_int_t *opt = option_int_init();
        option_int_set(opt, value);

        return opt;
    } else {
        return option_int_init();
    }
}

int main(void) {
    int defult_valu = 10;
    option_int_t *v1 = option_case(true);
    option_int_t *v2 = option_case(false);

    printf("Not epty: %d\n", *option_int_get_or_else(v1, &defult_valu)); // Olweys not null - seaf
    printf("Epty: %d\n", *option_int_get_or_else(v2, &defult_valu));

    if (option_int_get(v1)) {
        printf("Not null v1\n");
        free(option_int_get(v1));
    }

    if (option_int_get(v2)) {
        printf("Not null v2\n");
        free(option_int_get(v2));
    }
    option_int_free(v1);
    option_int_free(v2);

    return 0;
}
```
Output:
```bash
$ ./test
Not epty: 5
Epty: 10
Not null v1
```

Importantly, `option_<type>_free` only frees the buffer, not the value it points to!
