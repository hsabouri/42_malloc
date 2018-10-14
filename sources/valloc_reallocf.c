#include <malloc.h>

extern void *valloc(size_t s)
{
	return (malloc(s));
}

extern void *reallocf(void *addr, size_t size)
{
	void *a = realloc(addr, size);
	if (a == NULL) {
		free(addr);
		return (NULL);
	}
	return (a);
}