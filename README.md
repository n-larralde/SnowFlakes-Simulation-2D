# SnowFlakes-Simulation-2D

Summary: This 'mini-game' was part of a global optimization test process where you have to spawn as much snowflakes as possible.

At the begining, the program can handle about 5000 particules max.

After several optimizations like object pooling (using unique ptr), avoid memory "jumps", removing useless code... the program can handle more than 500k particles (in release mode).

Controls: 
* Arrow keys to move the 'character'
* Use num right 1-9 keys to change the numbers of particles. You may want to change the number of particles so that it runs smoothly on your computer, to do this you need to change the presets values associated to the num keys manually in the Globals.h file.

Depending on if you are running the game on release or debug, it will have a huge impact on perforamces. Prefer testing in release mode.
