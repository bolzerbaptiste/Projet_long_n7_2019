/**** Maxime Maurin - Projet Long N7 2017 ****/

#ifndef PRODUCT
#define PRODUCT

#include <ros/ros.h>
#include <string.h>


class Product
{
public:
	
	std::string name;
	int firstDestination;
	int productNumber;
	int manRangeSize;

	Product(std::string productName, int productFirstDestination, int initProductNumber,int productManRangeSize);
	~Product();

};



#endif
