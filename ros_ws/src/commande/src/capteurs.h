/**** Bruno DATO, Abdellah ELGOURAIN, Evgeny SHULGA M1 EEA ISTR Université Paul Sabatier Toulouse III 2016 ****/

#ifndef CAPT
#define CAPT

#include <commande_locale/Msg_SensorState.h>
#include "commande/Capteurs.h"
#include <ros/ros.h>


class Capteurs
{
private:

	ros::Subscriber sub_capteurs_ligne,sub_capteurs_simu;

public:
	
	bool PSx[25],DxD[13],DxG[13],CPx[11],CPIx[9];
	bool SIMULATION, LIGNE ; // Indicateurs simulation ou ligne
	Capteurs(ros::NodeHandle noeud);
	~Capteurs();

	void Actualiser(bool PS[],bool DD[],bool DG[],bool CP[],bool CPI[]);

	void Callback_capteurs_ligne(const commande::Capteurs msg);
	void Callback_capteurs_simulation(const commande_locale::Msg_SensorState::ConstPtr& msg);

	void Actualiser_PSx(long int CAPTEURS);
	void Actualiser_DxD(long int CAPTEURS);
	void Actualiser_DxG(long int CAPTEURS);
	void Actualiser_CPx(long int CAPTEURS);
	void Actualiser_CPIx(long int CAPTEURS);


};


// Outils divers //

bool MASK(long int registre,int numero_bit);









#endif
