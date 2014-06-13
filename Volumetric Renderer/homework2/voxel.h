//=========================
//Author: Shijing Liu
//Class: voxel.h
//Basic Information:this class is used to deal
//with read color, write color, read density, 
//write density 
//===========================================

#ifndef _VOXEL_H_
#define _VOXEL_H_

#include <iostream>
using namespace std; 

class voxel{
private:
	//the density of a voxel 
	float density; 
	//the red value 
	float red; 
	//the green value; 
	float green;
	//the blue value; 
	float blue; 
	//background value
	float backRedColor; 
	float backGreenColor;
	float backBlueColor; 

public: 
	//contructor
	voxel();
	//read density 
	float getDensity(); 
	//read Red value 
	float getRedValue();
	//read Green value
	float getGreenValue(); 
	//read Blue value 
	float getBlueValue(); 
	//get background value 
	float getBackRedValue();
	float getBackGreenValue(); 
	float getBackBlueValue();
	//write density 
	void setDensity(float newDensity);
	//write red color
	void setRedValue(float Red); 
	//write green color 
	void setGreenValue(float Green); 
	//write blude color
	void setBlueValue(float Blue); 
	//set background color 
	void setBackRedValue(float BackRedColor); 
	void setBackGreenValue(float BackGreenColor); 
	void setBackBlueValue(float BackBlueColor); 

};

#endif

