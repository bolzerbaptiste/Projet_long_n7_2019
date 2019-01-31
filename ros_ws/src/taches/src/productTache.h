/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#ifndef PRODUCT
#define PRODUCT

#include <ros/ros.h>
#include <string.h>


class ProductTache
{
public:
	
	int jobTime;
	int productNumber;

	ProductTache( int productJobTime, int ProductNumber);
	~ProductTache();

};



#endif
