#!/bin/bash
#
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

cd $(dirname "${0}")

backdown=./../backdown
testsuite=$(find ./markdown-testsuite -name "*.md")

echo "${testsuite}" | while read LINE
do
  result=$(${backdown} "${LINE}")
  expected=$(cat "${LINE%.*}.out")
  if [[ $result = $expected ]]; then
    echo -n "."
  else
    rf=tmp1.out
    ef=tmp2.out
    echo "${result}" > "${rf}"
    echo "${expected}" > "${ef}"
    res=$(diff -u "${rf}" "${ef}")
    ret=$?
    rm -rf "${rf}" "${ef}"
    if [[ ! ${ret} = 0 ]] ; then
      echo ""
      echo "Failed: " "${LINE}"
      echo "${res}"
      # exit 1
    fi
  fi
done

