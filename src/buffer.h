/*
 * Copyright (c) 2008, Natacha Porté
 * Copyright (c) 2011, Vicent Martí
 * Copyright (c) 2015, Shintaro Kaneko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __BD_BUFFER_H__
#define __BD_BUFFER_H__

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

#include "common.h"

EXTERN_C_BEGIN

#if defined(_MSC_VER)
#define __attribute__(x)
#define inline
#endif

typedef enum {
	BUF_OK = 0,
	BUF_ENOMEM = -1,
} buferror_t;

/* struct buf: character array buffer */
typedef struct buf {
	uint8_t *data;		/* actual character data */
	size_t size;	/* size of the string */
	size_t asize;	/* allocated size (0 = volatile buffer) */
	size_t unit;	/* reallocation unit size (0 = read-only buffer) */
} bd_buf;

/* CONST_BUF: global buffer from a string litteral */
#define BUF_STATIC(string) \
	{ (uint8_t *)string, sizeof string -1, sizeof string, 0, 0 }

/* VOLATILE_BUF: macro for creating a volatile buffer on the stack */
#define BUF_VOLATILE(strname) \
	{ (uint8_t *)strname, strlen(strname), 0, 0, 0 }

/* BUFPUTSL: optimized bufputs of a string litteral */
#define BUFPUTSL(output, literal) \
	bufput(output, literal, sizeof literal - 1)

/* bufgrow: increasing the allocated size to the given value */
int bufgrow(struct buf *, size_t);

/* bufnew: allocation of a new buffer */
struct buf *bufnew(size_t) __attribute__ ((malloc));

/* bufnullterm: NULL-termination of the string array (making a C-string) */
const char *bufcstr(struct buf *);

/* bufprefix: compare the beginning of a buffer with a string */
int bufprefix(const struct buf *buf, const char *prefix);

/* bufput: appends raw data to a buffer */
void bufput(struct buf *, const void *, size_t);

/* bufputs: appends a NULL-terminated string to a buffer */
void bufputs(struct buf *, const char *);

/* bufputc: appends a single char to a buffer */
void bufputc(struct buf *, int);

/* bufrelease: decrease the reference count and free the buffer if needed */
void bufrelease(struct buf *);

/* bufreset: frees internal data of the buffer */
void bufreset(struct buf *);

/* bufslurp: removes a given number of bytes from the head of the array */
void bufslurp(struct buf *, size_t);

/* bufprintf: formatted printing to a buffer */
void bufprintf(struct buf *, const char *, ...) __attribute__ ((format (printf, 2, 3)));

EXTERN_C_END

#endif

// vim:set ts=4 sts=4 sw=4 noet:
