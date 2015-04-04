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

#ifndef STACK_H__
#define STACK_H__

#include "common.h"

EXTERN_C_BEGIN

typedef enum {
	BD_STACK_SUCCESS,
	BD_STACK_FAILURE,
} bd_stack_status;

struct stack {
	void **item;
	size_t size;
	size_t asize;
};
typedef struct stack bd_stack;

/*
 * Instantiate a new stack.
 */
bd_stack *bd_stack_new();

/*
 * Initialize the stack with size.
 */
bd_stack_status bd_stack_init(bd_stack *, size_t);

/*
 * Release the stack.
 */
void bd_stack_free(bd_stack *);

/*
 * Reset the stack to reuse.
 */
void bd_stack_reset(bd_stack *);

/*
 * Resize the stack with size.
 */
bd_stack_status bd_stack_grow(bd_stack *, size_t);

/*
 * Insert the item at the top of the stack.
 */
bd_stack_status bd_stack_push(bd_stack *, void *);

/*
 * Draw the item from the top of the stack.
 * The item will be removed.
 */
void *bd_stack_pop(bd_stack *);

/*
 * Return the item from the top of the stack.
 */
void *bd_stack_top(bd_stack *);

EXTERN_C_END

#endif

/* vim:set ts=4 sts=4 sw=4 noet: */
