#include <iostream>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

/*Library from my Github --> /LuisGerar321 */
#include <utils/PDControl.h> 


double x, y, my_out;


void Odometry_Callback(const nav_msgs::Odometry::ConstPtr& data){
	x = data->pose.pose.position.x;
	y = data->pose.pose.position.y;
	std::cout<<"x_coord: "<<x<<"\ty_coord: "<<y<<std::endl;
}

int main(int argc, char** argv){

	ros::init(argc, argv,"DistanceMeterX");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("/mobile_base_controller/odom",2,Odometry_Callback); // "/mobile_base_controller/odom" -> "/odom"
	ros::Rate rate(30);

	ros::Publisher pub_vel = n.advertise<geometry_msgs::Twist>("/mobile_base_controller/cmd_vel", 2); // "/mobile_base_controller/cmd_vel" -> "/cmd_vel"
	geometry_msgs::Twist velocity;

	PD_Control_Class LinearControl(std::stod(argv[1]), 1.7, 1.5, 0.0007, 0.7);
	LinearControl.start_control();

	while(ros::ok()){
		system("clear");
		std::cout<<"Distance position pd controler with input = "<<std::stod(argv[1])<<std::endl;
		my_out = LinearControl.PD_Control(x); 
		velocity.linear.x = my_out;
		if(LinearControl.success_pd){
			return EXIT_SUCCESS;
		}
		pub_vel.publish(velocity); 
		ros::spinOnce();
		rate.sleep();
	}
	return EXIT_SUCCESS;
}