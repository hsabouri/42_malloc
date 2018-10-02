#include <malloc.h>

int	main(void)
{
	void *ptr;
	void *to_free[10];
	
	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);

	to_free[0] = malloc(10);
	to_free[1] = malloc(10);
	to_free[2] = malloc(10);
	to_free[3] = malloc(10);
	to_free[4] = malloc(10);
	to_free[5] = malloc(10);
	to_free[6] = malloc(10);
	to_free[7] = malloc(10);
	to_free[8] = malloc(10);
	to_free[9] = malloc(10);

	ptr = malloc(10);
	ptr = malloc(10);
	ptr = malloc(10);

	free(to_free[0]);
	free(to_free[5]);
	free(to_free[1]);
	free(to_free[8]);
	free(to_free[3]);
	free(ptr);
	free(to_free[4]);
	free(to_free[6]);
	free(to_free[7]);
	free(to_free[2]);
	free(to_free[9]);


	return (0);
}