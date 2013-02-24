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
	/bin/rm -f libfdatetime.h
	/bin/rm -f libfdatetime/definitions.h
	/bin/rm -f libfdatetime/features.h
	/bin/rm -f libfdatetime/types.h
	/bin/rm -f Makefile

