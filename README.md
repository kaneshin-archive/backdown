# Backdown

[![Build Status](https://travis-ci.org/backdown/backdown.svg?branch=master)](https://travis-ci.org/backdown/backdown)
[![Coverage Status](https://coveralls.io/repos/backdown/backdown/badge.svg?branch=master)](https://coveralls.io/r/backdown/backdown?branch=master)
[![Join the chat at https://gitter.im/backdown/backdown](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/backdown/backdown?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

`Backdown` is a Markdown parser based on the original code of the
[vmg/sundown](https://github.com/vmg/sundown) by Vicent Marti.

## Installation

- Dynamic Library
- Static Library
- Executable Files

Just type `make`.

## Features

*	**Fully standards compliant**

	`Backdown` passes out of the box the official Markdown v1.0.0 and v1.0.3
	test suites, and has been extensively tested with additional corner cases
	to make sure its output is as sane as possible at all times.

*	**Massive extension support**

	`Backdown` has optional support for several (unofficial) Markdown extensions,
	such as non-strict emphasis, fenced code blocks, tables, autolinks,
	strikethrough and more.

*	**UTF-8 aware**

	`Backdown` is fully UTF-8 aware, both when parsing the source document and when
	generating the resulting (X)HTML code.

*	**Tested & Ready to be used on production**

	`Backdown` has been extensively security audited, and includes protection against
	all possible DOS attacks (stack overflows, out of memory situations, malformed
	Markdown syntax...) and against client attacks through malicious embedded HTML.

	We've worked very hard to make `Backdown` never crash or run out of memory
	under *any* input. `Backdown` renders all the Markdown content in GitHub and so
	far hasn't crashed a single time.

*	**Customizable renderers**

	`Backdown` is not stuck with XHTML output: the Markdown parser of the library
	is decoupled from the renderer, so it's trivial to extend the library with
	custom renderers. A fully functional (X)HTML renderer is included.

*	**Optimized for speed**

	`Backdown` is written in C, with a special emphasis on performance. When wrapped
	on a dynamic language such as Python or Ruby, it has shown to be up to 40
	times faster than other native alternatives.

*	**Zero-dependency**

	`Backdown` is a zero-dependency library composed of 3 `.c` files and their headers.
	No dependencies, no bullshit. Only standard C99 that builds everywhere.

## Help us

`Backdown` is all about security. If you find a (potential) security vulnerability in the
library, or a way to make it crash through malicious input, please report it to us,
either directly via email or by opening an Issue on GitHub, and help make the web safer
for everybody.

## Unicode character handling

Given that the Markdown spec makes no provision for Unicode character handling, `Backdown`
takes a conservative approach towards deciding which extended characters trigger Markdown
features:

*	Punctuation characters outside of the U+007F codepoint are not handled as punctuation.
	They are considered as normal, in-word characters for word-boundary checks.

*	Whitespace characters outside of the U+007F codepoint are not considered as
	whitespace. They are considered as normal, in-word characters for word-boundary checks.

## License

[The MIT License (MIT)](http://kaneshin.mit-license.org/)

## Contributor

Shintaro Kaneko <kaneshin0120@gmail.com>

