Hello Fellow OpenSource Developers! 

I am a new member of this extraordinary community, and pleased to say that I am here to stay!

This is my first attempt at a 3D game, using OpenGL libray, along with some SDL2, GLEW, and others. It was 
made for my university module, Games Development.

The aim is very simple: go through the four walls without colliding with them! Sounds easy? Well the wall only appears after a certain time, only giving you little time for the last gate. But why is that?

Well, I love a good story; so here is the one for this game. 
You are a young man, who have lost everything in a horrible accident; when waking up from your coma and realizing that you cannot move anymore, you desperatly ask your doctor if there anything, ANYTHING he could do to make you walk again. And there was. 
By planting robotic parts into your body, thanks to the advanced technology which exists in 2020, you are able to walk again. But the downside is, since you are the FIRST of the project, the goverment wants to test you, mentally and physically. Fine, they got me to walk again. But everything changed when you started doing their dirty work. "For the good of the world" you kept telling yourself. Bullshit. How is killing, murdering, silencing people any good? They just want to keep their power. 
Imagine the look on their faces when you decided to betray them. Well that's how you ended up in jail. A normal one? No, to easy to escape! You were sent to the prison for the "special"; particularity? A 4-layered forcefield, impossible to break through. 
But that weird call you got yesterday, telling you to break out, saying it would help... Will it really? Or are you just going to die from that forcefield? Anyways, both are better than rusting in that cell. Just hope I'll get out of this... 

In the game, you play that person; beautifully designed, he is a cube. Move using the four arrow keys to find the holes in the forcefield before reaching them! Slowing down isn't an option! Get out fast. 

Back to the serious stuff. The libraries I have used are: 
 - SDL2
 - GLEW
 - GLU
 - Vectormath

For building, I have used Cmake. Therefore, after cloning the repository, type in "cmake CMakeLists.txt" from the project folder to create the make file. Then just type "make" and the game is created! To run it, type in 
"./RobotEscape". 

When building my project with Cmake, I had to go and find .cmake files which helped me find the libraries cmake could not. These files can be found under the Modules/ folder, and were, in no way, created by me. 
