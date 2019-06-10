/*
    Image.cpp
*/

#include <Image.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <GL/glut.h>
#include <Block.h>
#include <Point.h>

using namespace std;

Image::Image()
{
    //ctor
    static unsigned texture_id_number = 0;
    texture_id = texture_id_number++;
}

Image::Image(cv::Mat& set_img)
{
    img = set_img;
}

Image::~Image()
{
    //dtor
    free(&img);
}

void Image::ReadImg(const char img_name[])
{
    img = cv::imread(img_name,-1);
    width = img.cols -1 ;
    height = img.rows -1;
}

void Image::CVShow(const int window_type)
{
    cv::namedWindow("display",window_type);
    cv::imshow("display",img);
    cv::waitKey(0);
}

void Image::TransToRGB(cv::Mat& img)
{
    cv::Mat temp;
    img.copyTo(temp);

    for(int x=0; x<img.rows; x++)//trans image from BGR to RGB
    {
        for(int y=0; y<img.cols; y++)
        {
            if( img.channels()==3 )
            {
                temp.at<cv::Vec3b>(x,y)[2] = img.at<cv::Vec3b>(x,y)[0];
                temp.at<cv::Vec3b>(x,y)[0] = img.at<cv::Vec3b>(x,y)[2];

            }
            else if(img.channels()==4 )
            {
                temp.at<cv::Vec4b>(x,y)[2] = img.at<cv::Vec4b>(x,y)[0];
                temp.at<cv::Vec4b>(x,y)[0] = img.at<cv::Vec4b>(x,y)[2];
            }
            else
            {
                printf("FUCK IMG\n");
            }
        }
    }

    temp.copyTo(img);
    free(&temp);
}

void Image::UploadTexture(void)
{
    cv::Mat texture;

    img.copyTo( texture);
    TransToRGB( texture );  //opencv: BGR, opengl:RGB

    /*
        由於非 2^N 高寬的 texture 是顯卡無法接受的
        所以要先做一個2^N 大小高寬的圖給顯卡
        到時候在指定只顯示實際大小
    */
    duwidth  =  pow( 2, ceil( log(img.cols-1)/log(2) ) );   //2^n 大小
    duheight =  pow( 2, ceil( log(img.rows-1)/log(2) ) );

    int type;

    if( texture.channels()==3 )
        type = CV_8UC3;
    else if( texture.channels()==4 )
        type = CV_8UC4;


    cv::Mat temp(duheight,duwidth,type,cv::Scalar(0,0,0) );
    cv::Mat img_roi = temp( cv::Rect( 0, 0, texture.cols, texture.rows) );
    cv::addWeighted( img_roi, 0, texture, 1, 0, img_roi);
    temp.copyTo(texture);
    free(&temp);


    glEnable( GL_TEXTURE_2D);
    glGenTextures(1, &texture_id);              //綁定texture
    glBindTexture( GL_TEXTURE_2D, texture_id);  //同上

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );   //一些神奇參數
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    //開心的把texture給顯卡喽
    if( img.channels()==3 )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texture.cols, texture.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
    }
    else if( img.channels()==4 )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture.cols, texture.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data);
    }

    free(&texture);
}

void Image::GLDraw(Point location,int camera_width,int camera_height)
{

    if( texture_id >= 0 && texture_id != NULL )
    {
        double temp_w,temp_h;   // halve of image_size
        double img_w,img_h;     //   img / 2^n grid
        Block draw_block;


        temp_w = ( (double)width/ (double)camera_width ) * 2;
        temp_h = ( (double)height/ (double)camera_height ) * 2;
        draw_block.Setcenter( location);
        draw_block.Setwidth( temp_w);
        draw_block.Setheight( temp_h);

        img_w = (double)width / (double)duwidth;
        img_h = (double)height/ (double)duheight;


        glBindTexture( GL_TEXTURE_2D, texture_id);  //綁定此ID
        glEnable( GL_TEXTURE_2D);   //開始貼texture

        /*
            glTextCoor2d :texture中要使用的部分 0~1
            glVertex2d :貼的位置
        */
        glBegin( GL_QUADS); //start to draw a grid
        glTexCoord2d( 0    , 0    ); glVertex2d( draw_block.Vertices(0).Getx() , draw_block.Vertices(0).Gety() );//L,D
        glTexCoord2d( img_w, 0    ); glVertex2d( draw_block.Vertices(1).Getx() , draw_block.Vertices(1).Gety() );//R,D
        glTexCoord2d( img_w, img_h); glVertex2d( draw_block.Vertices(2).Getx() , draw_block.Vertices(2).Gety() );//R,U
        glTexCoord2d( 0    , img_h); glVertex2d( draw_block.Vertices(3).Getx() , draw_block.Vertices(3).Gety() );//L,U
        glEnd();    //end

        glDisable( GL_TEXTURE_2D);  //結束貼texture
    }

}







