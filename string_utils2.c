#include "main.h"

/**
 * write_int - write the integer n to stdout
 * @n: input integer
 * Return: void (no return)
 */
void write_int(int n)
{
	unsigned int x;

	if (n < 0)
	{
		_putchar('-', STDERR_FILENO);
		x = -n;
	} else
	{
		x = n;
	}

	if (x / 10)
	{
		write_int(x / 10);

	}

	_putchar((x % 10) + '0', STDERR_FILENO);
}
