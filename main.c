#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(void)
{
	void *ptr;

	ptr = malloc(2000);
	strcpy(ptr, "Hello. I am a good person, what do you think about me ?!\n");
	printf("%s\n", ptr);
	ptr = realloc(ptr, 3);
	ptr = realloc(ptr, 2000);
	ptr = realloc(ptr, 8000);
	ptr = realloc(ptr, 523957);
	printf("%s\n", ptr);
	free(ptr);
	free(ptr);
	return (0);
}