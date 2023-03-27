#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

/**
 * get_precision - custom printf function that handles precision for non-custom conversion specifiers
 * @format: format string
 * Return: number of characters printed
 */
int get_precision(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;
	int precision = (-1);

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;

			/* handle precision for floating-point numbers*/
			if (*format == '.')
			{
				format++;
				precision = 0;
				while (*format >= '0' && *format <= '9')
				{
					precision = (precision * 10) + (*format - '0');
					format++;
				}	
			}

			switch (*format)
			{
				case 'd':
				{
					int value = va_arg(args, int);
					printf("%d", value);
					printed_chars++;
					break;
				}
				case 'f':
				{
					double value = va_arg(args, double);
					if (precision != -1)
					{
						printf("%.*f", precision, value);
					}
					else
					{
						printf("%f", value);
					}
					printed_chars++;
					break;
				}
				case 'c':
				{
					char value = va_arg(args, int);  /* char is promoted to int in variadic functions*/
					printf("%c", value);
					printed_chars++;
					break;
				}
				case 's':
				{
					char *value = va_arg(args, char *);
					printf("%s", value);
					printed_chars += strlen(value);
					break;
				}
				default:
					printf("Invalid format specifier");
					printed_chars += 20; /* assuming 20 characters are printed for an error message*/
				break;
			}
		}
		else
		{
			printf("%c", *format);
			printed_chars++;
		}

		format++;
	}

	va_end(args);

	return printed_chars;
}
