#ifndef CHRSET
#define CHRSET

#include<sys/types.h>

typedef size_t(*chrsize_fn)(const char*);
extern char*strget(const char*, chrsize_fn, int, size_t*);
extern size_t strlenof(const char*, chrsize_fn, size_t*);

#define CHRSIZE_FN(name) extern size_t chrsize_##name(const char*)
CHRSIZE_FN(ascii);
CHRSIZE_FN(gbk);
CHRSIZE_FN(utf8);
#undef CHRSIZE_FN

#endif//CHRSET
