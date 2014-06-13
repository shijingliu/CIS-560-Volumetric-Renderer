//===========================================
//Author: Shijing Liu
//Class: normalSimulation.h
//Basic Information:this class is used to implement 
//simulation. It first precomputes the 
//the light value (Q) and Store it. Later on, use the 
//light value in the ray match.
//===========================================


#include "voxel.h"
#include "point.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include "EasyBMP.h" 


using namespace std; 
class normalSimulation{
private:
	string str; 
	//define the kapa
	float kapa ; 
	//define the step size in x-axis
	float stepX ; 
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
	//set an index 
	int index; 
	//declare a temporary number 
	float temp;
	//declare a vector to store the string, light value, voxels and points 
	//vector<string> vSstore; 
    vector<float> vQstore1;
	vector<float> vQstore2; 
	vector<voxel> vVstore; 
	vector<point> vPoint;
	vector<point> vNpoint; 
    //define the step size
    float step;
	//set light red color 
	int lightRedColor; 
	//set light blue color 
	int lightBlueColor; 
	//set light green color 
    int lightGreenColor;
	//define the length 
	float a; 
    float length;
    //calculate step times
	int stepTime; 
	//declare light value 
	float deltaQ1;
	float Q1;
	float deltaQ2; 
	float Q2; 

	//declare dentisty 
	float Density; 
	//some parameters for primitives
public:
	//constructor 
	normalSimulation(string nStr, int _x, int _y, int _z);
	//set up the values for sphere primitive
	void getSphere(); 
	//set up the values for a cloud primitive 
	void getCloud(); 
	//set up the values for a 
	void getPyroclastic(); 
	//set up the mixture of two cloud 
	void getMixture(int entry); 
	//set up the inputs 
	void inputFile(); 
	//instantiation primitive
	void instiationPrimitive();
	//polygon primitive
	void polygonPrimitive();
	//precomputed light and store them in the voxel 
	void addLight (); 
	//raymatch from eye to voxel 
	void rayMatch (); 
	//the simulation of the whole process of ray match 
    void Simulation(); 
	
};
