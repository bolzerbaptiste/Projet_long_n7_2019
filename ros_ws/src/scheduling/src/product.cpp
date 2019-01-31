/**** Maxime Maurin - Projet Long N7 2017 ****/

#include <ros/ros.h>
#include "product.h"


// Constructeur
Product::Product(std::string productName, int productFirstDestination, int initProductNumber,int productManRangeSize)
{
	name = productName;
	firstDestination = productFirstDestination;
	productNumber = initProductNumber;
	manRangeSize = productManRangeSize;
}

// Destructeur
Product::~Product(){}


