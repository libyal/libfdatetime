include_HEADERS = \
	libfdatetime.h

pkginclude_HEADERS = \
	libfdatetime/definitions.h \
	libfdatetime/error.h \
	libfdatetime/extern.h \
	libfdatetime/features.h \
	libfdatetime/types.h

EXTRA_DIST = \
	libfdatetime.h.in \
	libfdatetime/definitions.h.in \
	libfdatetime/features.h.in \
	libfdatetime/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libfdatetime.h
	-rm -f libfdatetime/definitions.h
	-rm -f libfdatetime/features.h
	-rm -f libfdatetime/types.h
	-rm -f Makefile

