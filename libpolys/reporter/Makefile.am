ACLOCAL_AMFLAGS = -I ../../m4

AM_CPPFLAGS = -I${top_srcdir} -I${top_srcdir}/.. -I${top_builddir} -I${top_builddir}/..  

noinst_LTLIBRARIES = libreporter.la 
#### libreporterdir = $(libdir)/singular

libreporter_la_SOURCES  = dError.cc reporter.cc
## libreporter_la_LDFLAGS  = -release ${PACKAGE_VERSION}
## libreporter_la_LIBADD   = ${top_builddir}/misc/libmisc.la

libreporter_la_includedir  =$(includedir)/singular/reporter
libreporter_la_include_HEADERS   = reporter.h 


