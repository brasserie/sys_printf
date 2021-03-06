/**
BSD 3-Clause License

Copyright (c) 2018, Anthony Rabine
All rights reserved.
*/

#ifndef SYS_PRINT_H_
#define SYS_PRINT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#define PRINT_BUF_LEN 12 // the following should be enough for 32 bit int

typedef void (*putc_func)(const char c);

typedef struct
{
	uint32_t maxLen;
	uint32_t len;
	putc_func pPutc;

    // Private use, temp buffer for int to char
    // Some compilers are not C99, so cannot declare VLA
    char print_buf[PRINT_BUF_LEN];
} sys_print_ctx_t;

/**
 * @brief Generic printf() embedded implementation.
 * For a specific output (ie, display, Jtag, UART ...) give a proper function pointer that pushes only
 * one char to an output.
 *
 * Example of use, like a printf() function:
 * void my_printf(sys_print_ctx_t *ctx, const char *format, ...)
 * {
 *    int *varg = (int *) (&format);
 *    (void)system_printf (ctx, 0, varg);
 * }
 *
 * Example of a snprintf implementation:
 * int my_snprintf (sys_print_ctx_t *ctx, char *out, unsigned int buffer_len, const char *format, ...)
 * {
 *     int *varg = (int *) (&format);
 *    return system_printf (ctx, &out, varg);
 * }
 *
 * @param[in] ctx Context of the output
 * @param[out] out output memory or NULL
 * @param[in] arguments of the printf
 */
int sys_printf (sys_print_ctx_t *ctx, char **out, const char *fmt, va_list arg);


int sys_snprintf(char *out, uint32_t maxLen, const char *format, ...);

#endif /* SYS_PRINT_H_ */
