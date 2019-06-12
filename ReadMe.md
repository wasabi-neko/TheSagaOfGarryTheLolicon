# The Saga of Garry The Lolicon
![example image 1](https://github.com/JapariToki/TheSagaOfGarryTheLolicon/blob/master/ReadMe_img/ex1.PNG)
***
## information:
### HLHS_28G_informationG
* author: AnJung
* date: 2017/06/05
* add some comment in: 2019/06/10
***
## description:
mad with `C++`, `openGL`, `openCV2` .

The `openCV2` lib is for opening and storing imgs.
And the `openGL` is for 'drawing' the window.

This program use `openGL` with `GLUT`, but `GLUT` is a bit *old* now. So it's not recommended operate the `openGl` with `GLUT` now.

This project only took me two weeks to complete(excluding the images). So it is a bit...simple or... er... a mess... 

Actually, the game is just beta. I didn't completely finish it.
***
## Example images
![example2](https://github.com/JapariToki/TheSagaOfGarryTheLolicon/blob/master/ReadMe_img/ex2.PNG)
![example3](https://github.com/JapariToki/TheSagaOfGarryTheLolicon/blob/master/ReadMe_img/ex3.PNG)

***
## How to
Just execute the `~bin/Debug/Game0.exe`.

*attention* There is only debug version, so it might work a bit slow. If you want full experience of the game, compile this with release method. Don't know how? Just Google it and use your brain.
***
## construction of the classes
| `Block` |
| :------- |
| `Point` |


*all the graphic methods are in this class*

| `Image` |
| :----- |
| `opencv methods` |
| `openGL methods` |

| `Camera` |
| :-- |
| `Block`|
| `some statue values`|

| `Character`|
| :-- |
| `Block` |
| `Image` |
| `some methods` |
| `some values` |


`Player` extend form: `Character`

| `Player` |
| :----- |
| `new control key` |
| `define some value` |


`FlyingRabbit` extend from: `Character`

| `FlyingRabbit` |
| :--- |
| `new enemy methods` |
| `define some value` |

| `Enemy` |
| :--- |
| `controls all of the enemy` |

| `PlayerStatus` |
| :--- |
| `store player stats` |
| `control player in mainLoop` |

*the position in all of the `Show()` method is using relative pos(real - camera.center)*

the `max_score` data is stored in the `~bin/Debug/data/max_score.txt`

***

## how it works
* initialize all (`BackGround`, `Enemy`, `Player`)
* start `GLUT` main loop
  * show the buffer
  * wait a few milliseconds
  * get keyBoard keys
  * `if (exit)` then break loop 
  * calculate and update the game staues
  * `if (dead)` then break loop and set status to endGame
  * draw all the things should be seen on the buffer perspectively
  * swap buffer
* END

***
## The things have not done
You might found that the method: `Camera.MoveTo()` is never been used. Actually, I originally planed making a scroll map for this game,  and the `Camera.MoveTo()` is mad for scrolling the screen. Also,  the `Show` methods is based to the `Camera` pos. If you want, you can fork a new_branch, and try to complete this, making this game a real scroll map game. 

![=u=](https://github.com/JapariToki/TheSagaOfGarryTheLolicon/blob/master/ReadMe_img/=u=.bmp)
