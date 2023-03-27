#include <stdarg.h>
#include <stdio.h>

/**
 * get_precision - custom printf function that handles precision for non-custom conversion specifiers
 * @format: format string
 * Return: number of characters printed
 */
int get_precision(const char *format, ...)
{
	va_list args;
	 int printed_chars = 0;
	 int precision = -1;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;

 	if (*format == '.')
            {
                precision = 0;
                while (*(++format) >= '0' && *format <= '9')
                    precision = precision * 10 + (*format - '0');
            }

            switch (*format)
            {
                case 'd':
                    printed_chars += printf("%d", va_arg(args, int));
                    break;
                case 'f':
                    printed_chars += precision == -1 ? printf("%f", va_arg(args, double))
                                                      : printf("%.*f", precision, va_arg(args, double));
                    break;
                case 'c':
                    printed_chars += printf("%c", va_arg(args, int));
                    break;
                case 's':
                    printed_chars += printf("%.*s", precision, va_arg(args, char *));
                    break;
                default:
                    printed_chars += printf("Invalid format specifier");
                    break;
            }
        }
        else
        {
            putchar(*format);
            printed_chars++;
        }
        format++;
    }

    va_end(args);

    return printed_chars;
}
