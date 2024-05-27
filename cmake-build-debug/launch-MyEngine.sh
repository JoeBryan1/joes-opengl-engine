#!/bin/sh
bindir=$(pwd)
cd /Users/joebryan/CLionProjects/opengl-learn/src/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/joebryan/CLionProjects/opengl-learn/cmake-build-debug/MyEngine 
	else
		"/Users/joebryan/CLionProjects/opengl-learn/cmake-build-debug/MyEngine"  
	fi
else
	"/Users/joebryan/CLionProjects/opengl-learn/cmake-build-debug/MyEngine"  
fi
