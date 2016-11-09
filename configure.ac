AC_PREREQ([2.69])
AC_INIT([ifacebind], [0.0.1], [support@nubolabs.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_GNU_SOURCE
AM_PROG_AR

AC_DISABLE_STATIC

# Checks for libraries.
AC_CHECK_LIB([dl], [dlsym])

LT_INIT([disable-static])
AC_SUBST([LIBTOOL_DEPS])

AC_CONFIG_MACRO_DIR([m4])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h stdlib.h string.h sys/socket.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([inet_ntoa])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
