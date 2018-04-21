#ifndef REPPAT
#define REPPAT

#define F_EXEC(name) int exec_##name(\
	regexp_t*re, pat_t*pat,\
	const char*str, off_t off,\
	size_t*matlen, ...)
typedef struct pat_t pat_t;
struct pat_t{
	linked_t proto;
	int(*matcher)(regexp_t*, pat_t*, const char*, off_t, size_t*, ...);
};

typedef struct reppat_common{
	reppat_t proto;
	varray_t srt;
}reppat_common;
typedef struct reppat_group{
	reppat_t proto;
	int gindex;
	bool reverse;
	reppat_t*pats;
}reppat_group;

#endif//REPPAT
