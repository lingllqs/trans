#ifndef TEST_H
#define TEST_H

/* ASSERT 宏依赖 stdlib.h 和 stdio.h */
#include <stdlib.h>
#include <stdio.h>


#define ASSERT(cond)                                                                  \
    do {                                                                              \
        if (!(cond)) {                                                                \
            fprintf(stderr, "ASSERT FAILED: %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            exit(1);                                                                  \
        }                                                                             \
    } while (0)

#endif  // !TEST_H
