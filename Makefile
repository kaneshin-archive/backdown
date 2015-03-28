# Copyright (c) 2009, Natacha Porté
# Copyright (c) 2011, Vicent Marti
# Copyright (c) 2015, Shintaro Kaneko
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

SRCDIR=src
SRCS=\
	$(SRCDIR)/houdini_href_e.c \
	$(SRCDIR)/houdini_html_e.c \
	$(SRCDIR)/html.c \
	$(SRCDIR)/html_smartypants.c \
	$(SRCDIR)/autolink.c \
	$(SRCDIR)/buffer.c \
	$(SRCDIR)/markdown.c \
	$(SRCDIR)/stack.c

CFLAGS=-c -g -O3 -fPIC -Wall -Werror -Wsign-compare -I$(SRCDIR)
LDFLAGS=-g -O3 -Wall -Werror
CC=gcc

OBJS = $(subst .c,.o,$(SRCS))

TARGET=backdown smartypants libbackdown.so html_blocks

.PHONY: all clean

all: $(TARGET)

# libraries

libbackdown.so: libbackdown.so.1
	ln -f -s $^ $@

libbackdown.so.1: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ -shared $^

# executables
backdown: backdown.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

smartypants: smartypants.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -I$(SRCDIR) $< -o $@

clean:
	rm -f *.o $(SRCDIR)/*.o $(TARGET) libbackdown*

# perfect hashing
html_blocks: src/html_blocks.h

src/html_blocks.h: html_block_names.txt
	gperf -N find_block_tag -H hash_block_tag -C -c -E --ignore-case $^ > $@

