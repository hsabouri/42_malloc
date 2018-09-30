#include <malloc.h>

int	main(void)
{
	void *ptr;
	void *to_free;
	
	ptr = malloc(1000);
	ptr = malloc(1000);
	free(ptr);
	ptr = malloc(1000);
	ptr = malloc(1000);
	to_free = malloc(1000);
	ptr = malloc(1000);
	ptr = malloc(1000);
	ptr = malloc(1000);
	free(to_free);
	free(ptr);
	return (0);
}