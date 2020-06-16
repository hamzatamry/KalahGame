# kalah-game
kalah game projet known also as mancala game made with C and SDL2. Here you will either the console version or graphical user interface version.

How to run the game ?

  Console version
  
    To run the console version after clonning, use prompt command to navigate inside the kalah console folder. 
      1. To compile it, type this command :
          gcc *.c -o kalah
      2. To run it type this command depending on your operating system : 
          windows : kalah
          Linux : ./kalah
  
   GUI version
  
      1. Before compiling, make sure you have SDL2, SDL2_ttf, SDL2_image installed on your gcc compiler. After that type this command : 
          gcc *.c -o kalah -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
      2. To run it type this command depending on your operating system :
          windows : kalah
          Linux : ./kalah
          
 Enjoy it.

