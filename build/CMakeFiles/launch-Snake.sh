#!/bin/sh
bindir=$(pwd)
cd /Users/max/Documents/master1/MOTEUR/Snake3D/Snake/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/max/Documents/master1/MOTEUR/Snake3D/build/Snake 
	else
		"/Users/max/Documents/master1/MOTEUR/Snake3D/build/Snake"  
	fi
else
	"/Users/max/Documents/master1/MOTEUR/Snake3D/build/Snake"  
fi
