/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#ifndef PRODUCT
#define PRODUCT

#include <ros/ros.h>
#include <string.h>


class ProductPost
{
public:
	
	int nextDestination;
	int productNumber;

	ProductPost( int productNextDestination, int ProductNumber);
	~ProductPost();

};



#endif
