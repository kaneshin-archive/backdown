/*
 * Copyright (c) 2011, Vicent Marti
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

#ifndef __BD_ESCAPE_H__
#define __BD_ESCAPE_H__

#include "common.h"
#include "buffer.h"

EXTERN_C_BEGIN

#define BD_ESCAPE_FACTOR(x) (((x) * 12) / 10)
#define BD_UNESCAPE_FACTOR(x) (x)

/**
 * According to the OWASP rules:
 */
extern const uint8_t BD_HTML_ESCAPE_TABLE[];
extern const char *BD_HTML_ESCAPES[];

/**
 * Escape Mode
 */
typedef enum {
	BD_ESCAPE_SECURE,
	BD_ESCAPE_INSECURE,
} bd_escape_mode;

/*
 * Escape href
 */
void bd_escape_href(bd_buf *ob, const uint8_t *src, size_t size);

/*
 * Escape html
 */
void bd_escape_html(bd_buf *ob, const uint8_t *src, size_t size, bd_escape_mode mode);
void bd_escape_html_secure(bd_buf *ob, const uint8_t *src, size_t size);
void bd_escape_html_insecure(bd_buf *ob, const uint8_t *src, size_t size);

EXTERN_C_END

#endif

// vim:set ts=4 sts=4 sw=4 noet:
