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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "markdown.h"
#include "html.h"
#include "buffer.h"

#define READ_UNIT 1024
#define OUTPUT_UNIT 64

typedef enum bd_status
{
	BD_SUCCESS = 0,
	BD_FAILURE,

	BD_UNABLE_ALLOCATE_MEMORY,
	BD_UNABLE_OPEN_FILE,
} bd_status_t;

bd_status_t
bd_render(struct buf *ob, const struct buf *ib)
{
	struct sd_callbacks callbacks;
	struct html_renderopt options;
	struct sd_markdown *markdown;

	sdhtml_renderer(&callbacks, &options, 0);
	markdown = sd_markdown_new(0, 16, &callbacks, &options);
	sd_markdown_render(ob, ib->data, ib->size, markdown);
	sd_markdown_free(markdown);
	return BD_SUCCESS;
}

bd_status_t
bd_io(struct buf *ob, struct buf *ib, FILE *in)
{
	size_t nread;
	bd_status_t sts = BD_SUCCESS;

	bufgrow(ib, READ_UNIT);
	while ((nread = fread(ib->data + ib->size, 1, ib->asize - ib->size, in)) > 0)
	{
		ib->size += nread;
		bufgrow(ib, ib->size + READ_UNIT);
	}

	if ((sts = bd_render(ob, ib)) != BD_SUCCESS)
		return sts;

	if (ob->size != fwrite(ob->data, 1, ob->size, stdout))
		sts = BD_FAILURE;

	return sts;
}

void
bd_result(bd_status_t sts)
{
	switch (sts)
	{
		case BD_UNABLE_ALLOCATE_MEMORY:
			fprintf(stderr, "Unable to allocate memory\n");
		case BD_UNABLE_OPEN_FILE:
			fprintf(stderr, "Unable to open input file: %s\n", strerror(errno));
		default:
			;
	}
}

int
main(int argc, char **argv)
{
	int i;
	bd_status_t sts = BD_SUCCESS;
	struct buf *ib, *ob;
	FILE *in;

	/* performing markdown parsing */
	ib = bufnew(READ_UNIT);
	ob = bufnew(OUTPUT_UNIT);

	if (ib && ob)
	{
		if (argc <= 1)
			sts = bd_io(ob, ib, stdin);

		for (i = 1; i < argc && BD_SUCCESS == sts; ++i)
		{
			if ((in = fopen(argv[i], "r")))
			{
				sts = bd_io(ob, ib, in);
				fclose(in);
				/* reset buffet for next step */
				bufreset(ib);
				bufreset(ob);
			}
			else
			{
				sts = BD_UNABLE_OPEN_FILE;
			}
		}
	}
	else
	{
		sts = BD_UNABLE_ALLOCATE_MEMORY;
	}

	/* cleanup */
	bufrelease(ib);
	bufrelease(ob);

	/* result output with status */
	bd_result(sts);
	return sts;
}

