#ifndef __COMMON_H__
#define __COMMON_H__


#include <stdint.h>
#include <stdlib.h>

#define __align(x) __attribute__((aligned(x)))

inline static void mwr(const uint32_t volatile *addr, const uint32_t data) {
    *(volatile uint32_t *volatile) (addr) = data;
}

inline static uint32_t mrd(const uint32_t volatile *addr) {
    return (*(volatile uint32_t *volatile) (addr));
}

inline static void infinite_loop(void) {
    while (1) {};
}


#endif /* __COMMON_H__ */
