@echo off

set program="bin\glGUI\convex_hull_gl.exe"

if exist %program% (
	.\%program%
) else (
	echo ERROR: You should run make before execute %program%
)

