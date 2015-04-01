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

#include "escape.h"

void
bd_escape_html(bd_buf *ob, const uint8_t *src, size_t size, bd_escape_mode mode)
{
	size_t i = 0, org;

	bufgrow(ob, BD_ESCAPE_FACTOR(size));

	for (org = i; i < size; org = ++i)
	{
		while (i < size && BD_HTML_ESCAPE_TABLE[src[i]] == 0)
			i++;

		if (i > org)
			bufput(ob, src + org, i - org);

		/* escaping */
		if (i >= size)
			break;

		/* The forward slash is only escaped in secure mode */
		if (src[i] == '/' && mode == BD_ESCAPE_INSECURE)
			bufputc(ob, '/');
		else
			bufputs(ob, BD_HTML_ESCAPES[BD_HTML_ESCAPE_TABLE[src[i]]]);
	}
}

void
bd_escape_html_secure(bd_buf *ob, const uint8_t *src, size_t size)
{
	bd_escape_html(ob, src, size, BD_ESCAPE_SECURE);
}

void
bd_escape_html_insecure(bd_buf *ob, const uint8_t *src, size_t size)
{
	bd_escape_html(ob, src, size, BD_ESCAPE_INSECURE);
}
