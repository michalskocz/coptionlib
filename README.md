# C option lib

A simple implementation of the option contained in a single header 'coption.h'

## Usage
The library automatically generates option types for the specified type and implements the required methods:
```c
#include "coption.h"

GENERATE_OPTION(int)

int main(void) {
    option_int_t *option = option_int_init(); int value = 5;

    option_int_set(option, &value);
    if (option->exist) {
        int out = *option_int_get(option);
    }
    option_int_free(option);
}

```
Importantly, `option_<type>_free` only frees the buffer, not the value it points to!
