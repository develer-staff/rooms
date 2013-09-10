MAKEFILE = Makefile.cppunit

PREFIX = $$PWD/../cppunit-build

Makefile.target = Makefile
Makefile.commands = ./configure "LDFLAGS=-ldl" --prefix=$${PREFIX}

all.commands = make && make install
all.depends = Makefile

TARGET = \\\

QMAKE_DISTCLEAN += Makefile
QMAKE_EXTRA_TARGETS += Makefile all
