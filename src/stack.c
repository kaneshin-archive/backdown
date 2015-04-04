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

#include "stack.h"

#include <stdlib.h>
#include <string.h>

bd_stack *
bd_stack_new()
{
	bd_stack *ret;
	ret = (bd_stack *)malloc(sizeof(bd_stack));

	if (NULL != ret)
		bd_stack_init(ret, 0);

	return ret;
}

bd_stack_status
bd_stack_init(bd_stack *st, size_t initial_size)
{
	if (NULL == st)
		return BD_STACK_FAILURE;

	st->item = NULL;
	st->size = 0;
	st->asize = 0;

	if (!initial_size)
		initial_size = 8;

	return bd_stack_grow(st, initial_size);
}

void
bd_stack_free(bd_stack *st)
{
	if (NULL == st)
		return;

	bd_stack_reset(st);

	free(st);
	st = NULL;
}

void
bd_stack_reset(bd_stack *st)
{
	if (NULL == st)
		return;

	if (NULL != st->item)
	{
		free(st->item);
		st->item = NULL;
	}

	st->size = 0;
	st->asize = 0;
}

bd_stack_status
bd_stack_grow(bd_stack *st, size_t new_size)
{
	void **new_st;

	if (st->asize >= new_size)
		return BD_STACK_SUCCESS;

	new_st = realloc(st->item, new_size * sizeof(void *));
	if (NULL == new_st)
		return BD_STACK_FAILURE;

	memset(new_st + st->asize, 0x0,
		(new_size - st->asize) * sizeof(void *));

	st->item = new_st;
	st->asize = new_size;

	if (st->size > new_size)
		st->size = new_size;

	return BD_STACK_SUCCESS;
}

bd_stack_status
bd_stack_push(bd_stack *st, void *item)
{
	if (BD_STACK_SUCCESS != bd_stack_grow(st, st->size * 2))
		return BD_STACK_FAILURE;

	st->item[st->size++] = item;
	return BD_STACK_SUCCESS;
}

void *
bd_stack_pop(bd_stack *st)
{
	if (!st->size)
		return NULL;

	return st->item[--st->size];
}

void *
bd_stack_top(bd_stack *st)
{
	if (!st->size)
		return NULL;

	return st->item[st->size - 1];
}

/* vim:set ts=4 sts=4 sw=4 noet: */
