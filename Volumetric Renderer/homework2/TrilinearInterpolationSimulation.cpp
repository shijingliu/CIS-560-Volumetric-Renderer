//=========================
//Author: Shijing Liu
//Class: TrilinearInterpolationSimulation.cpp
//Basic Information:this class is used to implement 
//trilinear interpolation. It first precompute the 
//the light value (Q) and Store it. Later on, use the 
//light value in the ray match.
//In the trilinear interpolation part, we used the 
//following formulas:
//weightX = (1-abs(x-(float)(a+xMove)))
//weightY = (1-abs(y-(float)(b+yMove)))/1;
//weightZ = (1-abs(z-(float)(c+zMove)))/1;
//weight = weightX*weightY*weightZ;
//===========================================

#include "TrilinearInterpolationSimulation.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include "EasyBMP.h" 
#include "voxel.h"
using namespace std; 

//declare a template to convert the string to other type 
template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

//constructor 
TrilinearInterpolationSimulation::TrilinearInterpolationSimulation(string nStr, int _x, int _y, int _z)
{
	str = nStr; 
	xMove = _x;
	yMove = _y;
	zMove = _z; 
}

//trilinear interpolation simualtion 
void TrilinearInterpolationSimulation::Simulation()
{
	//declare an object for ifstream 
	ifstream myReadFile; 
	//open the first txt file "test1.txt"
    myReadFile.open(str);
	//declare a index
	int index =0; 
	//declare a vector to store the string 
	vector<string> vSstore (1010000); 
	//declare a vector to store Q 
	vector<float> vQstore (1001000);
	//declare a temporary number 
	float temp = 0;
	//declare a vector to store voxel; 
	vector<voxel> vVstore (1010000); 
	//read the contents from "text1.txt"
	if(myReadFile.is_open())
	{  
		string str;
		while(!myReadFile.eof()){
			getline(myReadFile, str);
			vSstore[index] = str; 
			index++;
		}	
	}

	//store all the density into the vector 
	for(int i = 0; i<1000000; ++i)
	{
	   from_string<float>(temp, std::string(vSstore[i+13]), std::dec);
	   vVstore[i].setDensity(temp);
	   if(str == "test1.txt")
	   {
			 vVstore[i].setRedValue(245);
			 vVstore[i].setBlueValue(245); 
			 vVstore[i].setGreenValue(245); 
	   }
	   if(str == "test2.txt")
	   {
			vVstore[i].setRedValue(240);
			vVstore[i].setGreenValue(247);
			vVstore[i].setBlueValue(255); 
	   }
	   if(str == "test3.txt")
	   {
			vVstore[i].setRedValue(33);
			vVstore[i].setGreenValue(140);
			vVstore[i].setBlueValue(33); 
	   }
	}
	myReadFile.close();
	
	//define the step size
    const float step = 0.5;
	//set light Red corlor
	const int lightRedColor = 1; 
	//set light blue color 
	const int lightBlueColor = 1; 
	//set light green color 
	const int lightGreenColor = 1;

	//check which combination of background color we should use 
	if(str == "test1.txt")
	{
		backRedColor = 69; 
		backGreenColor = 130;
		backBlueColor = 181;
		kapa = (float) 0.7;
	}
	if(str == "test2.txt")
	{
		backRedColor = 255; 
		backGreenColor = 69;
		backBlueColor = 0;
		kapa = (float)0.9;
	}
	if(str == "test3.txt")
	{
		backRedColor = 0; 
		backGreenColor = 0;
		backBlueColor = 204;
		kapa = (float)0.4;
	}

	BMP output; 
	output.SetSize(640, 480);
	output.SetBitDepth (24);

	 //store the precomputed transmittance 
	for(int i = -320; i< 320; ++i)
	{
		for(int j = -240; j< 240; ++j)
		{
			   float a = (float) (200*200 + j*j + i*i); 
			   float length = sqrt(a);
			   //calculate the corresponding step size in the x, y, z direction 
			   stepX = 200*step/length; 
			   stepY = i*step/length; 
			   stepZ = j*step/length;
			   //calculate step times
			   int stepTime = (int) (length/step); 
			   //delcare delta Q
			   float deltaQ = 0.0; 
			   //declare Q 
			   float Q = 0.5;
			   //declare dentisty 
			   float Density = 0.0;
               //delcare weight
			   float weightX = 0.0; 
			   float weightY = 0.0; 
			   float weightZ = 0.0;
			   float weight =0.0;
			   //go through the light one by one 
			   for(int l= 1; l<= stepTime; ++l)
			   {
				    x = (float)(200-l*stepX); 
			        y = (float)(l*stepY); 
			        z = (float)(l*stepZ); 
					float interpolatedDensity = 0.0;
					if((x>(0+xMove)&&x<(100+xMove))&&(y>(0+yMove)&&y<(100+yMove))&&(z>(0+zMove)&&z<(100+zMove)))
					{
						//convert x,y,z into integer
						voxelX = (int) (x-xMove);
						voxelY = (int) (y-yMove); 
						voxelZ = (int) (z-zMove);
						for(int a = voxelX; a<= voxelX+1; ++a)
				        {
					        for(int b = voxelY; b<= voxelY+1; ++b)
					        {
						        for(int c = voxelZ; c<= voxelZ+1; ++c)
						        {
									weightX = (1-abs(x-(float)(a+xMove)))/1;
							        weightY = (1-abs(y-(float)(b+yMove)))/1;
							        weightZ = (1-abs(z-(float)(c+zMove)))/1;
							        weight = weightX*weightY*weightZ;
                                    index = a +100*b + c*100*100;
									if(index <= 1000000)
									{
									  interpolatedDensity += vVstore[index].getDensity()*weight;
									}
								}
							}
						}
						index = voxelX + voxelY*100 + voxelZ*100*100; 
					    deltaQ = exp(-kapa*step*interpolatedDensity);
						Q *= deltaQ; 
						vQstore[index]= Q;
					}
			   }
		}
	}
    
	//ray match between eye and voxel
    for(int i = -320; i < 320; ++i)
	{
		for(int j= -240; j < 240; ++j)
		{
			//calculate and record the total length of the ray 
			float a = (float) (i*i + j*j + 240*240); 
			float length = sqrt(a); 
		    //the red color in the pixel 
			int redColor = 0; 
			//the green color in the pixel
			int greenColor = 0;
			//the blue color in the pixel 
			int blueColor = 0; 
			//calculate how many steps should go in the ray 
			int stepTime = (int) (length/step);
			//density is used to record voxel density 
			float Density = 0.0; 
			//define transmittance; 
			float Transmittance = 1.0;
			//deltaT is used to calculate transmittance 
			float deltaT = 0.0;
			//calculate the corresponding step size in the x, y, z direction
			stepX = i*step/length; 
			stepY = j*step/length;
			stepZ = 240*step/length;
			//declare weight
			float weightX = 0.0; 
			float weightY = 0.0; 
			float weightZ = 0.0; 
			float weight =0.0; 

			for(int k = 1; k <= stepTime; ++k)
			{
			   x = (float)(k*stepX); 
			   y = (float)(k*stepY); 
			   z = (float)(200.0-k*stepZ); 
               //conditional judgement to see if light is cast into the grid 
			   if((x>(0+xMove)&&x<(100+xMove))&&(y>(0+yMove)&&y<(100+yMove))&&(z>(0+zMove)&&z<(100+zMove)))
			   {
				   //convert x,y,z into integer
				   voxelX = (int) (x-xMove);
				   voxelY = (int) (y-yMove); 
				   voxelZ = (int) (z-zMove);
				   float interpolatedDensity = 0.0;
				   float interpolatedRedColor = 0.0; 
				   float interpolatedGreenColor =0.0; 
				   float interpolatedBlueColor =0.0;
				   for(int a = voxelX; a<= voxelX+1; ++a)
				   {
					   for(int b = voxelY; b<= voxelY+1; ++b)
					   {
						   for(int c = voxelZ; c<= voxelZ+1; ++c)
						   {
							   weightX = (1-abs(x-(float)(a+xMove)))/1;
							   weightY = (1-abs(y-(float)(b+yMove)))/1;
							   weightZ = (1-abs(z-(float)(c+zMove)))/1;
							   weight = weightX*weightY*weightZ;
							   index = a + b*100 + c*100*100;
							   if(index <= 1000000)
							   {
								   //interpolate density 
								   interpolatedDensity += vVstore[index].getDensity()*weight;
								   //interpolate redColor 
								   interpolatedRedColor += vVstore[index].getRedValue()*weight; 
								   //interpolate greenColor
								   interpolatedGreenColor += vVstore[index].getGreenValue()*weight; 
								   //interpolate blueColor 
								   interpolatedBlueColor += vVstore[index].getBlueValue()*weight; 
							   }
						   }
					   }
				   }
				   deltaT = exp(-kapa*step*interpolatedDensity);
				   Transmittance*=deltaT;
				   if(Transmittance < exp(-6.0))
				   {
						break; 
				   }
				   index = voxelX + 100*voxelY + 100*100*voxelZ;
				   redColor += (int)((1-deltaT)/kapa*(interpolatedRedColor*lightRedColor)*Transmittance*vQstore[index]);
				   greenColor += (int)((1-deltaT)/kapa*(interpolatedGreenColor*lightGreenColor)*Transmittance*vQstore[index]);
				   blueColor += (int)((1-deltaT)/kapa*(interpolatedBlueColor*lightBlueColor)*Transmittance*vQstore[index]);
			   }
			}
			//set the color by adding material color with blackground color 
		    if(Transmittance > exp(-6.0)){
				   redColor = (int) (redColor*(1-Transmittance)+ backRedColor*Transmittance); 
				   greenColor = (int) (greenColor*(1-Transmittance) + backGreenColor*Transmittance); 
				   blueColor = (int) (blueColor*(1-Transmittance) + backBlueColor*Transmittance); 
			}

			output(i+320, 239-j)->Red = redColor; 
			output(i+320, 239-j)->Blue = blueColor; 
			output(i+320, 239-j)->Green = greenColor;
		}	
	}

	//check the file name 
	if(str == "test1.txt")
	{
	  output.WriteToFile("BabysFirstCloudImage.bmp");
	}else if (str == "test2.txt")
	{
		output.WriteToFile("FadedCloud.bmp");
	}if (str == "test3.txt")
	{
		output.WriteToFile("BothInOne.bmp");
	}
}

