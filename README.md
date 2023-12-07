# Asteroids
C++ school assigment

How to launch from source code:
1. Download the project
2. Open file "test1.Sln"
3. Start the program

How to launch from stand alone:
1. Download the standalone realse
2. Unzip
3. Open file "test.exe"

How to Play:
A,D - Rotate
W,S - Froward/Backawrds
Space - Shoot

There are values to controll for some controll located in  Main.cpp, Game.cpp and Game.h
for now the spawn rate is set through the roof, end condition is turned off and the collision interaction between asteroids is disabled (tho still checked just doesn't do the bounce math) 

# Profiling and some small optimization 
![Alt text](NoFlyWeight.png?raw=true "Optional Title")
![Alt text](CollisionBottelnecking.png?raw=true "Optional Title")
Based of the proffiling of the above proffiling the two main isssue are sudden spikes in memory usage that correspond to spawning new wave and ofcourse time spend on checking the collision.

Solution for the first problem is a Desgin Patern called FlyWieght, which boils down to reussing assets saving on memory and in addition saving some time that would be spend on loading assets.
![Alt text](2000withFlyWeight.png?raw=true "Optional Title")

Unfortunetly I didn't manage to eliminate the bigger problem which is checking the collision and around 1500 asteroids game drops bellow 30FPS as it needs to make around 1,125,000 comparisons.
A small improvement was made when I switched to checking the condition from using the sqrt on distance in favor of multiplying the requierd distance for collision.
I thought of implementing space partitioning but sadly I was running low on time and was not sure if that would actually make a significant problem since the asteroids are packed so tighlty when they are in those numbers.
