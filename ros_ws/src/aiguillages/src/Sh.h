#ifndef SH
#define SH

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <unistd.h>
#include <vrep_common/simRosEnablePublisher.h>
#include <vrep_common/simRosEnableSubscriber.h>


using namespace std;


//aiguillage 1->2
class Sh
{
private:
	int handle;
	float time;
	
	


public:
	Sh(int h,float t);
	int get_handle();
	float get_time();
	

};

#endif
