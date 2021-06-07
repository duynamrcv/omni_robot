# 3-Wheeled Omni-directional Mobie robot
## Download and Installation
```
$ mkdir -p catkin_ws/src
$ cd catkin_ws/src
$ git clone https://github.com/duynamrcv/omni_robot.git
$ cd ..
$ catkin_make
```
## Simulation on Gazebo
```
roslaunch omni_gazebo gazebo.launch
```
## Teleop controller
```
rosrun omni_teleop teleop
```
## Topic
### Subscriber
* cmd_vel <```geometry_msgs/Twist```>
