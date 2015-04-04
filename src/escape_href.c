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

/*
 * The following characters will not be escaped:
 *
 *              -_.+!*'(),%#@?=;:/,+&$ alphanum
 *
 * Note that this character set is the addition of:
 *
 *      - The characters which are safe to be in an URL
 *      - The characters which are *not* safe to be in
 *      an URL because they are RESERVED characters.
 *
 * We asume (lazily) that any RESERVED char that
 * appears inside an URL is actually meant to
 * have its native function (i.e. as an URL 
 * component/separator) and hence needs no escaping.
 *
 * There are two exceptions: the chacters & (amp)
 * and ' (single quote) do not appear in the table.
 * They are meant to appear in the URL as components,
 * yet they require special HTML-entity escaping
 * to generate valid HTML markup.
 *
 * All other characters will be escaped to %XX.
 *
 */
static const uint8_t HREF_ESCAPE_TABLE[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void
bd_escape_href(bd_buf *ob, const uint8_t *src, size_t size)
{
	static const char hex_chars[] = "0123456789ABCDEF";
	size_t  i = 0, org;
	char hex_str[3];

	bufgrow(ob, BD_ESCAPE_FACTOR(size));
	hex_str[0] = '%';

	for (org = i; i < size; org = ++i)
	{
		while (i < size && HREF_ESCAPE_TABLE[src[i]] != 0)
			i++;

		if (i > org)
			bufput(ob, src + org, i - org);

		/* escaping */
		if (i >= size)
			break;

		switch (src[i]) {
		case '&': 
			/* amp appears all the time in URLs, but needs
			 * HTML-entity escaping to be inside an href */
		case '\'':
			/* the single quote is a valid URL character
			 * according to the standard; it needs HTML
			 * entity escaping too */
			bufputs(ob, BD_HTML_ESCAPES[BD_HTML_ESCAPE_TABLE[src[i]]]);
			break;
		default:
			/* every other character goes with a %XX escaping */
			hex_str[1] = hex_chars[(src[i] >> 4) & 0xF];
			hex_str[2] = hex_chars[src[i] & 0xF];
			bufput(ob, hex_str, 3);
		}
	}
}

// vim:set ts=4 sts=4 sw=4 noet:
