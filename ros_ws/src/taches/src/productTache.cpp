/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include <ros/ros.h>
#include "productTache.h"


// Constructeur
ProductTache::ProductTache( int productJobTime, int ProductNumber)
{
	jobTime = productJobTime;
	productNumber = ProductNumber;
}

// Destructeur
ProductTache::~ProductTache(){}


