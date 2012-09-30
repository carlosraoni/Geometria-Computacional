#!/bin/sh

program="bin/glGUI/point_in_polygon_gl"

if [ -f "$program" ] 
	then ./$program
	else
		echo "ERROR: You should run make before execute $program"
		
fi
