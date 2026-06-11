#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libfdatetime/.libs/libfdatetime.1.dylib && test -f ./pyfdatetime/.libs/pyfdatetime.so
then
	install_name_tool -change /usr/local/lib/libfdatetime.1.dylib ${PWD}/libfdatetime/.libs/libfdatetime.1.dylib ./pyfdatetime/.libs/pyfdatetime.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

