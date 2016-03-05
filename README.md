# AGVTASK1
Path planning 
Prerequisites:
1.opencv (preferably >2.4) must be installed 

2.ROS INDIGO must be installed

Working procedure :
1.clone this repository in a suitable destination (src folder )in catkin workspace

2.open listen.cpp and talk.cpp in your favourite text editor 

3.Change the following line :
  
  cv::Mat img=imread("/home/sourabha/catkin_ws/src/AGVTASK1/src/ps1.png",CV_LOAD_IMAGE_COLOR);

  to 

  cv::Mat img=imread("/home/<username>/<catkin workspace>/src/AGVTASK1/src/ps1.png",CV_LOAD_IMAGE_COLOR);
  

4.In catkin_ws directory source the setup.bash file by 

   " $ source devel/setup.bash"

5 $ catkin_make

6 $ roscore

7 $ rosrun AGVTASK1 listen

8 $ rosrun AGVTASK1 talk
