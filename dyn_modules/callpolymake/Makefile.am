ACLOCAL_AMFLAGS = -I ../../m4

moduledir = $(libexecdir)/singular/MOD

if SING_HAVE_POLYMAKE
if ENABLE_P_PROCS_DYNAMIC
  module_LTLIBRARIES=polymake.la
endif
endif

# forcefully enable exceptions for polymake
POLYMAKE_CFLAGS = -fexceptions -frtti

AM_LDFLAGS	= ${PM_LDFLAGS}
# -release ${PACKAGE_VERSION}
  
SOURCES = polymake_conversion.cc polymake_documentation.cc polymake_wrapper.cc

CXXFLAGS += $(POLYMAKE_CXXFLAGS)

polymake_la_SOURCES = $(SOURCES)

MYINCLUDES = -I${top_srcdir} -I${top_builddir} -I${srcdir} \
-I${top_srcdir}/libpolys -I${top_builddir}/libpolys  \
-I${top_builddir}/factory/include $(GMP_CFLAGS) $(PM_INC) $(PM_CFLAGS) \
$(POLYMAKE_CFLAGS) $(FACTORY_CFLAGS)

P_PROCS_CPPFLAGS_COMMON = -DDYNAMIC_VERSION

polymake_la_CPPFLAGS = ${MYINCLUDES} ${P_PROCS_CPPFLAGS_COMMON} ${POLYMAKE_CFLAGS}
polymake_la_CXXFLAGS = ${POLYMAKE_CFLAGS}
polymake_la_CFLAGS = ${POLYMAKE_CFLAGS}

if ENABLE_P_PROCS_DYNAMIC
  P_PROCS_MODULE_LDFLAGS = ${AM_LDFLAGS} -shared -module
else
  P_PROCS_MODULE_LDFLAGS = ${AM_LDFLAGS}
endif

# Add under Mac OS X: -twolevel_namespace -weak_reference_mismatches weak -undefined dynamic_lookup
polymake_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGS}
polymake_la_LIBADD = ${PM_LIBS}
