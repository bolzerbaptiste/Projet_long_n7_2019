/**** Maxime Maurin - Projet Long N7 2017 ****/

#ifndef SHUTTLE
#define SHUTTLE

#include <ros/ros.h>
#include "string.h"


class Shuttle
{
public:
	
	std::string name;
	int destination;
	int product;
	int handle;
	int handlePlatform;
	int zone;

	Shuttle(std::string shuttleName, int shuttleDestination, int shuttleProduct, int shuttleHandler,int platformHandler,int shuttleStartZone);
	~Shuttle();

};



#endif
