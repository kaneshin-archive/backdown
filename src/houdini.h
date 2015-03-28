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

#ifndef HOUDINI_H__
#define HOUDINI_H__

#include "common.h"
#include "buffer.h"

EXTERN_C_BEGIN

#ifdef HOUDINI_USE_LOCALE
#	define _isxdigit(c) isxdigit(c)
#	define _isdigit(c) isdigit(c)
#else
/*
 * Helper _isdigit methods -- do not trust the current locale
 * */
#	define _isxdigit(c) (strchr("0123456789ABCDEFabcdef", (c)) != NULL)
#	define _isdigit(c) ((c) >= '0' && (c) <= '9')
#endif

extern void houdini_escape_html(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_html0(struct buf *ob, const uint8_t *src, size_t size, int secure);
extern void houdini_unescape_html(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_xml(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_uri(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_url(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_href(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_unescape_uri(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_unescape_url(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_js(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_unescape_js(struct buf *ob, const uint8_t *src, size_t size);

EXTERN_C_END

#endif
