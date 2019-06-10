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

The `openCV2` lib is for opening and storing imgs.The `openGL` is for 'drawing' the window.

this program use `openGL` with `GLUT`, but `GLUT` is a bit *old* now.So its not recommand that operat the `openGl` with `GLUT` now.

this porject only took me two weeks to compelet it(excluding the images).So it is a bit...simple or... er... a mess... 

actually, the game is just beta.I didnot completed finish  it.
***
## Example images
![example2](https://github.com/JapariToki/TheSagaOfGarryTheLolicon/blob/master/ReadMe_img/ex2.PNG)
![example3](https://github.com/JapariToki/TheSagaOfGarryTheLolicon/blob/master/ReadMe_img/ex3.PNG)

***
## How to
just exe the `~bin/Debug/Game0.exe`.

*attention*It only have debug version, so it might exe a bit slow.If you want full experience of the game, compile this with realse method. Donot know how? just use goole and your brain.
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
| `some staue values`|

| `Character`|
| :-- |
| `Block` |
| `Image` |
| `some methods` |
| `some values` |


`Player` extend form: `Character`

| `Player` |
| :----- |
| `new contorl key` |
| `defin some value` |


`FlyingRabbit` extend from: `Character`

| `FlyingRabbit` |
| :--- |
| `new enemy methods` |
| `define some value` |

| `Enemy` |
| :--- |
| `contorls all of the enemy` |

| `PlayerStatu` |
| :--- |
| `store player sta` |
| `contorl player in mainLoop` |

*the position in all of the `Show()` method is using relative pos(real - camera.center)*

***

## how it works
* initialize all (`BackGround`, `Enemy`, `Player`)
* start `GLUT` main loop
  * show the buffer
  * wait a few millmiseconds
  * get keyBoard keys
  * `if (exit)` then break loop 
  * calculate and update the game staues
  * `if (dead)` then break loop and set sta to endGame
  * draw all the things sould be seen on the buffer perspectively
  * swap buffer
* END

***
## whishes
You might found that the method: `Camera.MoveTo()` is never been used.Actually, i originally plan to make a scroll map for this game, and the `Camera.MoveTo()` is mad for scroll the screen,and the `Show` methods is based to the `Camera` pos.If you want, you can new a new_branch, and try to compelte this, making this game a real scroll map game. 
![=u=](https://github.com/JapariToki/TheSagaOfGarryTheLolicon/blob/master/ReadMe_img/=u=.bmp)
