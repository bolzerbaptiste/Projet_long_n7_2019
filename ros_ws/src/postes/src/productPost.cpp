/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include <ros/ros.h>
#include "productPost.h"


// Constructeur
ProductPost::ProductPost( int productNextDestination, int ProductNumber)
{
	nextDestination = productNextDestination;
	productNumber = ProductNumber;
}

// Destructeur
ProductPost::~ProductPost(){}


