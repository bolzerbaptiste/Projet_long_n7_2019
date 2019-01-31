/**** Bruno DATO, Abdellah ELGOURAIN, Evgeny SHULGA M1 EEA ISTR Université Paul Sabatier Toulouse III 2016 ****/

#ifndef API_sch
#define API_sch

#include <ros/ros.h> //librairie
#include <string> 
#include <iostream>
#include "automates/Entrees.h"
#include "automates/Sorties.h"

class API_schneider
{
private:

	ros::Publisher pub_entrees; //permet de publier sur topic ENTREE API
	ros::Subscriber sub_sorties; //permet de s'abonner au topic sorties API
	const char* adresse_ip;
	uint16_t entrees,sorties;

public:

	
	API_schneider(ros::NodeHandle noeud,const std::string num_API,const char* adresse_ip_api) ; //Contrusteur
	~API_schneider();	
	uint16_t get_register(int adresse_registre, int nombre_registres); //retourne le registre des entrees/capteurs
	void write_register(int adresse_registre, int nombre_registres,uint16_t registre); //ecrit le parametre registre sur la mem correspondant aux sorties/actionneurs
	void Callback(const automates::Sorties msg);  //pour publier sur le topic correspondant à l'API
	void publish(); //ca publie

};


#endif
