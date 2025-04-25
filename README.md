## OpenGL Renderer
#### my submition for the graphics programming assignment - Staffordshire University

For this assignment we were tasked with building a 3D simulation running in OpenGL and C++ using an Object Oriented Approach. Throughout development i have been aiming to meet the First Class requirements, which are as followed:

* Reading multiple meshes data from .OBJ files
* Common renderering optimisations such as face windig, back face culling ext
* Text Renderering (atleast 3 forms of text)
* A good camera controller with the ability to track objects
* Animation on objects without user input
* The ability to manipulate objects with user input
* A texturing implementation that allows user to change textures at runtime
* Materials and lighting implemented
* A scene graph implementation referencing a linked list data structure
* High quality coding standards

## Controls
#### Camera
the camera functions similarly to the unreal engine camera:<br>
* WASD to move around the scene<br>
* Hold right click and move mouse to change camera direction<br>
however additionality allows object tracking:<br>
* E to toggle object tracking
* Space to cycle tracked object

#### Transformations
to select a transformation mode:<br>
* T to translate
* O to scale
* R to rotate
* T to change the texture
To modify the Axis:<br>
* N increase selected axis
* M decrease selected axis
