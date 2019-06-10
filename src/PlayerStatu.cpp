#include "PlayerStatu.h"

#include <stdio.h>
#include <windows.h>
#include <Point.h>
#include <Player.h>
#include <Block.h>

//block //glut window coordination
#define HP_BLOCK_CENTER_X -0.8
#define HP_BLOCK_CENTER_Y 0.8
#define HP_BLOCK_WIDTH 85
#define HP_BLOCK_HEIGHT 30
#define GAMEOVER_BLOCK_CENTER_X 0
#define GAMEOVER_BLOCK_CENTER_Y 0
#define GAMEOVER_BLOCK_WIDTH 2
#define GAMEOVER_BLOCK_HEIGHT 2
#define SCORE_BLOCK_CENTERE_X 0.65
#define SCORE_BLOCK_CENTERE_Y 0.6
#define MAX_SCORE_BLOCK_CENTER_X 0.65
#define MAX_SCORE_BLOCK_CENTER_Y 0.8

//glut window coordination
#define NUMBER_SPACE -0.05
#define SCORE_SKIN_ADDX -0.25
#define SCORE_SKIN_ADDY 0.05


#ifndef CAMERA_SIZE_WIDTH
#define CAMERA_SIZE_WIDTH 640
#endif // CAMERA_SIZE_WIDTH

#ifndef CAMERA_SIZE_HEIGHT
#define CAMERA_SIZE_HEIGHT 400
#endif // CAMERA_SIZE_HEIGHT


int PlayerStatu::max_score;
int PlayerStatu::score;

int PlayerStatu::max_score_arr[5];
int PlayerStatu::score_arr[5];

PlayerStatu::PlayerStatu()
{
    //ctor
    hp_block.Setcenter( Point( HP_BLOCK_CENTER_X, HP_BLOCK_CENTER_Y) );
    hp_block.Setwidth( HP_BLOCK_WIDTH );
    hp_block.Setheight( HP_BLOCK_HEIGHT );

    gameover_block.Setcenter( Point( GAMEOVER_BLOCK_CENTER_X, GAMEOVER_BLOCK_CENTER_Y) );
    gameover_block.Setwidth( GAMEOVER_BLOCK_WIDTH );
    gameover_block.Setheight( GAMEOVER_BLOCK_HEIGHT );


    max_score_block.Setcenter( Point( MAX_SCORE_BLOCK_CENTER_X, MAX_SCORE_BLOCK_CENTER_Y ) );
    score_block.Setcenter( Point( SCORE_BLOCK_CENTERE_X, SCORE_BLOCK_CENTERE_Y ) );


    show_heathpoint = false;
    show_gameoverskin = false;
    show_maxscore = false;
    show_score = false;
}

PlayerStatu::~PlayerStatu()
{
    //dtor
}

void PlayerStatu::Prepare(void)
{
    char s[40];


    for(int i=0; i<6; i++)
    {

        sprintf(s,"PlayerStatue_skin//hp%d.bmp",i);

        HP_skin[i].ReadImg(s);
        HP_skin[i].UploadTexture();
        HP_skin[i].ReleaseImg();
    }

    for(int i=0; i<10; i++)
    {
        sprintf(s,"PlayerStatue_skin//number%d.png",i);

        number_skin[i].ReadImg(s);
        number_skin[i].UploadTexture();
        number_skin[i].ReleaseImg();
    }

    gameover_skin.ReadImg("PlayerStatue_skin//gameover.bmp");
    gameover_skin.UploadTexture();
    gameover_skin.ReleaseImg();


    max_score_skin.ReadImg("PlayerStatue_skin//maxscore_skin.png");
    max_score_skin.UploadTexture();
    max_score_skin.ReleaseImg();

    printf("test\n");

    score_skin.ReadImg("PlayerStatue_skin//score_skin.png");
    score_skin.UploadTexture();
    score_skin.ReleaseImg();

    delete s;
    //end read skin


    score = 0;

    FILE* file;

    file = fopen("data//max_score.txt","r");
    fscanf(file,"%d", &max_score);
    fclose(file);

    printf("MAX:%d\n",max_score);


    ScoreCaculate();
    MaxScoreCaculate();
}


void PlayerStatu::ScoreCaculate(void)
{
    for(int i=0; i<5; i++)
    {
        int temp;


        temp = floor( (float)score / pow( 10, i) );
        score_arr[i] =temp%10;
    }
}

void PlayerStatu::MaxScoreCaculate(void)
{
    for(int i=0; i<5; i++)
    {
        int temp;


        temp = floor( (float)max_score / pow( 10, i) );
        max_score_arr[i] =temp%10;
    }
}

void PlayerStatu::Update(void)
{
    show_gameoverskin = false;
    show_heathpoint = false;
    show_maxscore = true;
    show_score = true;


    if( score > max_score )
    {
        max_score = score;
    }

    ScoreCaculate();
    MaxScoreCaculate();


    if( !player->IsDead() )
    {
        show_heathpoint = true;

        FILE* file;

        file = fopen("data//max_score.txt","w");
        fprintf(file,"%d\n", (int)max_score);
        fclose(file);
    }
    else
    {
        show_gameoverskin = true;
        player->Setawake( false );
    }
}

void PlayerStatu::ShowPlayerHP(void)
{
    unsigned HP;
    Point position;

    HP = player->Gethealth_point();
    HP_skin_ptr = HP_skin + HP;

    position = hp_block.Getcenter();


    HP_skin_ptr->GLDraw(position, CAMERA_SIZE_WIDTH, CAMERA_SIZE_HEIGHT);
}

void PlayerStatu::ShowGameover(void)
{
    Point position;

    position = gameover_block.Getcenter();


    gameover_skin.GLDraw(position, CAMERA_SIZE_WIDTH, CAMERA_SIZE_WIDTH);
}

void PlayerStatu::ShowMaxScore(void)
{
    Point position;


    position = max_score_block.Getcenter();

    for(int i=0; i<5; i++)
    {
        number_skin_ptr = number_skin + max_score_arr[i];
        number_skin_ptr->GLDraw( position , CAMERA_SIZE_WIDTH, CAMERA_SIZE_HEIGHT );

        position.Addx( NUMBER_SPACE );
    }

    position.Addx( SCORE_SKIN_ADDX );
    position.Addy( SCORE_SKIN_ADDY );
    max_score_skin.GLDraw( position, CAMERA_SIZE_WIDTH, CAMERA_SIZE_HEIGHT);

//    printf("max:%d\n",max_score);
}

void PlayerStatu::ShowScore(void)
{
    Point position;


    position = score_block.Getcenter();

    for(int i=0; i<5; i++)
    {
        number_skin_ptr = number_skin + score_arr[i];
        number_skin_ptr->GLDraw( position , CAMERA_SIZE_WIDTH, CAMERA_SIZE_HEIGHT );

        position.Addx( NUMBER_SPACE );
    }

    position.Addx( SCORE_SKIN_ADDX );
    position.Addy( SCORE_SKIN_ADDY );
    score_skin.GLDraw(position, CAMERA_SIZE_WIDTH, CAMERA_SIZE_HEIGHT);

//    printf("score:%d\n",score);
}

void PlayerStatu::Show(void)
{
    if( show_heathpoint )
    {
        ShowPlayerHP();
    }

    if( show_gameoverskin )
    {
        ShowGameover();
    }

    if( show_maxscore )
    {
        ShowMaxScore();
    }

    if( show_score )
    {
        ShowScore();
    }
}


















