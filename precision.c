#include "main.h"

/**
 * get_precision - Calculates the precision for printing.
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: List of arguments.
 *
 * Return: Precision on success, -1 on error.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = 0;

	if (format[curr_i] != '.')
		return (-1); /* No precision specifier found */

	precision = -1; /* Initialize to -1 to detect errors */

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			if (precision < 0)
				precision = 0;
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			if (precision < 0)
				return (-1); /* Invalid precision value */
			break;
		}
		else if (format_specifier(format[curr_i]))
		{
			break; /* Precision specifier is complete */
		}
		else
		{
			return (-1); /* Invalid character in precision specifier */
		}
	}

	if (precision < 0)
		return (-1); /* Precision specifier not found or invalid */

	*i = curr_i - 1;

	return (precision);
}

