#include <malloc.h>

int	main(void)
{
	printf("Test of maxing out TINY pools:\n");
	for (int i = 0; i < 10000; i++) {
		printf("%zu - ", (size_t)malloc(TINY));
	}
	printf("\n");
	printf("Test of maxing out SMALL pools:\n");
	for (int i = 0; i < 10000; i++) {
		printf("%zu - ", (size_t)malloc(SMALL));
	}
	printf("\n");
	printf("Test of maxing out LARGE pools:\n");
	for (int i = 0; i < 10; i++) {
		printf("%zu - ", (size_t)malloc(10000));
	}
	return (0);
}