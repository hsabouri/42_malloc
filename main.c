#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(void)
{
	void *ptr;
	void *otherptr;

	write(1, "\n", 1);
	write(1, "\n", 1);
	write(1, "\n", 1);
	write(1, "\n", 1);
	write(1, "\n", 1);
	ptr = malloc(16);
	strcpy(ptr, "Hello !\n");
	write(1, (char *)ptr, 10);
	ptr = realloc(ptr, 5000);
	write(1, (char *)ptr, 10);
	/*
	for (int i = 0; i < 2789; i++) {
		ptr = malloc(16);
		strcpy(ptr, "Hello !");
		printf("%s\n", (char *)ptr);
	}
	otherptr = ptr;
	for (int i = 0; i < 2789; i++) {
		ptr = malloc(16);
		strcpy(ptr, "Hello !");
		printf("%s\n", (char *)ptr);
	}
	otherptr = realloc(otherptr, 5000);
	printf("%s\n", (char *)otherptr);
	ptr = realloc(ptr, 5000);
	printf("%s\n", (char *)ptr);
	otherptr = realloc(otherptr, 10000);
	printf("%s\n", (char *)otherptr);
	*/
	return (0);
}