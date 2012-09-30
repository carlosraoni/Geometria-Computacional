#!/bin/sh

program="bin/glGUI/triangulation_gl"

if [ -f "$program" ] 
	then ./$program
	else
		echo "ERROR: You should run make before execute $program"
		
fi
