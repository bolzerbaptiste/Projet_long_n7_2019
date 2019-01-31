/**** Maxime Maurin - Projet Long N7 2017 ****/

#include <ros/ros.h>
#include "shuttle.h"


// Constructeur
Shuttle::Shuttle(std::string shuttleName, int shuttleDestination, int shuttleProduct, int shuttleHandler,int platformHandler,int shuttleStartZone)
{
	name = shuttleName;
	destination = shuttleDestination;
	product = shuttleProduct;
	handle = shuttleHandler;
	handlePlatform = platformHandler;
	zone = shuttleStartZone;
}

// Destructeur
Shuttle::~Shuttle(){}


