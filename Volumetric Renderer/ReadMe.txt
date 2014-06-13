Homework 2, computer graphics(CIS 560)
Author: Shijing Liu

all the common parts and the extra credit parts have been finished for this 
homework. Two lights have been implemented in this program (extra credit 2). One is at the
position (200,0,0). Another is at the position (0, 200, 0). I have rendered 
five pictures:
1. BabyFirstCloudImage2.bmp
   This picture shows the volumetric rendering of a sphere. 

2. GettingBetter.bmp
   This picture shows the volumetric rendering of a cloud.  

3. LastConfig.bmp 
   This picture shows the volumetric rendering of two cloud and one pyroclastic

4. instantiationPrimitive.bmp (extra credit 1) 
   This picture shows the volumetric rendering of instantiation primitive on
   the basis of 216000 instantiation primitive 

5. startingfromcubic.bmp (extra credit 3) 
   this picture shows a cotton-like picture derived from a 60*60*60 cubic


The followings are the classes I have implemented:
1. point.cpp
This class implement some basic function for points, such as getX() and setX().
It is used for implementing the first extra credits, instiation primitive. 

2. voxel.cpp
voxel class is used to store voxel 

3. normalSimulation.cpp 
normalSimulation class is used to implement volumetric rendering and all the
primitives, including sphere, cloud, pyroclastic, instantiation primitive, 
polygon primitive.

 