#!/bin/sh

echo "Generating build information using aclocal, autoheader, automake and autoconf"
echo "This may take a while ..."

# Regenerate configuration files.

export WANT_AUTOMAKE_1_6=1

aclocal
autoheader
automake --gnits --include-deps --add-missing --copy 
autoconf

#Copy settings.h.cvs to settings.h and that's it,

directory=`dirname $0`
echo "Now you are ready to run ./configure"
