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

PROGNAME=$(basename ${0})
VERSION="1.0"

COLOR_NONE="\033[0m"
COLOR_RED="\033[0;31m"

dir=$(dirname ${0})
prjdir="${dir}/.."

backdown="${prjdir}/backdown"
testsuite=$(find "${dir}"/markdown-testsuite -name "*.md")
ignorelist=()
case ${OSTYPE} in
  linux* )
    ignorelist+=("EOL-CR+LF.md")
    ignorelist+=("EOL-CR.md")
    ignorelist+=("list-code-1-space.md")
    ignorelist+=("ordered-list-inner-par-list.md")
    ;;
  darwin* )
    ignorelist+=("EOL-CR+LF.md")
    ignorelist+=("EOL-CR.md")
    ignorelist+=("list-code-1-space.md")
    ignorelist+=("ordered-list-inner-par-list.md")
    ;;
  windows* )
    ;;
esac

tmpdir="/tmp/backdown"
if [[ ! -d "${tmpdir}" ]]; then
  mkdir -p "${tmpdir}"
fi

verbose=0
noexit=0
for opt in ${*}
do
  case ${opt} in
    '--verbose')
      verbose=1
      ;;
    '-ne'|'--noexit')
      noexit=1
      ;;
    '--version')
      echo "${PROGNAME} ${VERSION}"
      exit 0
      ;;
  esac
  shift
done

success()
{
  echo -n "."
}

failure()
{
  echo -n -e ${COLOR_RED}"F"${COLOR_NONE}
  if [[ ${verbose} = 1 ]]; then
    echo ""
    echo -n -e "${COLOR_RED}Failed: "
    echo -e "${1}${COLOR_NONE}"
    echo "${2}"
  fi
}

echo "${testsuite}" | while read LINE
do
  skip=0
  name=$(basename ${LINE})
  for ignore in ${ignorelist[@]}
  do
    if [[ "${ignore}" = "${name}" ]]; then
      skip=1
    fi
  done
  if [[ ${skip} = 1 ]]; then
    continue
  fi
  result=$(${backdown} "${LINE}")
  expected=$(cat "${LINE%.*}.out")
  if [[ "${result}" = "${expected}" ]]; then
    success
  else
    restmp="${tmpdir}/${$}.result"
    exptmp="${tmpdir}/${$}.expected"
    echo "${result}" > "${restmp}"
    echo "${expected}" > "${exptmp}"
    res=$(diff -u "${restmp}" "${exptmp}")
    if [[ ${?} = 0 ]]; then
      success
    else
      failure "${LINE}" "${res}"
      if [[ ! ${noexit} = 1 ]]; then
        echo ""
        exit 1
      fi
    fi
  fi
done
echo ""
