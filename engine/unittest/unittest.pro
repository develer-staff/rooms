TEMPLATE = subdirs

cppunit.subdir = ../lib/cppunit
cppunit.makefile = Makefile.cppunit

tests.subdir = tests
tests.depends = cppunit

SUBDIRS = cppunit tests
