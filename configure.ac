dnl configure.in, used by autoconf
dnl to create the configure script
dnl @(#) Thorsten Otto, 04.07.2002
dnl
dnl TODO: check for Roman-8 system charset on HPUX systems
dnl
AC_PREREQ(2.52)

AC_INIT(udo, 7.11, [http://bugs.udo-open-source.org/],,[http://www.udo-open-source.org/])
AC_CONFIG_SRCDIR(src/udo.c)

AC_CONFIG_MACRO_DIR([m4])

###############################################################################
#
#       Autoheader stuff
#
###############################################################################

AH_TOP([
#ifndef __AUTOCONFIG_H__
#define __AUTOCONFIG_H__
])

AH_BOTTOM([
#endif /* __AUTOCONFIG_H__ */
])

AC_CANONICAL_HOST

if test "$ECHO_E" = ""; then
  ECHO_E="echo -e"
fi
AC_SUBST(ECHO_E)
AC_SUBST(RC_TARGET)

AC_CONFIG_HEADER(src/config.h:src/config_h.in)

AM_INIT_AUTOMAKE

m4_define([AC_ADD_CFLAG], [
for flag in $2; do
case " [$]$1 " in
"* $flag *") ;;
*) AC_MSG_CHECKING([whether the compiler understands] $flag)
   saved_$1="[$]$1"
   $1="[$]$1 $flag"
   AC_TRY_COMPILE(, , result=yes, $1="$saved_$1"; result=no)
   AC_MSG_RESULT([$result])
   ;;
esac
done
])

###############################################################################
#
#       Some utility functions to make checking for X things easier.
#
###############################################################################

# Like AC_CHECK_HEADER, but it uses the already-computed -I directories.
#
AC_DEFUN([AC_CHECK_X_HEADER], [
  ac_save_CPPFLAGS="$CPPFLAGS"
  if test \! -z "$includedir" ; then 
    CPPFLAGS="$CPPFLAGS -I$includedir"
  fi
  CPPFLAGS="$CPPFLAGS $X_CFLAGS"
  CPPFLAGS=`eval eval eval eval eval eval eval eval eval echo $CPPFLAGS`
  AC_CHECK_HEADERS([$1],[$2],[$3],[$4])
  CPPFLAGS="$ac_save_CPPFLAGS"])

# Like AC_EGREP_HEADER, but it uses the already-computed -I directories.
#
AC_DEFUN([AC_EGREP_X_HEADER], [
  ac_save_CPPFLAGS="$CPPFLAGS"
  if test \! -z "$includedir" ; then 
    CPPFLAGS="$CPPFLAGS -I$includedir"
  fi
  CPPFLAGS="$CPPFLAGS $X_CFLAGS"
  CPPFLAGS=`eval eval eval eval eval eval eval eval eval echo $CPPFLAGS`
  AC_EGREP_HEADER([$1], [$2], [$3], [$4])
  CPPFLAGS="$ac_save_CPPFLAGS"])

# Like AC_TRY_COMPILE, but it uses the already-computed -I directories.
#
AC_DEFUN([AC_TRY_X_COMPILE], [
  ac_save_CPPFLAGS="$CPPFLAGS"
  if test \! -z "$includedir" ; then 
    CPPFLAGS="$CPPFLAGS -I$includedir"
  fi
  CPPFLAGS="$CPPFLAGS $X_CFLAGS"
  CPPFLAGS=`eval eval eval eval eval eval eval eval eval echo $CPPFLAGS`
  AC_TRY_COMPILE([$1], [$2], [$3], [$4])
  CPPFLAGS="$ac_save_CPPFLAGS"])


# Like AC_CHECK_LIB, but it uses the already-computed -I and -L directories.
# Use this sparingly; it probably doesn't work very well on X programs.
#
AC_DEFUN([AC_CHECK_X_LIB], [
  ac_save_CPPFLAGS="$CPPFLAGS"
  ac_save_LDFLAGS="$LDFLAGS"
#  ac_save_LIBS="$LIBS"

  if test \! -z "$includedir" ; then 
    CPPFLAGS="$CPPFLAGS -I$includedir"
  fi
  # note: $X_CFLAGS includes $x_includes
  CPPFLAGS="$CPPFLAGS $X_CFLAGS"

  if test \! -z "$libdir" ; then
    LDFLAGS="$LDFLAGS -L$libdir"
  fi
  # note: $X_LIBS includes $x_libraries
  LDFLAGS="$LDFLAGS $X_LIBS $X_EXTRA_LIBS"

  CPPFLAGS=`eval eval eval eval eval eval eval eval eval echo $CPPFLAGS`
  LDFLAGS=`eval eval eval eval eval eval eval eval eval echo $LDFLAGS`
  AC_CHECK_LIB([$1], [$2], [$3], [$4], [$5])
  CPPFLAGS="$ac_save_CPPFLAGS"
  LDFLAGS="$ac_save_LDFLAGS"
#  LIBS="$ac_save_LIBS"
  ])


# Like AC_CHECK_FUNC, but uses additional header files for compiling
# (needed for the math functions, which are only correctly identified
# when including math.h)
# AC_CHECK_X_FUNCS(INCLUDES, FUNCTION..., [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
AC_DEFUN([AC_CHECK_X_FUNC],
[AS_VAR_PUSHDEF([ac_var], [ac_cv_func_$2])dnl
AC_CACHE_CHECK([for $2], ac_var,
[AC_LINK_IFELSE([AC_LANG_PROGRAM([[$1]], [[$2]])],
		[AS_VAR_SET(ac_var, yes)],
		[AS_VAR_SET(ac_var, no)])])
AS_IF([test AS_VAR_GET(ac_var) = yes], [$3], [$4])
AS_VAR_POPDEF([ac_var])dnl
])# AC_CHECK_X_FUNC


# Like AC_CHECK_X_FUNCS, but uses additional header files for compiling
# AC_CHECK_X_FUNCS(INCLUDES, FUNCTION..., [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
m4_define([_AH_CHECK_X_FUNCS],
[m4_foreach_w([AC_Func], [$1],
   [AH_TEMPLATE(AS_TR_CPP([HAVE_]m4_defn([AC_Func])),
      [Define to 1 if you have the `]m4_defn([AC_Func])[' function.])])])
AC_DEFUN([AC_CHECK_X_FUNCS],
[_AH_CHECK_X_FUNCS([$2])dnl
for ac_func in $2
do
AC_CHECK_X_FUNC([$1], $ac_func,
	      [AC_DEFINE_UNQUOTED(AS_TR_CPP([HAVE_$ac_func])) $3],
	      [$4], [$5])dnl
done
])


# Like AC_TRY_RUN, but it uses the already-computed -I directories.
# (But not the -L directories!)
#
AC_DEFUN([AC_TRY_X_RUN], [
  ac_save_CPPFLAGS="$CPPFLAGS"
  if test \! -z "$includedir" ; then 
    CPPFLAGS="$CPPFLAGS -I$includedir"
  fi
  CPPFLAGS="$CPPFLAGS $X_CFLAGS"
  AC_TRY_RUN([$1], [$2], [$3], [$4])
  CPPFLAGS="$ac_save_CPPFLAGS"])


# Usage: HANDLE_X_PATH_ARG([variable_name],
#                          [--command-line-option],
#                          [descriptive string])
#
# All of the --with options take three forms:
#
#   --with-foo (or --with-foo=yes)
#   --without-foo (or --with-foo=no)
#   --with-foo=/DIR
#
# This function, HANDLE_X_PATH_ARG, deals with the /DIR case.  When it sees
# a directory (string beginning with a slash) it checks to see whether
# /DIR/include and /DIR/lib exist, and adds them to $X_CFLAGS and $X_LIBS
# as appropriate.
#
AC_DEFUN([HANDLE_X_PATH_ARG], [
   case "$[$1]" in
    yes) ;;
    no)  ;;

    /*)
     AC_MSG_CHECKING([for [$3] headers])
     d=$[$1]/include
     if test -d $d; then
       X_CFLAGS="-I$d $X_CFLAGS"
       AC_MSG_RESULT([$d])
     else
       AC_MSG_RESULT([not found ($d: no such directory)])
     fi

     AC_MSG_CHECKING([for [$3] libs])
     d=$[$1]/lib
     if test -d $d; then
       X_LIBS="-L$d $X_LIBS"
       AC_MSG_RESULT([$d])
       if test -d "$d/pkgconfig" -a "$cross_compiling" = no; then
	      case :$PKG_CONFIG_PATH: in
	      *":$d:"*) ;;
	      *) PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$d" ;;
	      esac
       fi
     else
       AC_MSG_RESULT([not found ($d: no such directory)])
     fi

     # replace the directory string with "yes".
     [$1]_req="yes"
     [$1]=$[$1]_req
     ;;

    *)
     echo ""
     AC_MSG_ERROR([
argument to [$2] must be \"yes\", \"no\", or a directory.
If it is a directory, then \`DIR/include' will be added to
the -I list, and \`DIR/lib' will be added to the -L list.])
     ;;
   esac
  ])


###############################################################################
#
#       Function to figure out how to create directory trees.
#
###############################################################################

AC_DEFUN([AC_PROG_INSTALL_DIRS],
 [AC_CACHE_CHECK([whether "\${INSTALL} -d" creates intermediate directories],
    ac_cv_install_d_creates_dirs,
    [ac_cv_install_d_creates_dirs=no
     rm -rf conftestdir
     if mkdir conftestdir; then
       ${INSTALL} -d "conftestdir/dir1/dir2" >/dev/null 2>&1
       if test -d conftestdir/dir1/dir2/. ; then
         ac_cv_install_d_creates_dirs=yes
       fi
       rm -rf conftestdir
     fi
    ])

  if test "$ac_cv_install_d_creates_dirs" = no ; then
    AC_CACHE_CHECK([whether "mkdir -p" creates intermediate directories],
      ac_cv_mkdir_p_creates_dirs,
      [ac_cv_mkdir_p_creates_dirs=no
       rm -rf conftestdir
       if mkdir conftestdir; then
         mkdir -p conftestdir/dir1/dir2 >/dev/null 2>&1
         if test -d conftestdir/dir1/dir2/. ; then
           ac_cv_mkdir_p_creates_dirs=yes
         fi
         rm -rf conftestdir
       fi
      ])
  fi

  if test "$ac_cv_install_d_creates_dirs" = yes ; then
    INSTALL_DIRS='${INSTALL} -d'
  elif test "$ac_cv_mkdir_p_creates_dirs" = yes ; then
    INSTALL_DIRS='mkdir -p'
  else
    # any other ideas?
    INSTALL_DIRS='${INSTALL} -d'
  fi
])


###############################################################################
###############################################################################
#
#       End of function definitions.  Now start actually executing stuff.
#
###############################################################################
###############################################################################

# stuff for Makefiles
AC_PROG_INSTALL
AC_PROG_INSTALL_DIRS
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Support silent build rules, requires at least automake-1.11. Disable
# by either passing --disable-silent-rules to configure or passing V=1
# to make
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_PROG_CC
AC_EXEEXT
AC_C_CONST
AC_PROG_CC_C_O

###############################################################################
#
# Early compiler setup.
#
###############################################################################

TARGET_OS=unix
case $host in
  *-*-mingw*|*-*-msys*|*-*-MINGW*|*-*-MSYS*|*-*-cygwin*|*-*-CYGWIN*)
     test "$CC" = "" && CC=gcc
     test "$CXX" = "" && CXX="g++"
     for arg in -mms-bitfields -mno-cygwin -mwin32 -mthreads; do
        case $CC in
        *$arg*) ;;
        *) if $CC $arg -E - < /dev/null >/dev/null 2>&1; then
             echo adding $arg to $CC
             CC="$CC $arg"
             CXX="$CXX $arg"
           fi
        esac
     done
     TARGET_OS=win32
     CPPFLAGS="$CPPFLAGS -D_WIN32 -D__WIN32__"
     LIBS="-lole32"
     case $host in
  	x86_64-*-*) RC_TARGET=pe-x86-64 ;;
	*) RC_TARGET=pe-i386 ;;
     esac
     ;;
  *-apple-darwin* )
     test "$CC" = "" && CC=gcc
     test "$CXX" = "" && CXX="g++"
     for arg in -fwritable-strings; do
        case $CC in
        *$arg*) ;;
        *) if $CC $arg -E - < /dev/null >/dev/null 2>&1; then
             echo adding $arg to $CC
             CC="$CC $arg"
             CXX="$CXX $arg"
           fi
        esac
     done
     ECHO_E="echo"
     CPPFLAGS="$CPPFLAGS -D__MACOSX__"
     CFLAGS="$CFLAGS $CPROJECTFLAGS"
     LDFLAGS="$LDFLAGS $LDPROJECTFLAGS"
     ;;
  *-*-linux* )
     CPPFLAGS="$CPPFLAGS -D__LINUX__"
     ;;
  *-*-irix* )
     CPPFLAGS="$CPPFLAGS -D__IRIX__"
     ;;
  *-*-beos* )
     CPPFLAGS="$CPPFLAGS -D__BEOS__"
     ;;
  *-*-os2* )
     CPPFLAGS="$CPPFLAGS -D__OS2__"
     ;;
  *-*-amigaos )
     CPPFLAGS="$CPPFLAGS -D__AMIGA__"
     ;;
  *-*-sinix* )
     CPPFLAGS="$CPPFLAGS -D__SINIX__"
     ;;
  *-*-sunos* )
     CPPFLAGS="$CPPFLAGS -D__SUNOS__"
     ;;
  *-*-hpux* )
     CPPFLAGS="$CPPFLAGS -D__HPUX__"
     ;;
  *-*-nextstep* )
     CPPFLAGS="$CPPFLAGS -D__NEXTSTEP__"
     ;;
  m68k*-*-mint* | *-atarist-* )
     TARGET_OS=tos
     ;;
  *)
     CPPFLAGS="$CPPFLAGS -D__UNIX__"
     ;;
esac

if test "$cross_compiling" = no; then
  # do not consider this as a native build only because we can exec build programs;
  # it might just be a binfmt handler that makes this possible
  case $build in *-*-linux*)
     case $host in
     *-*-linux*) ;;
     *) cross_compiling=yes ;;
     esac
  esac
fi

AC_C_VA_COPY

AH_TEMPLATE([__HPUX_ROMAN8__], [use HP-Roman-8 character set on HPUX])
AH_TEMPLATE([__HPUX_ISO__], [use iso-latin1 character set on HPUX])

AC_ARG_ENABLE(roman-8,
[AC_HELP_STRING(--enable-roman-8, [use HP-Roman-8 character set on HPUX])],
[case $enableval in
yes) AC_DEFINE(__HPUX_ROMAN8__) ;;
no)  case $host in 
  *-hpux*) AC_DEFINE(__HPUX_ISO__) ;;
  esac
  ;;
*)   AC_MSG_ERROR([must be yes or no: --enable-roman-8=$enableval]) ;;
esac
])

AC_ARG_ENABLE(warnings,
[AC_HELP_STRING(--enable-warnings, [enable compiler warnings])],
[case $enableval in
yes)
     for arg in -Wall -W -Wstrict-prototypes -Wmissing-prototypes \
           -Wmissing-declarations -Wwrite-strings -Wbad-function-cast \
           -Wcast-qual -Wdeclaration-after-statement -Wundef
     do
         AC_ADD_CFLAG(CFLAGS, $arg)
     done
     ;;
no)  ;;
*)   AC_MSG_ERROR([must be yes or no: --enable-warnings=$enableval]) ;;
esac
])

AC_ARG_ENABLE(fatal-warnings,
[AC_HELP_STRING(--enable-fatal-warnings, [Turn compiler warnings into errors [default=disabled]])],
[case $enableval in
yes) enable_fatal_warnings=yes
     ;;
no)  enable_fatal_warnings=no
     ;;
*)   AC_MSG_ERROR([must be yes or no: --enable-fatal-warnings=$enableval]) ;;
esac
], [enable_fatal_warnings=no])

AH_TEMPLATE([UDO_INTEGRATED], [define to integrate UDO into the shell])
AC_ARG_ENABLE(integrate,
[AC_HELP_STRING(--enable-integrate, [integrate UDO into the shell])],
[case $enableval in
yes)
     udo_integrated=yes
     ;;
no)  udo_integrated=no ;;
*)   AC_MSG_ERROR([must be yes or no: --enable-warnings=$enableval]) ;;
esac
], [udo_integrated=yes])
if test "$udo_integrated" = yes; then
     AC_DEFINE([UDO_INTEGRATED])
fi
AM_CONDITIONAL(UDO_INTEGRATED, test "$udo_integrated" = yes)

AM_CONDITIONAL(OS_WIN32, test "$TARGET_OS" = "win32")
AM_CONDITIONAL(OS_TOS, test "$TARGET_OS" = "tos")
AM_CONDITIONAL(OS_UNIX, test "$TARGET_OS" = "unix")
AM_CONDITIONAL(CROSS_COMPILING, test "$cross_compiling" != no)

AC_CHECK_HEADERS([argz.h limits.h locale.h nl_types.h malloc.h string.h strings.h unistd.h process.h sys/param.h endian.h io.h fcntl.h dlfcn.h pwd.h wchar.h])

AC_CHECK_FUNCS([strcasecmp strncasecmp stricmp strnicmp strincmp strncmpi strlwr strupr tmpnam strerror sys_errlist mkstemp fdopen times])
AC_CHECK_FUNCS([getcwd munmap putenv setenv setlocale strchr])
AC_CHECK_FUNCS([sigaction syslog realpath setrlimit])
AC_CHECK_FUNCS([getuid geteuid getgid getegid getpid getppid lstat mkdir])



###############################################################################
#
#       Check for -lgtk (and Gnome stuff)
#
###############################################################################

AC_ARG_WITH(gui,[

User interface options:

]AC_HELP_STRING(--with-gui, [Select gui to use @<:@automatic@:>@])],
  [with_gui="$withval"],[with_gui=auto])
with_gui_req="$with_gui"

case $with_gui in
   auto)
      ;;
   win32)
      if test $TARGET_OS != win32; then
         AC_MSG_ERROR([win32 gui is only available for windows])
      fi
      ;;
   gem)
      if test $TARGET_OS != tos; then
         AC_MSG_ERROR([GEM gui is only available for TOS])
      fi
      ;;
   sdl|sdl2)
      ;;
   none)
      ;;
   gtk2|gtk3)
      ;;
   *) AC_MSG_ERROR([unsupported GUI $with_gui])
      ;;
esac


parse_gtk_version_string() {
  # M4 sucks!!
  changequote(X,Y)
  eval version_string='$ac_'$1'_version_string'
  maj=`echo $version_string | sed -n 's/\..*//p'`
  min=`echo $version_string | sed -n 's/[^.]*\.\([^.]*\).*/\1/p'`
  changequote([,])
  version=`echo "$maj * 1000 + $min" | bc`
  if test -z "$version"; then
    version=unknown
    version_string=unknown
  fi
  eval ac_$1_version=$version
  eval ac_$1_version_string=$version_string
}

# Find pkg-config... (need this for both gtk and gdk_pixbuf.)
# if the user specified --with-gtk=/foo/ then look there.
#
gtk_path="$PATH"
if test ! -z "$gtk_dir"; then
  # canonicalize slashes.
  foo=`echo "${gtk_dir}/bin" | sed 's@//*@/@g'`
  gtk_path="$foo:$gtk_path"
fi

AC_PATH_PROGS(pkg_config, pkg-config,, $gtk_path)

if test -z "$pkg_config" ; then
  AC_MSG_WARN([pkg-config not found!])
  pkg_config="false"
fi
#
# do not trust pkg-config when cross-compiling,
# unless PKG_CONFIG_LIBDIR was set up to
# point to the correct path
if test "$cross_compiling" != no -a "$PKG_CONFIG_LIBDIR" = ""; then
  pkg_config=false
fi


# Utility function for running pkg-config-based tests...
#
pkgs=''
pkg_check_version() {
  vers=""
  if test "$ok" = yes ; then
    req="$1"
    min="$2"
    AC_MSG_CHECKING(for $req)
    if $pkg_config --exists "$req" ; then
      vers=`$pkg_config --modversion "$req"`
      if $pkg_config --exists "$req >= $min" ; then
        AC_MSG_RESULT([$vers])
        pkgs="$pkgs $req"
        return 0
      else
        AC_MSG_RESULT([$vers (wanted >= $min)])
        ok=no
        return 1
      fi
    else
      AC_MSG_RESULT([no])
      ok=no
      return 1
    fi
  fi
  return 1
}


AH_TEMPLATE([HAVE_GTK],[Define this if you have Gtk (any version.)])
AH_TEMPLATE([HAVE_GTK2],[Define this if you have Gtk 2.x.])
AH_TEMPLATE([HAVE_GTK3],[Define this if you have Gtk 3.x.])
AH_TEMPLATE([HAVE_XML],[Define this if you have the XML library.])
AH_TEMPLATE([HAVE_GTKHTML], [Define this if you have the GtkHtml library.])
AH_TEMPLATE([HAVE_GTKHTML2], [Define this if you have the GtkHtml2 library.])
AH_TEMPLATE([HAVE_GDK_PIXBUF],
	    [Define this if you have the GDK_Pixbuf library installed.])
AH_TEMPLATE([HAVE_SOUP], [Define this if you have the Soup library.])
AH_TEMPLATE([HAVE_NEWSOUP], [Define this if you have the Soup library and it has cookies support.])


  have_soup="no"
  ok="yes"
  pkgs=''
  pkg_check_version      libsoup-2.4  2.26.0
  have_newsoup="$ok"
  have_soup="$ok"
  if test "$have_soup" = "no"; then
    ok="yes"
    pkgs=''
    pkg_check_version      libsoup-2.4  2.0.0
  fi
  soup_pkgs=$pkgs

  if test "$have_soup" = yes; then
    AC_CACHE_CHECK([for Soup includes], ac_cv_soup_config_cflags,
                   [ac_cv_soup_config_cflags=`$pkg_config --cflags $soup_pkgs`])
    AC_CACHE_CHECK([for Soup libs], ac_cv_soup_config_libs,
                   [ac_cv_soup_config_libs=`$pkg_config --libs $soup_pkgs`])
      ac_save_LDFLAGS="$LDFLAGS"
      ac_save_CFLAGS="$CFLAGS"
      CFLAGS="$CFLAGS  $ac_cv_soup_config_cflags"
      LDFLAGS="$LDFLAGS $ac_cv_soup_config_libs"
      AC_TRY_LINK([#include <libsoup/soup.h>],
                  [soup_session_async_new();],
                  ,
                  [have_soup=no],
                  [have_soup=no])
      LDFLAGS=$ac_save_LDFLAGS
      CFLAGS=$ac_save_CFLAGS
  fi

  if test "$have_soup" = yes; then
    AC_DEFINE(HAVE_SOUP)
    SOUP_CFLAGS="$SOUP_CFLAGS $ac_cv_soup_config_cflags"
    SOUP_LIBS="$SOUP_LIBS $ac_cv_soup_config_libs"
  fi
  if test "$have_newsoup" = yes; then
    AC_DEFINE(HAVE_NEWSOUP)
  fi
AM_CONDITIONAL(HAVE_SOUP, test x$have_soup != xno)
AM_CONDITIONAL(HAVE_NEWSOUP, test x$have_newsoup != xno)


have_gtk2=no
have_gtk3=no
jurassic_gtk=no
gtk_halfassed=no
have_gdk_pixbuf=no
have_gtkhtml=no
have_gtkhtml2=no
ac_atk_version="unknown"


if test "$with_gui" = gtk2 -o "$with_gui" = gtk3 -o "$with_gui" = auto; then
  ok="yes"
  gtk2_min_version="2.16.0"
  pkgs=''
  pkg_check_version         gmodule-2.0  2.0.0
  pkg_check_version         gthread-2.0  2.0.0
  if test "$TARGET_OS" = "unix"; then
  pkg_check_version         gio-unix-2.0 2.0.0
  fi
  glib2_pkgs=$pkgs
  pkg_check_version         gtk+-2.0     $gtk2_min_version  ; ac_gtk2_version_string="$vers"
  #
  # pango >= 1.31 does not support pangox any longer, so do not require it
  #
  have_gtk2="$ok"
  # but check for it anyways
  if test "$with_x" != no; then
    pkg_check_version       pangox       1.10.0
  fi
  if test "$with_quartz" = yes; then
    pkg_check_version       pangoft2     1.10.0
  fi
  if $pkg_config --exists pango ">=" 1.31.5; then
    pkg_check_version       harfbuzz     0.9.4
  fi
  ok="yes"
  pkg_check_version         gdk-pixbuf-2.0  2.0.0
  have_gdk_pixbuf=$ok
  gtk2_pkgs=$pkgs

  if test "$have_gtk2" = no; then
    if test -n "$ac_gtk2_version_string" ; then
      if test "$req" = "gtk+-2.0"; then
        if $pkg_config --exists gtk+-2.0; then
          jurassic_gtk=yes
        fi
      else
        gtk_halfassed="$ac_gtk2_version_string"
        gtk_halfassed_lib="$req"
      fi
    fi
  else
    parse_gtk_version_string gtk2
    jurassic_gtk=no
  fi

  ok="yes"
  gtk3_min_version="2.90.6"
  pkgs=''
  pkg_check_version         gmodule-2.0  2.0.0
  pkg_check_version         gthread-2.0  2.0.0
  if test "$TARGET_OS" = "unix"; then
  pkg_check_version         gio-unix-2.0 2.0.0
  fi
  glib3_pkgs=$pkgs
  pkg_check_version         gtk+-3.0     $gtk3_min_version  ; ac_gtk3_version_string="$vers"
  #
  # pango >= 1.31 does not support pangox any longer, so do not require it
  #
  have_gtk3="$ok"
  # but check for it anyways
  if test "$with_x" != no; then
    pkg_check_version       pangox       1.10.0
  fi
  if test "$with_quartz" = yes; then
    pkg_check_version       pangoft2     1.10.0
  fi
  if $pkg_config --exists pango ">=" 1.31.5; then
    pkg_check_version       harfbuzz     0.9.4
  fi
  ok="yes"
  pkg_check_version         gdk-pixbuf-2.0  2.0.0
  have_gdk_pixbuf=$ok
  gtk3_pkgs=$pkgs

  if test "$have_gtk3" = no; then
    if test -n "$ac_gtk3_version_string" ; then
      if test "$req" = "gtk+-3.0"; then
        if $pkg_config --exists gtk+-3.0; then
          jurassic_gtk=yes
        fi
      else
        gtk_halfassed="$ac_gtk3_version_string"
        gtk_halfassed_lib="$req"
      fi
    fi
  else
    parse_gtk_version_string gtk3
    jurassic_gtk=no
  fi

  if test "$have_gtk2" = yes; then
    if test "$with_gui" = auto -o "$with_gui" = gtk2; then
      gtk_pkgs="$gtk2_pkgs"
      glib_pkgs="$glib2_pkgs"
      with_gui=gtk2
      gtk_version=$ac_gtk2_version
      gui_version=$ac_gtk2_version_string
    fi
  fi
  if test "$have_gtk3" = yes; then
    if test "$with_gui" = auto -o "$with_gui" = gtk3; then
      gtk_pkgs="$gtk3_pkgs"
      glib_pkgs="$glib3_pkgs"
      with_gui=gtk3
      gtk_version=$ac_gtk3_version
      gui_version=$ac_gtk3_version_string
    fi
  fi

  if test "$with_gui" = gtk2; then
  ok="yes"
  pkgs=''
  pkg_check_version      libgtkhtml-2.0  2.0.0
  have_gtkhtml="$ok"
  gtkhtml_pkgs=$pkgs
  if test "$have_gtkhtml" = yes; then
    AC_CACHE_CHECK([for GtkHtml includes], ac_cv_gtkhtml_config_cflags,
                   [ac_cv_gtkhtml_config_cflags=`$pkg_config --cflags $gtkhtml_pkgs`])
    AC_CACHE_CHECK([for GtkHtml libs], ac_cv_gtkhtml_config_libs,
                   [ac_cv_gtkhtml_config_libs=`$pkg_config --libs $gtkhtml_pkgs`])
      ac_save_LDFLAGS="$LDFLAGS"
      ac_save_CFLAGS="$CFLAGS"
      CFLAGS="$CFLAGS  $ac_cv_gtkhtml_config_cflags"
      LDFLAGS="$LDFLAGS $ac_cv_gtkhtml_config_libs"
      AC_TRY_LINK([#include <libgtkhtml/gtkhtml.h>],
                  [html_document_new();],
                  ,
                  [have_gtkhtml=no],
                  [have_gtkhtml=no])
      LDFLAGS=$ac_save_LDFLAGS
      CFLAGS=$ac_save_CFLAGS
  fi

  # STFU gtkhtml2 installs pkgconfig files with version numbers
  ok="yes"
  pkgs=''
  pkg_check_version      libgtkhtml-3.14  2.0.0
  have_gtkhtml2="$ok"
  gtkhtml2_pkgs=$pkgs

  if test "$have_gtkhtml2" = yes; then
    AC_CACHE_CHECK([for GtkHtml2 includes], ac_cv_gtkhtml2_config_cflags,
                   [ac_cv_gtkhtml2_config_cflags=`$pkg_config --cflags $gtkhtml2_pkgs`])
    AC_CACHE_CHECK([for GtkHtml2 libs], ac_cv_gtkhtml2_config_libs,
                   [ac_cv_gtkhtml2_config_libs=`$pkg_config --libs $gtkhtml2_pkgs`])
      ac_save_LDFLAGS="$LDFLAGS"
      ac_save_CFLAGS="$CFLAGS"
      CFLAGS="$CFLAGS  $ac_cv_gtkhtml2_config_cflags"
      LDFLAGS="$LDFLAGS $ac_cv_gtkhtml2_config_libs"
      AC_TRY_LINK([#include <gtkhtml/gtkhtml.h>],
                  [gtk_html_new();],
                  ,
                  [have_gtkhtml2=no],
                  [have_gtkhtml2=no])
      LDFLAGS=$ac_save_LDFLAGS
      CFLAGS=$ac_save_CFLAGS
  fi
  fi

  if test "$have_gtk2" = yes -o "$have_gtk3" = yes; then
    AC_CACHE_CHECK([for Gtk includes], ac_cv_gtk_config_cflags,
                   [ac_cv_gtk_config_cflags=`$pkg_config --cflags $gtk_pkgs`])
    AC_CACHE_CHECK([for Gtk libs], ac_cv_gtk_config_libs,
                   [ac_cv_gtk_config_libs=`$pkg_config --libs $gtk_pkgs`])
    AC_CACHE_CHECK([for GLib includes], ac_cv_glib_config_cflags,
                   [ac_cv_glib_config_cflags=`$pkg_config --cflags $glib_pkgs`])
    AC_CACHE_CHECK([for GLib libs], ac_cv_glib_config_libs,
                   [ac_cv_glib_config_libs=`$pkg_config --libs $glib_pkgs`])
    # ATK does not define a version number in public headers,
    # so grab it now from pkg-config
    # (it it only used for information and not checked anywhere)
    AC_CACHE_CHECK([for ATK version], ac_cv_atk_version,
                   [ac_cv_atk_version=`$pkg_config --modversion atk`])
    # maybe require atk 1.20? versions before do not have atk_get_version()
  fi
  ac_gtk_config_cflags=$ac_cv_gtk_config_cflags
  ac_gtk_config_libs=$ac_cv_gtk_config_libs
  ac_glib_config_cflags=$ac_cv_glib_config_cflags
  ac_glib_config_libs=$ac_cv_glib_config_libs
  ac_atk_version=$ac_cv_atk_version
  
  GTK_DATADIR=""
  if test "$with_gui" = gtk3; then
    GTK_DATADIR=`$pkg_config --variable=prefix gtk+-3.0`
    GTK_DATADIR="$GTK_DATADIR/share"
  elif test "$with_gui" = gtk2; then
    GTK_DATADIR=`$pkg_config --variable=prefix gtk+-2.0`
    GTK_DATADIR="$GTK_DATADIR/share"
  fi

  if test "$with_gui" = gtk3 -o "$with_gui" = gtk2; then
    INCLUDES="$INCLUDES $ac_gtk_config_cflags"
    GTK_CFLAGS="$GTK_CFLAGS $ac_gtk_config_cflags"
    GTK_LIBS="$GTK_LIBS $ac_gtk_config_libs"
    GLIB_CFLAGS="$GLIB_CFLAGS $ac_glib_config_cflags"
    GLIB_LIBS="$GLIB_LIBS $ac_glib_config_libs"
    AC_DEFINE(HAVE_GTK)
    if test "$have_gtk2" = yes; then
      AC_DEFINE(HAVE_GTK2)
    fi
    if test "$have_gtk3" = yes; then
      AC_DEFINE(HAVE_GTK3)
    fi
    AC_DEFINE(HAVE_XML)
    if test "$have_gdk_pixbuf" = yes; then
      AC_DEFINE(HAVE_GDK_PIXBUF)
    fi
  fi
  if test "$have_gtkhtml2" = yes; then
    AC_DEFINE(HAVE_GTKHTML2)
    GTKHTML_CFLAGS="$GTKHTML_CFLAGS $ac_cv_gtkhtml2_config_cflags"
    GTKHTML_LIBS="$GTKHTML_LIBS $ac_cv_gtkhtml2_config_libs"
  elif test "$have_gtkhtml" = yes; then
    AC_DEFINE(HAVE_GTKHTML)
    GTKHTML_CFLAGS="$GTKHTML_CFLAGS $ac_cv_gtkhtml_config_cflags"
    GTKHTML_LIBS="$GTKHTML_LIBS $ac_cv_gtkhtml_config_libs"
  fi
  #
  # remove switches from GTKHTML_{CFLAGS|LIBS} that already
  # appear in GTK_{CFLAGS|LIBS}
  #
  tmp_flags=
  for p in $GTKHTML_CFLAGS; do
    case $p in
    -I* | -D*)
      case " ${GTK_CFLAGS} ${GLIB_CFLAGS} " in
      *" $p "*) ;;
      *) tmp_flags="$tmp_flags $p" ;;
      esac ;;
     *) tmp_flags="$tmp_flags $p" ;;
    esac
  done
  GTKHTML_CFLAGS="$tmp_flags"
  tmp_flags=
  for p in $GTKHTML_LIBS; do
    case $p in
    -L* | -l* | -mt|-mthreads|-kthread|-Kthread|-pthread|-pthreads|--thread-safe|-threads)
      case " ${GTK_LIBS} ${GLIB_LIBS} " in
      *" $p "*) ;;
      *) tmp_flags="$tmp_flags $p" ;;
      esac ;;
     *) tmp_flags="$tmp_flags $p" ;;
    esac
  done
  GTKHTML_LIBS="$tmp_flags"
fi
if test "$have_gtk2" = no -a "$with_gui" = gtk2; then
	AC_MSG_ERROR([*** GTK2 was requested, but was not found ***])
fi
if test "$have_gtk3" = no -a "$with_gui" = gtk3; then
	AC_MSG_ERROR([*** GTK3 was requested, but was not found ***])
fi

AM_CONDITIONAL(HAVE_GTK, test "$with_gui" = gtk2 -o "$with_gui" = gtk3)
AM_CONDITIONAL(HAVE_GTK2, test "$with_gui" = gtk2)
AM_CONDITIONAL(HAVE_GTK3, test "$with_gui" = gtk3)
AM_CONDITIONAL(HAVE_GTKHTML, test x$have_gtkhtml != xno)
AM_CONDITIONAL(HAVE_GTKHTML2, test x$have_gtkhtml2 != xno)

AC_DEFINE_UNQUOTED([ATK_VERSION_FROM_CONFIGURE], "$ac_atk_version", [The version of ATK])
ac_bz2_version=`bzip2 --version 2>&1 </dev/null | sed -n 's/.*Version \([[0-9]]*\.[[0-9]]*\.[[0-9]]*\).*/\1/p'`
if test "$ac_bz2_version" = ""; then ac_bz2_version="unknown"; fi
AC_DEFINE_UNQUOTED([BZ2_VERSION_FROM_CONFIGURE], "$ac_bz2_version", [The version of BZ2])

# Note that we don't define HAVE_GLIB even if it is available;
# there are several command line tools that only
# need a small subset of Glib (mainly memory functions),
# and we don't want to depend on Glib in that case.

###############################################################################
#
#       Gettext support
#
###############################################################################

AH_TEMPLATE([GETTEXT_PACKAGE], [define to the name of the gettext package])

AC_PROG_INTLTOOL
GETTEXT_PACKAGE=udo
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE")
AC_DEFINE_UNQUOTED(PACKAGE, "$GETTEXT_PACKAGE")
AC_SUBST(GETTEXT_PACKAGE)

ALL_LINGUAS="`grep -v '^#' "$srcdir/po/LINGUAS" | tr '\n' ' '`"
AC_SUBST([CONFIG_STATUS_DEPENDENCIES],['$(top_srcdir)/po/LINGUAS'])
AM_GLIB_GNU_GETTEXT
XGETTEXT="$XGETTEXT --from-code=UTF-8"
AM_GLIB_DEFINE_LOCALEDIR([LOCALEDIR])
MKINSTALLDIRS="$INSTALL_DIRS"
AC_SUBST(MKINSTALLDIRS)



AC_SUBST(GTK_LIBS)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GLIB_LIBS)
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(XML_LIBS)
AC_SUBST(GTKHTML_LIBS)
AC_SUBST(GTKHTML_CFLAGS)
AC_SUBST(SOUP_LIBS)
AC_SUBST(SOUP_CFLAGS)
AC_SUBST(JPEG_CFLAGS)
AC_SUBST(JPEG_LIBS)
AC_SUBST(PNG_CFLAGS)
AC_SUBST(PNG_LIBS)
AC_SUBST(XPM_LIBS)

AC_CONFIG_COMMANDS_PRE([
if test "$GCC" = "yes" -a "$enable_fatal_warnings" = "yes"; then
	CFLAGS="$CFLAGS -Werror"
	CXXFLAGS="$CXXFLAGS -Werror"
	OBJCFLAGS="$OBJCFLAGS -Werror"
fi
])

AC_CONFIG_COMMANDS([pofiles],[
	sed -e "/POTFILES =/r po/POTFILES" po/Makefile.in > po/Makefile
        sed -e "/POTFILES =/r udosh/po/POTFILES" udosh/po/Makefile.in > udosh/po/Makefile 
      ])

AC_OUTPUT([
	Makefile
	src/Makefile
	doc/Makefile
	doc/en/Makefile
	doc/de/Makefile
	udosh/Makefile
	udosh/win32/Makefile
	udosh/win32/res/Makefile
	udosh/win32/Manual/Makefile
	udosh/gtk/Makefile
	udosh/gtk/icons/Makefile
	udosh/gtk/Manual/Makefile
	udosh/gtk/Manual/de/Makefile
	udosh/gtk/Manual/en/Makefile
	po/Makefile.in
	udosh/po/Makefile.in
])
