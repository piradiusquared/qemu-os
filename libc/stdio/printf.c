#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* TODO: error checking, buffer overflow errors */
char *convert(int num, int base)
{
	static char rep[] = "0123456789ABCDEF";
	static char buffer[32];
	char *ptr = &buffer[31];

	*ptr = '\0';

	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num != 0);

	return (ptr);
}

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

/* TODO: track written chars, and add error checking */
int printf(const char* restrict format, ...)
{
	char *traverse; 
    char *s; /* string holder*/
    char *num; /* int/hex/oct holder */
	int val; /* Temp num holder as int type */

    va_list parameters;
    va_start(parameters, format);


	while (*format != '\0') {

		if (*format != '%') {
			putchar(*format);
			format++;
			continue;
		}

		format++; /* Move past the format specifier */

		switch (*format) {
		case 'c':
			val = va_arg(parameters, int);
        	putchar(val);
            break;

        case 's':
			s = va_arg(parameters, char *);
            printf(s, strlen(s));
            break;
		
		/* Numbers and stuff. TODO: floating points later */
		case 'd': { /* decimal rep */
			val = va_arg(parameters, int);
			if (val < 0) {
				val = -val;
            	putchar('-'); /* Negative value */
            }
			
			char *decimal = convert(val, 10); /* Decimal conversion*/
			print(decimal, strlen(decimal));
            break; 
		}

        case 'o': /* oct rep */
			val = va_arg(parameters, unsigned int);
			num = convert(val, 8);
			print(num, strlen(num));
			break;
			
		case 'x': /* hex rep */
			val = va_arg(parameters, unsigned int);
			num = convert(val, 16);
			print(num, strlen(num));
			break;
        }

		format++;
	}

    va_end(parameters);
	return (0);
}


// int printf(const char* restrict format, ...) {
// 	va_list parameters; /* Get a variable number of args like printing strings, chars*/
// 	va_start(parameters, format);

// 	int written = 0;

// 	while (*format != '\0') {
// 		size_t maxrem = INT_MAX - written;

// 		/* Enter if current is not % or next in line is % specifier */
// 		if (format[0] != '%' || format[1] == '%') {
// 			if (format[0] == '%')
// 				format++; /* Move pointer forward to next char*/
			
// 			size_t amount = 1;
// 			while (format[amount] && format[amount] != '%')
// 				amount++; /* Move forward until find another % or end of input */
			
// 			if (maxrem < amount) { /* Buffer overflow (printing over MAXINT) */
// 				// TODO: Set errno to EOVERFLOW.
// 				return -1;
// 			}

// 			if (!print(format, amount)) /* End of char to print*/
// 				return -1;
			
// 			format += amount; /* Update pointer and amount printed*/
// 			written += amount;
// 			continue;
// 		}

// 		const char* format_begun_at = format++;
		
// 		switch (*format) {
// 		case 'c': {
// 			format++;
// 			char c = (char) va_arg(parameters, int /* char promotes to int */);
// 			if (!maxrem) {
// 				// TODO: Set errno to EOVERFLOW.
// 				return -1;
// 			}

// 			if (!print(&c, sizeof(c))) /* Print single char*/
// 				return -1;

// 			written++;
// 			break;
// 		}

// 		case 's': {
// 			format++;
// 			const char* str = va_arg(parameters, const char*);
// 			size_t len = strlen(str);
// 			if (maxrem < len) {
// 				// TODO: Set errno to EOVERFLOW.
// 				return -1;
// 			}
// 			if (!print(str, len))
// 				return -1;
// 			written += len;
		
// 			break;
// 		}

// 		default: {
// 			format = format_begun_at;
// 			size_t length = strlen(format);
// 			if (maxrem < length) {
// 				// TODO: Set errno to EOVERFLOW.
// 				return -1;
// 			}
// 			if (!print(format, length))
// 				return -1;
// 			written += length;
// 			format += length;
// 		}

// 		}
// 	}

// 	va_end(parameters);
// 	return written;
// }
