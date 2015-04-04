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

#ifndef __BD_AUTOLINK_H__
#define __BD_AUTOLINK_H__

#include "common.h"
#include "buffer.h"

EXTERN_C_BEGIN

typedef enum {
	BD_AUTOLINK_DEFAULT         = 0,
	BD_AUTOLINK_SHORT_DOMAINS   = 1 << 0,
} bd_autolink_flags;

int bd_autolink_issafe(const uint8_t *data, size_t size);

size_t bd_autolink__www(size_t *rewind_p, bd_buf *link,
	uint8_t *data, size_t offset, size_t size, bd_autolink_flags flags);
size_t bd_autolink__email(size_t *rewind_p, bd_buf *link,
	uint8_t *data, size_t offset, size_t size, bd_autolink_flags flags);
size_t bd_autolink__url(size_t *rewind_p, bd_buf *link,
	uint8_t *data, size_t offset, size_t size, bd_autolink_flags flags);

EXTERN_C_END

#endif

// vim:set ts=4 sts=4 sw=4 noet:
