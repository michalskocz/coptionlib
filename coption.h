/*
Copyright (c) 2026 Michał Skoczylas
Licensed under the BSD 2-Clause License
*/

#ifndef C_OPTION_H
#define C_OPTION_H

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#define __GET_OPTION_TYPE_EXTERNAL_NAME(type) option_##type##_t
#define __GET_OPTION_TYPE_INTERNAL_NAME(type) __option_##type##_t

#define __OPTION_INTERNAL_FROM_EXTERNAL(type, opt) \
    ((__GET_OPTION_TYPE_INTERNAL_NAME(type) *)((char *)(opt) - sizeof(__GET_OPTION_TYPE_INTERNAL_NAME(type))))

#define __GENERATE_OPTION_TYPE(type)                                      \
typedef struct {                                                          \
    bool exist;                                                           \
} __GET_OPTION_TYPE_EXTERNAL_NAME(type);                                   \
                                                                          \
typedef struct {                                                          \
    type *value;                                                          \
} __GET_OPTION_TYPE_INTERNAL_NAME(type);

#define __GENERATE_OPTION_TYPE_INIT(type)                                 \
static inline __GET_OPTION_TYPE_EXTERNAL_NAME(type) *option_##type##_init(void) \
{                                                                         \
    char *buffer = malloc(                                                \
        sizeof(__GET_OPTION_TYPE_INTERNAL_NAME(type)) +                   \
        sizeof(__GET_OPTION_TYPE_EXTERNAL_NAME(type)));                   \
                                                                          \
    if (!buffer)                                                          \
        return NULL;                                                      \
                                                                          \
    __GET_OPTION_TYPE_INTERNAL_NAME(type) *hidden =                        \
        (__GET_OPTION_TYPE_INTERNAL_NAME(type) *)buffer;                  \
                                                                          \
    __GET_OPTION_TYPE_EXTERNAL_NAME(type) *opt =                          \
        (__GET_OPTION_TYPE_EXTERNAL_NAME(type) *)(                        \
            buffer + sizeof(__GET_OPTION_TYPE_INTERNAL_NAME(type)));      \
                                                                          \
    hidden->value = NULL;                                                 \
    opt->exist = false;                                                   \
                                                                          \
    return opt;                                                           \
}

#define __GENERATE_OPTION_TYPE_SET(type)                                  \
static inline void option_##type##_set(                                   \
    __GET_OPTION_TYPE_EXTERNAL_NAME(type) *opt,                           \
    type *value)                                                          \
{                                                                         \
    if (!opt)                                                             \
        return;                                                           \
                                                                          \
    __GET_OPTION_TYPE_INTERNAL_NAME(type) *hidden =                       \
        __OPTION_INTERNAL_FROM_EXTERNAL(type, opt);                       \
                                                                          \
    hidden->value = value;                                                \
    opt->exist = (value != NULL);                                         \
}

#define __GENERATE_OPTION_TYPE_FREE(type)                                 \
static inline void option_##type##_free(                                  \
    __GET_OPTION_TYPE_EXTERNAL_NAME(type) *opt)                           \
{                                                                         \
    if (!opt)                                                             \
        return;                                                           \
                                                                          \
    free((char *)opt - sizeof(__GET_OPTION_TYPE_INTERNAL_NAME(type)));    \
}

#define __GENERATE_OPTION_TYPE_GET(type)                                  \
static inline type *option_##type##_get(                                  \
    __GET_OPTION_TYPE_EXTERNAL_NAME(type) *opt)                           \
{                                                                         \
    if (!opt || !opt->exist)                                              \
        return NULL;                                                      \
                                                                          \
    __GET_OPTION_TYPE_INTERNAL_NAME(type) *hidden =                       \
        __OPTION_INTERNAL_FROM_EXTERNAL(type, opt);                       \
                                                                          \
    return hidden->value;                                                 \
}

#define __GENERATE_OPTION_TYPE_GET_OR_ELSE(type)                          \
static inline type *option_##type##_get_or_else(                          \
    __GET_OPTION_TYPE_EXTERNAL_NAME(type) *opt,                           \
    type *fallback)                                                       \
{                                                                         \
    type *value = option_##type##_get(opt);                               \
    return value ? value : fallback;                                      \
}

#define __GENERATE_OPTION_METHODS(type)                                   \
__GENERATE_OPTION_TYPE_INIT(type)                                         \
__GENERATE_OPTION_TYPE_SET(type)                                          \
__GENERATE_OPTION_TYPE_FREE(type)                                         \
__GENERATE_OPTION_TYPE_GET(type)                                          \
__GENERATE_OPTION_TYPE_GET_OR_ELSE(type)

#define GENERATE_OPTION(type)                                             \
__GENERATE_OPTION_TYPE(type)                                              \
__GENERATE_OPTION_METHODS(type)

#endif // C_OPTION_H
