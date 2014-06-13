//=========================
//Author: Shijing Liu
//Class: TrilinearInterpolationSimulation.h
//Basic Information:this class is used to declare some parameters 
//for trilinear interpolation simulation 
//===========================================


#include <iostream>
#include <string>
using namespace std; 

class TrilinearInterpolationSimulation{
private:
	string str; 
	//define the kapa
	float kapa; 
	//define the step size in x-axis
	float stepX; 
	//define the step size in y-axis
	float stepY;
	//define the step size in z-axis
	float stepZ;
	//define the x position
	float x;
	//define the y position
	float y;
	//define the z position
	float z; 
	//convert x from float to int type 
	int voxelX; 
	//convert y from float to int type 
	int voxelY; 
	//convert z from float to int type 
	int voxelZ; 
	//set blackground color 
	int backRedColor; 
	int backGreenColor;
	int backBlueColor; 
	//set the value to move buffer; 
	int xMove;
	int yMove;
	int zMove;  

public:
	TrilinearInterpolationSimulation(string nStr, int _x, int _y, int _z);
    void Simulation(); 
};