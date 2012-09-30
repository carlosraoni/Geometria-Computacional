@echo off

set program="bin\glGUI\triangulation_gl.exe"

if exist %program% (
	.\%program%
) else (
	echo ERROR: You should run make before execute %program%
)

