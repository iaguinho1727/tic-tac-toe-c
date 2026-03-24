AC_INIT([TicTacToe], [1.0], [iago.arantes1727@gmail.com])
AC_PROG_CC

# Check for POSIX headers used by the project
AC_CHECK_HEADERS([unistd.h termios.h signal.h], [],
  [AC_MSG_ERROR([Required POSIX header not found. This project requires a POSIX-compatible system.])])

# Check for termios functions (terminal raw mode)
AC_CHECK_FUNCS([tcgetattr tcsetattr sigaction], [],
  [AC_MSG_ERROR([Required POSIX functions not found.])])

# Default DESTDIR to /usr/local/bin if not set
AC_ARG_VAR([DESTDIR], [Installation directory])
AS_IF([test "x$DESTDIR" = "x"], [DESTDIR="/usr/local/bin"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
