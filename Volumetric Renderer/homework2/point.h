//=========================
//Author: Shijing Liu
//Class: point.h
//Basic Information:this class is used to 
//get position for a point
//===========================================


#ifndef _POINT_H_
#define _POINT_H_

class point{
private:
	float x;
	float y;
	float z; 

public:
	point(); 
	point(int _x, int _y, int _z); 
	float getX();
	float getY();
	float getZ();

	void setX(float _x); 
	void setY(float _y);
	void setZ(float _z); 
};

#endif