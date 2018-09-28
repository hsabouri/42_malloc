#include <malloc.h>

int	main(void)
{
	void *ptr;

	for (int i = 0; i < 250; i++) {
		ptr = malloc(TINY);
	}
	for (int i = 0; i < 1200; i++) {
		ptr = malloc(TINY);
		free(ptr);
	}
	for (int i = 0; i < 1000; i++) {
		ptr = malloc(TINY);
		free(ptr);
	}
	free(NULL);
	return (0);
}