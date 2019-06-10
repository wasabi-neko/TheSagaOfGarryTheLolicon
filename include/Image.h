#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

/*
    Image.h
*/

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <GL/gl.h>
#include <Point.h>


class Image
{
public:

    Image();
    Image( cv::Mat& set_img );
    ~Image();


    cv::Mat* Getimg() { return &img; }
    int Getwidth() { return img.cols; }
    int Getheight() { return img.rows; }
    int Getchannal() {return img.channels();}
    int Getduwidth() {return duwidth;}
    int Getduheight() {return duheight;}
    GLuint Gettexture_id() { return texture_id; }


    void ReadImg(const char img_name[]);
    void UploadTexture(void);
    void CVShow(const int window_type);
    void GLDraw(Point location,int camera_width,int camera_height);// location為GLUT畫面相對比例座標
    void ReleaseImg(void){ free(&img); }


private:

    cv::Mat img;
    int width;
    int height;
    int duwidth;// 2^n grid
    int duheight;//2^n grid
    GLuint texture_id;

    void TransToRGB(cv::Mat& img);
};


#endif // IMAGE_H_INCLUDED
