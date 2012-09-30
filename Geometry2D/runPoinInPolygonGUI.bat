@echo off

set program="bin\glGUI\point_in_polygon_gl.exe"

if exist %program% (
	.\%program%
) else (
	echo ERROR: You should run make before execute %program%
)

