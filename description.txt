CS 4204 - Project 3

Author: John Ryding
Date: 4/25/11

Description
===========

	This program draws a 3-D robot that utilizes openGL lighting and texture mapping. Support is also included to move the camera around
	the 3D environment.

	Note:
		I have included the library stb_image.c, written by Sean Barret, from http://nothings.org/stb_image.c to help with the loading of image files into memory.
		
Instructions
============

	Turn Camera
		- Default state when program starts.
		- Press "p" to enter this state
		- Drag mouse left and right to make camera pan
	
	Zoom Camera
		- Press "z" to enter zoom state
		- Drag mouse up and down to make the camera zoom
	
	Rotate Camera
		- Press "r" to enter the rotate state
		- Drag mouse left and right to rotate the camera about the z axis
		
	Edit Limb Positions
		- Press "e" to enter this state
		- Right click the mouse to choose the limb to edit
		- Press 1,2,3 to determine the axis of rotation
			1: rotate the limb about the x-axis, default state
			2: rotate the limb about the y-axis
			3. rotate the limb about the z-axis
		- Drag the mouse left and right to change the rotation angle of the limb
	
	Save Current Pose
		- Right click the mouse and choose "Save Pose"
	
	Save Current Animation
		- Right click the mouse and choose "Save Animation"
		
	Change animation framerate
		- Right click the mouse, hover over "Set framerate" and click on a number to set the framerate
	
	Play the animation:
		- Press "f" for forward play
		- Press "b" for backward play
	
	Stop the animation:
		- Press "s"
		
	Add a keyframe to the animation:
		- Press the space bar
	
	Increase the current frame
		- Press the right arrow button
	
	Decrease the current frame
		- Press the left arrow button
		
Program Execution Instructions
==============================

	Mac:
		make -f Makefile_osx
		./project3
	
	Linux:
		make
		./project3
		
	Arguments (optional):
		-s	A path to a file that will be created to store the current pose of the robot.
		-l	A path to a file that will be used to load a previously saved robot file
		-As A path to a file that will be created to store the current animation of the robot.
		-Al A path to a file that will be used to load a previously animation file
		
	Note:
		I have included a pose file called "ro.bit"
		

Completed Requirements
======================

	- Create a 3D robot from project 2
	- saving the current pose of a robot to a file
	- loading a robot's pose into the program
	- Create an animation clip and save it to a file
	- Load an animation clip from a file
	- Specify the framerate of the animation
	- Specify key poses using the spacebar (Pressing the spacebar will append the current pose as a keyframe 10 frames ahead of the last keyframe)
	- Remove a keyframe from the animation using the "d" button
	- Play the animation clip forward and backward using the "f" and "b" button respectively
	- Stop the animation from playing using the "s" button
	- Use the left and right arrow buttons to increase and decrease the current frame
	- Dragging the mouse while pressing the SHIFT button will increase or decrease the frame
	
	
Robot Pose File
===============

The format of the pose file is the following:

<String, name of the limb>\n
<String, path to the texture file of the limb>\n
<float, angle of rotation about the x-axis> <float, angle of rotation about the y-axis> <float, angle of rotation about the z-axis>\n
<float, R value for ambient lighting> <float, G value for ambient lighting> <float, B value for ambient lighting> <float, A value for ambient lighting>\n
<float, R value for diffuse lighting> <float, G value for diffuse lighting> <float, B value for diffuse lighting> <float, A value for diffuse lighting>\n
<float, R value for specular lighting> <float, G value for specular lighting> <float, B value for specular lighting> <float, A value for specular lighting>\n
<float, shininess value>\n
\n

Example:

head
Baboon.bmp
80 30 0
0.9 0.9 0.9 1
0.9 0.9 0.9 1
0.9 0.9 0.9 1
100

Robot Animation File
===============

The format of the pose file is the following:

"channel"\n
"keyframe"\n
<int, time> <float, value> <string, tangent in rule> <string, tangent out rule>\n

Example:

channel
keyframe
0 0 linear linear
keyframe
10 0 linear linear
keyframe
20 0 linear linear
keyframe
30 0 linear linear
keyframe
40 0 linear linear
keyframe
50 0 linear linear
keyframe
60 0 linear linear
keyframe
70 0 linear linear
keyframe
80 0 linear linear
channel
keyframe
0 0 linear linear
keyframe
10 0 linear linear
keyframe
20 0 linear linear
keyframe
30 0 linear linear
keyframe
40 0 linear linear
keyframe
50 0 linear linear
keyframe
60 0 linear linear
keyframe
70 0 linear linear
keyframe
80 0 linear linear


	