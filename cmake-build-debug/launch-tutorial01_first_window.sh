#!/bin/sh
bindir=$(pwd)
cd /tutorial01_first_window
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  USERFILE_COMMAND-NOTFOUND 
	else
		"USERFILE_COMMAND-NOTFOUND"  
	fi
else
	"USERFILE_COMMAND-NOTFOUND"  
fi
