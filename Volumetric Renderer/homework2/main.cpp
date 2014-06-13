//=========================
//Author: Shijing Liu
//Class: Main.cpp
//Basic Information:this class is used to organize different objects;
//it also makes some outputs and inputs 
//===========================================

#include "EasyBMP.h" 
#include "normalSimulation.h"
#include "TrilinearInterpolationSimulation.h"
#include "voxel.h"
#include <iostream>

using namespace std; 

int main() 
{ 

	cout<<endl;
	cout<<endl;

	normalSimulation S1 ("test1.txt",-20, -20, 30); 
	S1.Simulation();
	cout<<"done with test1"<<endl; 
	cout<<endl;
	cout<<endl;
	normalSimulation S2 ("test2.txt",-30, -30, 50); 
	S2.Simulation();
	cout<<"done with test2"<<endl;
	cout<<endl; 
	cout<<endl; 
	normalSimulation S3 ("test3.txt",-20, -20, 30); 
	S3.Simulation();
	cout<<"done with test3"<<endl;
	cout<<endl; 
	cout<<endl; 
	normalSimulation S4 ("test4.txt",-20, -20, 30); 
	S4.Simulation();
	cout<<"done with test4"<<endl;
	cout<<endl; 
	cout<<endl; 
	normalSimulation S5 ("test5.txt",-30, -30, 50); 
	S5.Simulation();
	cout<<"done with test5"<<endl;
	cout<<endl; 
	cout<<endl; 

}