COMP 371 Computer Graphics Assignment 1
Winter 2020
Dania Kalomiris
40005674

Features (all features that have been instructed to implement have been implemented in this assignment but below is a brief overview):
- Olaf's position can be repositioned to a random location on the grid
- Olaf can be scaled up and down
- Olaf can be moved around the grid
- world orientation can be changed and reset
- render mode can be changed
- camera can be panned or tilted
- zooming in/out of the scene

Functionality (further details on functionality are in the source code for each object which depict all steps of the functionality):
- axis and Olaf parts are modeled after a cube
- vertex shader and fragment shader are in their own separate files which are loaded in from the main file
- the world orientation is changed by rotating all objects about the x and y axis
- to pan the camera, the user must press the right mouse button while moving the mouse horizontally
- to tilt the camera, the user must press the right mouse button while moving the mouse vertically
- to zoom in, the user must press the left mouse button while moving the mouse vertically up
- to zoom out, the user must press the left mouse button while moving the mouse vertically down

This assignment was built in Xcode and has only been tested on Mac. To run the application on a Mac, the .xcodeproj file under the xcode folder must be opened in xcode. All libraries have been added to the build paths of the Xcode project and thus require no further configurations. 

Due to developping this on Mac, since Mac keyboards do not have a 'Home' button, instead of pressing the 'Home' button to reposition the world orientation, the button was replaced with 'H'.