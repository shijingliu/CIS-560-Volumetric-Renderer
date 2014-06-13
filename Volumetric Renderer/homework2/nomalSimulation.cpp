//===========================================
//Author: Shijing Liu
//Class: normalSimulation.cpp
//Basic Information:this class is used to implement 
//trilinear interpolation. It first precompute the 
//the light value (Q) and Store it. Later on, use the 
//light value in the ray match.
//===========================================

#include "normalSimulation.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include "EasyBMP.h" 
#include "voxel.h"
#include "point.h"
#include "perlin.h"
#include <math.h>
using namespace std; 

#define BufferSize 1001000
#define BufferLength 100
#define BufferWidth 100
#define BufferHeight 100
#define setDensityValue 1000000
#define radius 40.0
#define sphereX 50
#define sphereY 50
#define sphereZ 50 


//declare a template to convert the string to other type 
template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

//================================================
//the constructor initialize all the necessary private 
//for late use
//===============================================
normalSimulation::normalSimulation(string nStr, int _x, int _y, int _z)
{
     str = nStr; 
	 xMove = _x;
	 yMove = _y;
	 zMove = _z; 
	 temp = 0;
	 index = 0; 
	 step = 0.5; 
	 lightRedColor = 1; 
	 lightBlueColor = 1; 
	 lightGreenColor = 1; 
	 //vSstore.resize(BufferSize);
	 vQstore1.resize(BufferSize); 
	 vQstore2.resize(BufferSize); 
	 vVstore.resize(BufferSize); 
	 vPoint.resize(BufferSize); 
	 vNpoint.resize(BufferSize); 
}

//===============================================
//simulation organizes all the methods to get image 
//=============================================
void normalSimulation::Simulation()
{
	inputFile(); 
	addLight();
	rayMatch();
} 

void normalSimulation::inputFile()
{
    //declare an object for ifstream 
	ifstream myReadFile; 
	//open the first txt file
	//myReadFile.open(str);
	myReadFile.open(str); 
	//read the contents from "text1.txt"
	cout<<"the information for the "<<str<<endl; 
	if(myReadFile.is_open())
	{  
		string str1;
		while(!myReadFile.eof()){
			getline(myReadFile, str1);
			cout<<str1<<endl; 
			index++;
		}	
	} 
	cout<<"==================================================================="<<endl; 
    if(str == "test1.txt")
	{
		getSphere();
		cout<<"writing test1"<<endl; 
	}else if(str == "test2.txt")
	{
		getCloud(); 
		cout<<"writing test2"<<endl; 
	}else if(str == "test3.txt")
	{
		getMixture(3); 
		cout<<"writing test3"<<endl; 
	}else if(str == "test4.txt")
	{
		instiationPrimitive();
		cout<<"writing test4"<<endl; 
	}else if(str == "test5.txt")
	{
	    polygonPrimitive(); 
		cout<<"writing test5"<<endl; 
	}

	for(int i = 0; i<setDensityValue; ++i)
	{
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
	   if(str == "test4.txt")
	   {
		   vVstore[i].setRedValue(245);
		   vVstore[i].setBlueValue(245); 
		   vVstore[i].setGreenValue(245); 
	   }
	   if(str == "test5.txt")
	   {
		   vVstore[i].setRedValue(245);
		   vVstore[i].setBlueValue(245); 
		   vVstore[i].setGreenValue(245); 
	   }
	}

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
		kapa = (float)0.15;
	}
	if(str == "test4.txt")
	{
		backRedColor = 69; 
		backGreenColor = 130;
		backBlueColor = 181;
		kapa = (float) 0.7;
	}
	if(str == "test5.txt")
	{
		backRedColor = 69; 
		backGreenColor = 130;
		backBlueColor = 181;
		kapa = (float) 0.7;
	}
}

//================================================
//getCloud create a cloud shaped object 
//the formula it uses is:
//density = fbm(P) + (1.0 - P/radius)
//================================================
void normalSimulation::getCloud()
{
	Perlin per(10,0.1,1.8,3);
	float noiseDensity = 0.0; 
    float disSquare = 0.0;
	float distance = 0.0; 
	int integerDis = 0; 
	for(int i = 0; i<BufferLength; ++i)
	{
		for(int j = 0; j<BufferWidth; ++j)
		{
			for (int k = 0; k<BufferHeight; ++k)
			{
				disSquare = (float) ((i-50)*(i-50) + (j-50)*(j-50) + (k-50)*(k-50)); 
				distance = sqrt(disSquare); 
				index = (i)+(j)*BufferWidth+(k)*BufferWidth*BufferHeight; 
				noiseDensity = (float) per.Get(i, j, k) + (float)(1.0- (float)(distance/20.0));
				//clamp the density that is not within 0 and 1 
				if(noiseDensity > 1)
				{
					noiseDensity = 1; 
				}
				if(noiseDensity < 0)
				{
					noiseDensity = 0; 
				}
				vVstore[index].setDensity(noiseDensity); 
			}
		}
	} 
}   

//=============================================
//getSphere create a sphere object 
//the formula it uses is:
//if(distance>=radius)
//		density = 0
//if(distance <40)
//      density = 1.0/distance
//===========================================
void normalSimulation::getSphere()
{
    float disSquare = 0.0;
	float distance = 0.0; 
	int integerDis = 0; 
	float scale = 0.0; 
	for(int i = 0; i<BufferLength; ++i)
	{
		for(int j = 0; j<BufferWidth; ++j)
		{
			for (int k = 0; k<BufferHeight; ++k)
			{
				disSquare = (float) ((i-sphereX)*(i-sphereX) + (j-sphereY)*(j-sphereY) + (k-sphereZ)*(k-sphereZ)); 
				distance = sqrt(disSquare); 
				index = (i)+(j)*BufferWidth+(k)*BufferWidth*BufferHeight; 
				if(distance>=radius)
				{ 
					vVstore[index].setDensity(0); 
				}else if(distance <radius)
				{
					scale = (float) 1/distance; 
					vVstore[index].setDensity(scale);  
				}
			}
		}
	}
}

//===========================================
//getPyroclastic is used to create the pyroclastic shaped object
//the formula it uses to create density is 
//pyroclasticDensity = max((radius- |P/radius + fbm(P)|), 0);
//===========================================

void normalSimulation::getPyroclastic()
{
	Perlin per(1,0.1,2.0,3);
	float pyroclasticDensity = 0.0; 
    float disSquare = 0.0;
	float distance = 0.0; 
	int integerDis = 0; 
	for(int i = 0; i<BufferLength; ++i)
	{
		for(int j = 0; j<BufferWidth; ++j)
		{
			for (int k = 0; k<BufferHeight; ++k)
			{
				disSquare = (float) ((i-50)*(i-50) + (j-50)*(j-50) + (k-50)*(k-50)); 
				distance = sqrt(disSquare); 
				index = (i)+(j)*BufferWidth+(k)*BufferWidth*BufferHeight;
				pyroclasticDensity = 5.0- abs(distance/5.0) + (float) (abs(per.Get(i,j,k)));

				//clamped the density between 0 and 1 
				if(pyroclasticDensity < 0)
				{
					pyroclasticDensity = 0; 
				}
				if(pyroclasticDensity > 1)
				{
					pyroclasticDensity = 1; 
				}
				vVstore[index].setDensity(pyroclasticDensity);  	
			}
		}
	}
}


//======================================================
//getMixture is corresponding to the test3.txt
//it is a mixture representation of two clouds and one pyroclastic 
//the density of the two clouds and the pyroclastic are calculated 
//seperatedly first. Then clamp the densities that are less than 0 
//and add them together. 
//======================================================

void normalSimulation::getMixture(int entry)
{
	Perlin per1(1,0.1,2.0,3);
	Perlin per2(1,0.1,1.8,3);
	Perlin per3(1,0.1,1.8,3);
	float pyroclasticDensity = 0.0; 
	float noiseDensity1 = 0.0; 
	float noiseDensity2 = 0.0; 
    float disSquare1 = 0.0;
	float distance1 = 0.0; 
	float disSquare2 = 0.0; 
	float distance2 = 0.0; 
	float disSquare3 = 0.0; 
	float distance3 = 0.0; 
	int integerDis = 0; 

	float entryDensity1 = 0.0;
	float entryDensity2 = 0.0; 
	float entryDensity3 = 0.0;   

	for(int i = 0; i<BufferLength; ++i)
	{
		for(int j = 0; j<BufferWidth; ++j)
		{
			for (int k = 0; k<BufferHeight; ++k) 
			{
				//calculate the distance of pyroclastic 
				disSquare1 = (float) ((i-50)*(i-50) + (j-50)*(j-50) + (k-50)*(k-50)); 
				distance1 = sqrt(disSquare1); 
				//calculate the distance of the first cloud 
				disSquare2 = (float) ((i-25)*(i-25) + (j-25)*(j-25) + (k-25)*(k-25)); 
				distance2 = sqrt(disSquare2);
				//calculate the distance of the second cloud 
			    disSquare3 = (float) ((i-75)*(i-75) + (j-75)*(j-75) + (k-75)*(k-75)); 
				distance3 = sqrt(disSquare2); 

				index = (i)+(j)*BufferWidth+(k)*BufferWidth*BufferHeight;
				//calculate the noise plan for each one 
				pyroclasticDensity = 5.0- abs(distance1/5.0) + (float) (abs(per1.Get(i,j,k)));
				noiseDensity1 = (float) per2.Get(i, j, k) + (float)(1.0- (float)(distance2/20.0));
				noiseDensity2 = (float) per3.Get(i, j, k) + (float)(1.0- (float)(distance3/5.0));

				//clamped the density less than 0  
				if(pyroclasticDensity < 0)
				{
					pyroclasticDensity = 0;    
				}
				if(noiseDensity1 < 0)
				{
					noiseDensity1 = 0;    
				}
				if(noiseDensity2 < 0)
				{
					noiseDensity2 = 0; 
				}
				entryDensity1 = noiseDensity1; 
				entryDensity2 = noiseDensity1 + pyroclasticDensity; 
				entryDensity3 = noiseDensity1 + noiseDensity2 + pyroclasticDensity; 
				if(entry == 1)
				{
				    vVstore[index].setDensity(entryDensity1);  
				}if(entry == 2)
				{
					vVstore[index].setDensity(entryDensity2);  
				}if(entry == 3)
				{
				    vVstore[index].setDensity(entryDensity3);  
				}
			}
		}
	}
}

//=======================================================
//instiationPrimitive goes with the follow steps:
//1. it starts with 216000 points
//2. these points are distributed by a noise plan. 
//3. go through each point. store 0.5*density to the current voxel
//and 0.1*density to the neighbour voxel
//=========================================================

void normalSimulation::instiationPrimitive()
{
	int neighbourhood1 =  0; 
	int neighbourhood2 =  0; 
	int neighbourhood3 =  0; 
	int neighbourhood4 =  0; 
	int neighbourhood5 =  0;
	int neighbourhood6 =  0;
	//generate one million random points 
    for(int i = 0; i<BufferLength; ++i)
	{
		for(int j = 0; j<BufferWidth; ++j)
		{
			for (int k = 0; k<BufferHeight; ++k) 
			{
				float _x  = (float)rand()/(float)RAND_MAX;
				float _y  = (float)rand()/(float)RAND_MAX;
				float _z  = (float)rand()/(float)RAND_MAX;
				float x100 = _x*60.0; 
				float y100 = _y*60.0;
				float z100 = _z*60.0; 

                index = k+j*BufferWidth+i*BufferLength*BufferWidth; 
				vPoint[index].setX(x100);
				vPoint[index].setY(y100);
				vPoint[index].setZ(z100);			
			}
		}
	 }
	
	//initialize each voxel first 
	for(int i = 0; i<1000000; i++)
	{
		vVstore[i].setDensity(0); 
	}

	for(int i = 0; i < 1000000; i++)
	{
		int tempX = (int) (vPoint[i].getX());
		int tempY = (int) (vPoint[i].getY()); 
		int tempZ = (int) (vPoint[i].getZ()); 

		Perlin perIP (1,0.1,2.0,3);
		float densityIP = perIP.Get(vPoint[i].getX(), vPoint[i].getY(), vPoint[i].getZ()); 
		if(densityIP <0)
		{
			densityIP = 0; 
		}

		index = tempX + tempY*BufferWidth + tempZ*BufferLength*BufferWidth; 
		if((tempX>0)&&(tempY>0)&&(tempZ>0)&&(tempX<(BufferLength-1))&&(tempY<(BufferWidth-1))&&(tempZ<(BufferHeight-1)))
		{
			int neighbourhood1 =  (tempX-1) + tempY*BufferWidth + tempZ*BufferLength*BufferWidth; 
			int neighbourhood2 =  (tempX+1) + tempY*BufferWidth + tempZ*BufferLength*BufferWidth; 
			int neighbourhood3 =  (tempX) + (tempY-1)*BufferWidth + tempZ*BufferLength*BufferWidth; 
			int neighbourhood4 =  (tempX) + (tempY+1)*BufferWidth + tempZ*BufferLength*BufferWidth; 
			int neighbourhood5 =  (tempX) + tempY*BufferWidth + (tempZ-1)*BufferLength*BufferWidth;
			int neighbourhood6 =  (tempX) + tempY*BufferWidth + (tempZ+1)*BufferLength*BufferWidth;
		}

		vVstore[index].setDensity(densityIP);

	}
} 

//================================================================
//polygon primitive start from a square cubic with 60*60*60
//then the cubic density was applied by formular
//density = fbm(P) + (1- P/Px - P/Py - P/Pz) 
//=======================================================
void normalSimulation::polygonPrimitive()
{
	 float disSquare = 0.0;
	 float distance = 0.0; 
	 float polygonDensity = 0.0; 
	 Perlin perPP (1,0.1,2.0,3);
	 for(int i = 0; i<1000000; i++)
	 {
		vVstore[i].setDensity(0); 
	 }
	 for(int i = 0; i<BufferLength; i++)
	 {
		 for(int j=0; j<BufferWidth; j++)
		 {
			 for(int k =0; k<BufferHeight; k++)
			 {	
				 if(((i>20)&&(i<80))&&((j>20)&&(j<80))&&((k>20)&&(k<80)))
				 {
					 disSquare = (float) ((i-50)*(i-50) + (j-50)*(j-50) + (k-50)*(k-50)); 
					 distance = sqrt(disSquare); 
					 polygonDensity = perPP.Get(i,j,k) + (1 - (float)(distance/(i*1.0)) - (float)(distance/(j*1.0)) - (float)(distance/(k*1.0)));
					 if(polygonDensity < 0)
					 {
						 polygonDensity = 0; 
					 }
					 index = k+j*BufferWidth+i*BufferWidth*BufferLength; 
					 vVstore[index].setDensity(polygonDensity); 
				 }
			 }
		 }
	 } 
}

//===============================================
//add multiple lights, one light is in the position
//(200,0,0) while another light is in the position
//(0,200,0)
//============================================
void normalSimulation::addLight()
{   
	//precompute the light value QF
	for(int i = -320; i< 320; ++i)
	{
		for(int j = -240; j< 240; ++j)
		{
			   a = (float) (200*200 + j*j + i*i); 
			   length = sqrt(a);
			   //calculate the corresponding step size in the x, y, z direction 
			   stepX = 200*step/length; 
			   stepY = i*step/length; 
			   stepZ = j*step/length;
			   //calculate step times
			   stepTime = (int) (length/step); 
			   //delcare delta Q
			   deltaQ1 = 0.0; 
			   //declare Q 
			   Q1 = 1.0;
			   //declare dentisty 
			   Density = 0.0;
			   for(int l= 1; l<= stepTime; ++l)
			   {
				    x = (float)(200-l*stepX); 
			        y = (float)(l*stepY); 
			        z = (float)(l*stepZ); 
					if((x>(0+xMove)&&x<(BufferLength+xMove))&&(y>(0+yMove)&&y<(BufferWidth+yMove))&&(z>(0+zMove)&&z<(BufferHeight+zMove)))
					{
						//convert x,y,z into integer
						voxelX = (int) (x-xMove);
						voxelY = (int) (y-yMove); 
						voxelZ = (int) (z-zMove);
					    index = (voxelX) +BufferWidth*(voxelY) + (voxelZ)*BufferWidth*BufferHeight; 
						Density = vVstore[index].getDensity(); 
						deltaQ1 = exp(-kapa*step*Density); 
                        Q1 *= deltaQ1; 	
						vQstore1[index]= Q1; 
					}
			   } 

			   a = (float) (200*200 + j*j + i*i); 
			   length = sqrt(a);
			   //calculate the corresponding step size in the x, y, z direction
			 //  stepX = (-200)*step/length; 
			   stepX = i*step/length; 
			   stepY = 200*step/length; 
			   stepZ = j*step/length;
			   //calculate step times
			   stepTime = (int) (length/step); 
			   //delcare delta Q
			   deltaQ2 = 0.0; 
			   //declare Q 
			   Q2 = 1.0;
			   //declare dentisty 
			   Density = 0.0;
			   for(int l= 1; l<= stepTime; ++l)
			   {  
				    //x = (float)(l*stepX+200); 
					x = (float)(l*stepX); 
			        y = (float)(200-l*stepY); 
			        z = (float)(l*stepZ); 
					if((x>(0+xMove)&&x<(BufferLength+xMove))&&(y>(0+yMove)&&y<(BufferWidth+yMove))&&(z>(0+zMove)&&z<(BufferHeight+zMove)))
					{
						//convert x,y,z into integer 
						voxelX = (int) (x-xMove);
						voxelY = (int) (y-yMove); 
						voxelZ = (int) (z-zMove);
					    index = (voxelX) +BufferWidth*(voxelY) + (voxelZ)*BufferWidth*BufferHeight; 
						Density = vVstore[index].getDensity(); 
						deltaQ2 = exp(-kapa*step*Density); 
                        Q2 *= deltaQ2; 	
						vQstore2[index]= Q2; 
					} 
			   }
		}
	} 
}

//============================================================
//raymatch the voxel to the image 
//the combination of the two lights is recieved by formula
//if(Q1+Q2<1)
//  Q= Q1+Q2
//else
//  Q = max (Q1, Q2)
//===========================================================
void normalSimulation::rayMatch()
{
	BMP output; 
	output.SetSize(640, 480);
	output.SetBitDepth (24);
	//ray match 
	for(int i = -320; i < 320; ++i)
	{
		for(int j= -240; j < 240; ++j)
		{
			//calculate and record the total length of the ray 
			a = (float) (i*i + j*j + 240*240); 
			length = sqrt(a); 
		    //the red color in the pixel 
			int redColor = 0; 
			//the green color in the pixel
			int greenColor = 0;
			//the blue color in the pixel 
			int blueColor = 0; 
			//calculate how many steps should go in the ray 
			stepTime = (int) (length/step);
			//density is used to record voxel density 
			Density = 0.0; 
			//define transmittance; 
			float Transmittance = 1.0;
			//deltaT is used to calculate transmittance 
			float deltaT = 0.0;
			//calculate the corresponding step size in the x, y, z direction
			stepX = i*step/length; 
			stepY = j*step/length;
			stepZ = 240*step/length;

			for(int k = 1; k <= stepTime; ++k)
			{
			   x = (float)(k*stepX); 
			   y = (float)(k*stepY); 
			   z = (float)(200.0-k*stepZ); 
               //conditional judgement to see if light is cast into the grid 
			   if((x>(0+xMove)&&x<(BufferLength+xMove))&&(y>(0+yMove)&&y<(BufferWidth+yMove))&&(z>(0+zMove)&&z<(BufferHeight+zMove)))
			   {
				   //convert x,y,z into integer
				   voxelX = (int) (x-xMove);
				   voxelY = (int) (y-yMove); 
				   voxelZ = (int) (z-zMove);
		           index = (voxelX)+ BufferWidth*(voxelY) + (voxelZ)*BufferWidth*BufferHeight; 
				   Density= vVstore[index].getDensity();
				   deltaT = exp(-kapa*step*Density);
				   Transmittance*=deltaT;  
				   if(Transmittance < exp(-6.0))
				   {
					   break; 
				   }
				  
			       //combine the light value here 
				   float tempQ1 = vQstore1[index]+vQstore2[index];
				   
				   if(tempQ1>1)
				   {
					   tempQ1 = max(vQstore1[index], vQstore2[index]);
				   }
				
				
				   redColor += (int)((1-deltaT)/kapa*(vVstore[index].getRedValue()*lightRedColor)*Transmittance*(tempQ1));
				   greenColor += (int)((1-deltaT)/kapa*(vVstore[index].getRedValue()*lightRedColor)*Transmittance*(tempQ1));
				   blueColor += (int)((1-deltaT)/kapa*(vVstore[index].getRedValue()*lightRedColor)*Transmittance*(tempQ1)); 
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
	    output.WriteToFile("BabysFirstCloudImage2.bmp");
	}else if (str == "test2.txt")
	{
		output.WriteToFile("GettingBetter.bmp");
	}if (str == "test3.txt")
	{
		output.WriteToFile("LastConfig.bmp");
	}if(str == "test4.txt")
	{
	    output.WriteToFile("instantiationPrimitive.bmp");
	}if(str == "test5.txt")
	{
	    output.WriteToFile("startingFromCubic.bmp");
	}
}

