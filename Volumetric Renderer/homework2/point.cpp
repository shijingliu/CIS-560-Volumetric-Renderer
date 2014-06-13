//=========================
//Author: Shijing Liu
//Class: point.h
//Basic Information:this class is used to 
//get position for a point
//===========================================


#include <iostream>
#include "point.h"
//using namespace std; 

point::point()
{
}

point::point(int _x, int _y, int _z)
{
	x = _x; 
	y = _y; 
	z = _z; 
}

float point::getX()
{
	return x; 
}
float point::getY()
{
	return y; 
}
float point::getZ()
{
	return z; 
}

void point::setX(float _x) 
{
    x = _x; 
}
void point::setY(float _y)
{
	y = _y; 
}
void point::setZ(float _z)
{
	z = _z; 
}