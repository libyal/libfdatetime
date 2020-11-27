#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libfdatetime/.libs/libfdatetime.1.dylib && test -f ./pyfdatetime/.libs/pyfdatetime.so;
then
	install_name_tool -change /usr/local/lib/libfdatetime.1.dylib ${PWD}/libfdatetime/.libs/libfdatetime.1.dylib ./pyfdatetime/.libs/pyfdatetime.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

