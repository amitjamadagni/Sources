ACLOCAL_AMFLAGS = -I ../m4

noinst_LTLIBRARIES = libnumeric.la
### libnumericdir = $(libdir)/singular

AM_CPPFLAGS = -I${top_srcdir} -I${top_builddir} -I${top_srcdir}/libpolys -I${top_builddir}/libpolys ${GMP_CFLAGS} -I${top_srcdir}/factory/include -I${top_builddir}/factory/include ${FACTORY_CFLAGS} ${NTL_CFLAGS}

libnumeric_la_SOURCES   = mpr_base.cc mpr_inout.cc mpr_numeric.cc

### libnumeric_la_LIBADD = ${top_builddir}/kernel/libkernel.la 
### ${top_builddir}/libpolys/polys/libpolys.la

### libnumeric_la_LDFLAGS    = -release ${PACKAGE_VERSION}

libnumeric_la_includedir  =$(includedir)/singular/numeric
libnumeric_la_include_HEADERS = mpr_base.h mpr_inout.h mpr_numeric.h



