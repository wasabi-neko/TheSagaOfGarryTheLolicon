/*
    2017/06/05
    Game0

    FPS:30  //no
*/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include <opencv2/opencv.hpp>

#include<Block.h>
#include <Point.h>
#include <Image.h>
#include <Camera.h>
#include <Character.h>
#include <Player.h>
#include <FlyingRabbit.h>
#include <Enemy.h>
#include <PlayerStatu.h>

using namespace std;

#define CAMERA_SIZE_WIDTH 640
#define CAMERA_SIZE_HEIGHT 400
#define NEW_ENEMY_TIME 2000     //0.001 sec

unsigned FPS = 100;

Camera cam;
Image background;
Player player;
Enemy enemy;
PlayerStatu player_statue;

static long new_enemy_clock;

Point mouse_posision(0,0);

void Display(void);
void WindowSize(int width,int height);//維持畫面比例
void KeyboardDown(unsigned char key, int x,int y);
void KeyboardUp(unsigned char key, int x, int y);
void GameUpdate(int id);
void FlushTimer(int id);


using namespace std;

int main()
{
    srand( time(NULL) );
    ///gl setting
    glutInitDisplayMode( GLUT_DOUBLE| GLUT_RGBA);
    glutInitWindowSize( CAMERA_SIZE_WIDTH, CAMERA_SIZE_HEIGHT);
    glutCreateWindow("window title");

    glutIgnoreKeyRepeat( true);
    glEnable( GL_ALPHA_TEST);
    glAlphaFunc( GL_GREATER, 0);

    glutDisplayFunc( Display);   //call back function
    glutReshapeFunc( WindowSize);
    glutKeyboardFunc( KeyboardDown);
    glutKeyboardUpFunc( KeyboardUp);
    glutTimerFunc( 1, GameUpdate, 1);
    ///end gl setting

    ///init game options
    Block temp( Point(CAMERA_SIZE_WIDTH/2 , CAMERA_SIZE_HEIGHT/2 ) , CAMERA_SIZE_WIDTH, CAMERA_SIZE_HEIGHT);
    cam.Setvisible_area( temp);


    Block temp2 = player.Getcharacter_block();

    temp2.Setcenter( Point(300,200) );
    player.Setcharacter_block( temp2 );

    printf("test\n");
    player.Prepare();
    player.Activate();
    printf("player prepareing complete\n");


    player_statue.SetPlayer( &player );
    player_statue.Prepare();
    printf("player_statue complete\n");

    background.ReadImg("background_skin//background.png");
    background.UploadTexture();
    background.ReleaseImg();
    printf("background_skin complete\n");
    ///end init

    printf("start\n");
    glutMainLoop();
    return 0;
}

void Display(void)
{
    glClear( GL_COLOR_BUFFER_BIT);// 清空畫面
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    background.GLDraw( Point(0,0), CAMERA_SIZE_WIDTH, CAMERA_SIZE_HEIGHT);

    player_statue.Show();

    player.Show(cam);
    enemy.Show(cam);

    glutSwapBuffers();
}

void WindowSize(int width,int height)
{
    int window_w, window_h;
    double bas_w,bas_h;     //basic width
    double nw,nh,n;        //number of width,
    double mask_x,mask_y;


    bas_w = 1;
    bas_h = (double)CAMERA_SIZE_HEIGHT / (double)CAMERA_SIZE_WIDTH;

    nw = (double)width/bas_w;
    nh = (double)height/bas_h;
    n = nw<=nh ? nw : nh;

    window_w = n*bas_w;
    window_h = n*bas_h;

    mask_x = (double)( glutGet( GLUT_WINDOW_WIDTH) - window_w) /2;
    mask_y = (double)( glutGet( GLUT_WINDOW_HEIGHT) - window_h) /2;


    glViewport( mask_x, mask_y, window_w, window_h);            //當視窗長寬改變時，畫面也跟著變
                                                                //( start_x , start_y , window_size, window_size );

    glMatrixMode( GL_MODELVIEW);    //set window
    glLoadIdentity();
}

void KeyboardDown(unsigned char key, int x,int y)
{
//    printf("%x Down\n",key);

    switch( key )
    {
    case 'w':   //press 'w'

        Player::player_jump_key = true;
        Player::jump_skin_clock = 0;
        break;
    case 's':

        break;
    case 'a':

        Player::player_left_key = true;
        Player::walkl_skin_clock = 0;
        break;
    case 'd':

        Player::player_right_key = true;
        Player::walkr_skin_clock = 0;
        break;
    case 'j':

        Player::player_attack_key = true;
        break;
    case 'l':

        player.Setspeed( 2000/(double)FPS );
        break;
    case 27:
        exit(0);//exit program
        break;
    }
}

void KeyboardUp(unsigned char key, int x, int y)
{
//    printf("%x UP\n");
    switch( key )
    {
    case 'w':   //release 'w'

        Player::player_jump_key = false;
        break;
    case 's':

        break;
    case 'a':

        Player::player_left_key = false;
        break;
    case 'd':

        Player::player_right_key = false;
        break;
    case 'j':

        Player::player_attack_key = false;
        break;
    case 'l':

        player.Setspeed( 700/(double)FPS );
        break;
    }
}


void GameUpdate(int id)//1
{
//    printf("update\n");
    long start_time;
    long max_time = round( (1/(double)FPS)*1000 ) -1;
    long now_time;
    long delay;

    start_time = clock();

    ///main logic
    if( player.Getposition().Gety() <= 50)
    {
        player.Setgrounded( true );
    }
    else
    {
        player.Setgrounded( false );
    }

    if( player.Getposition().Getx() < -20 )
    {
        player.BeenAttack( 1,20 );
    }
    else if( player.Getposition().Getx() >= CAMERA_SIZE_WIDTH+20 )
    {
        player.BeenAttack( 1,20);
    }

    player.Control();
    player.UpdateStatu();

    //spawn enemy
    if( clock() - new_enemy_clock >= NEW_ENEMY_TIME )
    {
//        printf("new enemy appeared\n");//

        new_enemy_clock = clock();

        Point pos;
        double speed;

        speed = 150 + rand()%300;
        pos.Sety( rand()%100 + 300 );
        pos.Setx( rand()%600  );

        enemy.New( pos , speed,0, player);
    }

    enemy.Action();
    enemy.UpdateStatue();

    player_statue.Update();
    ///end main logic


    now_time = clock();
    delay = max_time - (now_time - start_time);
    if( delay <= 0)
        delay = 1;

//    printf("delay%d\n",delay);

    glutTimerFunc( delay, FlushTimer, -1);
}

void FlushTimer(int id)//-1
{
    glutPostRedisplay();// 更新一次Display
    glutTimerFunc( 1, GameUpdate, 1);
}




