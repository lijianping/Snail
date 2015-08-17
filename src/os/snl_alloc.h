#ifndef SNL_ALLOC_H
#define SNL_ALLOC_H

#include <snl_config.h>
#include <snl_utils.h>

#define SNL_DEFAULT_ALIGN   16

#define snl_algin(p, n)     (char *)((size_t)(p + (n - 1)) & ~(n - 1))

void *snl_malloc(size_t size);
void *snl_calloc(size_t size);
void snl_free(void *ptr);

#endif /* SNL_ALLOC_H */
