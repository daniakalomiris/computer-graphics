# COMP 371: Computer Graphics

- The scene has lighting (using the Phong model)
- Olaf's legs and arms move a little when he either moves forward or backward
- Olaf's position can be repositioned to a random location on the grid by pressing SPACEBAR
- Olaf can be scaled up and down by pressing SHIFT + J and SHIFT + U
- Olaf can be moved around the grid by pressing SHIFT + W, SHIFT + A, SHIFT + S and SHIFT + S
- World orientation can reset by pressing SHIFT + H
- Render mode can be changed by pressing SHIFT + P (points), SHIFT + L (lines), SHIFT + T (triangles) or SHIFT + O (triangle mesh)
- Camera can be panned or tilted by pressing RMB + moving mouse to the left/right and MMB + moving mouse up/down
- Zooming in/out of the scene by pressing LMB + moving mouse up/down
- Vertex shader and fragment shader are in their own separate files which are loaded in from the main file
- The world orientation is changed by rotating all objects about the x and y axis by pressing RIGHT ARROW, LEFT ARROW, UP ARROW and DOWN ARROW
- Toggle textures by pressing SHIFT + X
This assignment was built in Xcode and has only been tested on Mac. To run the application on a Mac, the .xcodeproj file under the xcode folder must be opened in xcode. All libraries have been added to the build paths of the Xcode project and thus require no further configurations. 

Due to developping this on Mac, since Mac keyboards do not have a 'Home' button, instead of pressing the 'Home' button to reposition the world orientation, the button was replaced with 'H'.
