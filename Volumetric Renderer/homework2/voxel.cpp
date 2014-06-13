//=========================
//Author: Shijing Liu
//Class: voxel.cpp
//Basic Information:this is voxel class deal with 
//write color, read color, write density, read density 
//===========================================

#include <iostream>
#include "voxel.h"
using namespace std; 

voxel::voxel()
{
}

//read density 
float voxel::getDensity()
{
	return density; 
}

//read red
float voxel::getRedValue()
{
	return red; 
}

//read green
float voxel::getGreenValue()
{
	return green; 
}

//read blue 
float voxel::getBlueValue()
{
	return blue; 
}

//read background color 
float voxel::getBackRedValue()
{
	return backRedColor; 
}

float voxel::getBackGreenValue()
{
	return backGreenColor; 
}

float voxel::getBackBlueValue()
{
	return backBlueColor; 
}

//write density 
void voxel:: setDensity (float newDensity)
{
	density= newDensity; 
}

//write red 
void voxel::setRedValue(float Red)
{
	red = Red; 
}

//write green
void voxel::setGreenValue(float Green)
{
	green = Green; 
}

//write blue 
void voxel::setBlueValue(float Blue)
{
	blue = Blue; 
}

//write red 
void voxel::setBackRedValue(float BackRedColor)
{
	backRedColor = BackRedColor; 
}

//write green
void voxel::setBackGreenValue(float BackGreenColor)
{
	backGreenColor = BackGreenColor; 
}

//write blue 
void voxel::setBackBlueValue(float BackBlueColor)
{
	backBlueColor = BackBlueColor; 
}