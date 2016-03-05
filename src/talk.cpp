#include "ros/ros.h"

#include "geometry_msgs/Point.h"
#include <stack>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include<iostream>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sstream>
#include <typeinfo>

using namespace cv;
using namespace std;
cv::Mat img=imread("/home/sourabha/catkin_ws/src/agv1/src/ps1.png",CV_LOAD_IMAGE_COLOR);
int flag[200][200]={0};
std::stack<int> ax;
std::stack<int> ay;
std::stack<int> axv;
std::stack<int> ayv;

int xr,yr,xg,yg;
double cal(int x, int y)  //calculates distance between two points
 { 
   return sqrt(((x-xg)*(x-xg)+(y-yg)*(y-yg)));
 }

int valid(int x,int y)       //checks whether the point exists in the given image
{
	if(x<img.rows&&y<img.cols&&x>0&&y>0)
	return 1;
	else
	return 0;
}

int main(int argc,char **argv)
{ 
  CvScalar s,c;
  int x1,y1,x2,y2,count1=0,count2=0;
  ros::init(argc, argv, "talk");
  ros::NodeHandle t;
  ros::Publisher chatter_pub = t.advertise<geometry_msgs::Point>("chatter",1000); //instead of path,name of my topic is chatter
  ros::Rate loop_rate(10);
  for(int y=0;y<img.rows;y++) // This segment to find start and end points 
	{
		for(int x=0;x<img.cols;x++)
		{ 
			const cv::Vec3b& s = img.at<cv::Vec3b>(y, x);

		    for(int c = 0; c < 3; ++c) 
		    {
			   unsigned int pxl_val = (unsigned int)s.val[c];
			   if(c==1)
			   { 
			     if(pxl_val==255) //finding green pixel
			     { 
				 if(count2==0)
				   {
					 x2=x;
					 y2=y;
					
					 
				   }
			     }
		       }
			   if(c==2)
			   {
		        if(pxl_val<240&&pxl_val>236)
			    {
				 if(count1==0)
				  {
					 x1=x;
					 y1=y;
					count1=0;
				  }
     			}		
    		  }
		}
		xr=x1;// storing the start and end points
		yr=y1;
		xg=x2;
		yg=y2;
	  
		axv.push(xr);//this stack used for storing path
		ayv.push(yr);	
	   }
	}
	
	int flag1=0;
    int c1=1,k=0;
    int i,j,a,b,cnt=1;
    double dm=10000.0;

while(!(ayv.top()==yg&&axv.top()==xg)) //path finding algorithm based on shortest distance .
  {  
  flag[ayv.top()][axv.top()]=1;
  for(i=ayv.top()-1;i<=ayv.top()+1;i++)
    {
     for(j=axv.top()-1;j<=axv.top()+1;j++)
       { 
		 if(valid(i,j)==1&&flag[i][j]==0&&!(img.at<Vec3b>(i,j).val[0]==255&&img.at<Vec3b>(i,j).val[1]==255&&img.at<Vec3b>(i,j).val[2]==255))
     	   { 
     	     if(cal(j,i)<dm)    // compares the distances of each neighbouring cell and moves to the lowest distance cell ( a bit like dijkstra)
      		  {                  //process continues for each cell where the distances(from destination) of neighbouring cells are calculated and the lowest is moved to 
     			dm=cal(j,i);
     			a=j;
     			b=i;
     			flag1=1;
     		  }
     	   }
       }
   }
   if(flag1==1)  // finds whether a closer cell has been obtained 
   {
	 axv.push(a); //path stack
     ayv.push(b);   //path stack
     flag1=0;
   } 			
   else  // other moves or backtracks to previous cell (unvisited) 
   {
     ayv.pop();  // rejects unwanted cells
     axv.pop();
   }
   dm=10000.0;
}
  while(!(axv.top()==xr&&ayv.top()==yr)) // reversing the stacks so that path is obtained  
  {
    ax.push(axv.top()); // uses a temporary stack to reverse 
    ay.push(ayv.top()); // uses a temporary stack to reverse 
    axv.pop();
    ayv.pop();
   }
  while(!(axv.top()==xg&&ayv.top()==yg)) // printing path
  {
     axv.push(ax.top()); // this stack stores the columns values of path 
     ayv.push(ay.top());  // this stack stores the row values of path 
     ax.pop();    // at the end stack ax and ay have no use just used as a temporary container for reversing stacks 
     ay.pop();
     geometry_msgs::Point t;
     t.x=ayv.top();
     t.y=axv.top();
     chatter_pub.publish(t);
     ROS_INFO("point sent:[%d,%d]",(int)t.x,(int)t.y);
     ros::spinOnce();
     loop_rate.sleep();
 }

 
	 return 0;
}

