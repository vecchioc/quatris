Quatris
=======

Quatris is a very simple games like tic-tac-toe, so don't try to win
against a computer!

(Note: This is very preliminary version but it works)

Read the 'INSTALL' file for more detailed directions.

BUILD
=====

Quatris uses the standard ./configure ; make. You need to use gmake, BSD
make probably won't work. Remember, run ./configure --help to see what
build options are available.

In order to compile Quatris, you need to have GTK+ 1.2.5 and GNOME 1.2
installed (as well as the development files!). The configure script
will fail if you don't. You can get it from http://www.gtk.org/ and
http://www.gnome.org.

RUN
===

You should run 'make install' as root to make sure plugins and other files
get installed into locations they want to be in. Once you've done that,
you only need to run 'quatris'.

If you want run quatris without installation you can execute directly
the binay from src directory. Note, the binary look for some pixmaps
in a subdir called "quatris/". For example you can do:

$ cd quatris-1.2.x
$ ln -s pixmaps quatris
$ src/quatris

HOME PAGE
=========
http://quatris.sourceforge.net

------
Gianluca De Marco
Giorgio Vecchiocattivi

Last updated: 2003-03-14

