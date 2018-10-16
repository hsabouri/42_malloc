#include "../includes/malloc.h"

int main()
{
    void *addr;

    addr = malloc(100);
    show_alloc_mem();
    ft_putstr("\n");

    addr = malloc(1000);
    show_alloc_mem();
    ft_putstr("\n");

    addr = malloc(10000);
    show_alloc_mem();
    ft_putstr("\n");

    free(addr);
    show_alloc_mem();
    ft_putstr("\n");

    addr = malloc(100);
    show_alloc_mem();
    ft_putstr("\n");

    addr = realloc(addr, 1000);
    show_alloc_mem();
    ft_putstr("\n");

    addr = realloc(addr, 10000);
    show_alloc_mem();
    ft_putstr("\n");
    return (0);
}