#ifndef __GLOBAL__
#define __GLOBAL__

#define CACHE_BLOCK_SIZE 64

#ifdef L2_CACHE
#define LLC_LEVEL 2
#else
#define LLC_LEVEL 1
#endif

#define MEM_BASE 0x80000000
#define MEM_SIZE 536870912
#define MEM_DELAY 30            // in ns

#define CACHE_REGSPACE_BASE 0xD000D000
#ifdef L2_CACHE
#define CACHE_REGSPACE_SIZE (NUM_CPUS*2+1) * 4096  // (num of caches) * regspace size of single cache
#else
#define CACHE_REGSPACE_SIZE (NUM_CPUS*2) * 4096    // (num of caches) * regspace size of single cache
#endif

//#define CACHE_DEBUG

#endif  // __GLOBAL__
