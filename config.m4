dnl $Id$
dnl config.m4 for extension wing_sharememory

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(wing_sharememory, for wing_sharememory support,
dnl Make sure that the comment is aligned:
dnl [  --with-wing_sharememory             Include wing_sharememory support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(wing_sharememory, whether to enable wing_sharememory support,
dnl Make sure that the comment is aligned:
dnl [  --enable-wing_sharememory           Enable wing_sharememory support])

if test "$PHP_WING_SHAREMEMORY" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-wing_sharememory -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/wing_sharememory.h"  # you most likely want to change this
  dnl if test -r $PHP_WING_SHAREMEMORY/$SEARCH_FOR; then # path given as parameter
  dnl   WING_SHAREMEMORY_DIR=$PHP_WING_SHAREMEMORY
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for wing_sharememory files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       WING_SHAREMEMORY_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$WING_SHAREMEMORY_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the wing_sharememory distribution])
  dnl fi

  dnl # --with-wing_sharememory -> add include path
  dnl PHP_ADD_INCLUDE($WING_SHAREMEMORY_DIR/include)

  dnl # --with-wing_sharememory -> check for lib and symbol presence
  dnl LIBNAME=wing_sharememory # you may want to change this
  dnl LIBSYMBOL=wing_sharememory # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $WING_SHAREMEMORY_DIR/$PHP_LIBDIR, WING_SHAREMEMORY_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_WING_SHAREMEMORYLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong wing_sharememory lib version or lib not found])
  dnl ],[
  dnl   -L$WING_SHAREMEMORY_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(WING_SHAREMEMORY_SHARED_LIBADD)

  PHP_NEW_EXTENSION(wing_sharememory, wing_sharememory.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
