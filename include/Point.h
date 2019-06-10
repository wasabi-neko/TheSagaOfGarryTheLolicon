#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point();
    Point(double setx, double sety);
    ~Point();


    void Setx(double val) { x = val; }
    void Sety(double val) { y = val; }


    void Addx(double add){ this->x += add;}
    void Addy(double add){ this->y += add;}

    double Getx() { return x; }
    double Gety() { return y; }


    double DistantTo(Point p);
    double ThetaTo(Point p);


    Point operator + (Point&);
    Point operator - (Point&);
    Point operator * (const double&);
    Point operator / (const double&);
    bool operator == (Point&);


private:
    double x; //!< Member variable "x"
    double y; //!< Member variable "y"
};

#endif // POINT_H
