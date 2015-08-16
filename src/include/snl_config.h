#ifndef SNL_CONFIG_H
#define SNL_CONFIG_H

#ifdef __linux__

#include <snl_linux_config.h>

#endif

typedef int           snl_int_t;
typedef unsigned int  snl_uint_t;

typedef unsigned char u_char;

typedef int8_t        snl_int8_t;
typedef uint8_t       snl_uint8_t;

typedef int16_t       snl_int16_t;
typedef uint16_t      snl_uint16_t;

typedef int32_t       snl_int32_t;
typedef uint32_t      snl_uint32_t;

typedef int64_t       snl_int64_t;
typedef uint64_t      snl_uint64_t;


#endif /* SNL_CONFIG_H */
