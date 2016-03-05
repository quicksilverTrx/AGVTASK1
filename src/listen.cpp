#include "ros/ros.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
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
using namespace cv;
using namespace std;
cv::Mat img=imread("/home/sourabha/catkin_ws/src/agv1/src/ps1.png",CV_LOAD_IMAGE_COLOR);


void pathCallback(const geometry_msgs::Point::ConstPtr &msg)// plots the points on the image 
{

  ROS_INFO("point received:[%d],[%d]",(int)msg->x,(int)msg->y);
  
  img.at<Vec3b>(msg->x,msg->y)[0]=255;
  img.at<Vec3b>(msg->x,msg->y)[1]=0;
  img.at<Vec3b>(msg->x,msg->y)[2]=0;

  imshow("mapped",img);
  
  waitKey(10);
}


int main(int argc, char **argv)
{
   ros::init(argc, argv, "listen");
   ros::NodeHandle t;
   ros::Subscriber sub = t.subscribe("chatter", 1000, pathCallback);
   ros::spin();
   return 0;
}
