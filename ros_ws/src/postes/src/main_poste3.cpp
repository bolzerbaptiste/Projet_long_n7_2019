/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include <ros/ros.h>
#include <unistd.h>
#include "Poste3.h"
#include <std_msgs/Int32.h>

using namespace std;

void SensorCallback()
{
	cout<<"~~~~~~~~Capteur actif~~~~~~~~~~"<<endl;
}


int main(int argc, char **argv)
{	

//initialisation du noeud ros et création d'un handle associé au noeud
	ros::init(argc, argv, "Poste3");	
	ros::NodeHandle nh;
	
	Poste3 Poste3(nh, argv[0]);

	ros::Rate loop_rate(25); //fréquence de la boucle 

	std_msgs::Int32 num_handle;
	std_msgs::Int32 destination;
	std_msgs::Int32 product;
	std_msgs::Int32 empty_shuttle;

	int NextDestination;
	int NextHandle;
	int NextProduct;

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

		cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		cout <<"         Poste 3         "<<endl;
		cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		
	

	while (ros::ok()){

		if (!Poste3.handlesShuttlesMain.empty()){

			// On lit la première ligne des listes
			num_handle.data = Poste3.handlesShuttlesMain.front();
			NextHandle = num_handle.data;
			destination.data = Poste3.destinationsShuttlesMain.front();
			NextDestination = destination.data;
			product.data = Poste3.productShuttlesMain.front();
			NextProduct = product.data;


			if(NextDestination == 3){
				while(Poste3.poste_libre==0){
					ros::spinOnce();	// Pour lire les fonctions Callback
				}
			
				Poste3.poste_libre = 0;
				Poste3.ShStop.publish(Poste3.num_STOP);

				while(!Poste3.PS2){
					ros::spinOnce();
				}
		
				Poste3.PS2_past = Poste3.PS2;


	
				if(Poste3.tache==0){
					if(Poste3.prod_recup==0){

						ROS_INFO("Navette presente au poste 3");		

						std::map<int,ProductPost*>::iterator it;
		
						it = Poste3.ProductsMap.find(NextProduct);	// find() améne l'itérateur à l'emplacement permetant la bonne clé

						if (it != Poste3.ProductsMap.end()) {		// Vrai si l'itérateur n'est pas hors de la liste
							
							Poste3.pubPinOn.publish(Poste3.num_PIN);	// Sortir les ergots					

							Poste3.pubProductInPost.publish(num_handle);
							Poste3.pubProductToTask.publish(product);

							Poste3.handlesShuttlesMain.pop_front();
							Poste3.destinationsShuttlesMain.pop_front();
							Poste3.productShuttlesMain.pop_front();
						}

						else{

							Poste3.ShStart.publish(Poste3.num_STOP);
							while(Poste3.PS2_past && Poste3.PS2){	// Attente du front descendant du capteur PS2
								ros::spinOnce();
							}

							Poste3.PS2_past = Poste3.PS2;
							Poste3.poste_libre = 1;
							ROS_WARN("Ce n'est pas le bon produit");	



							Poste3.pubSendShuttle.publish(num_handle); // Envoi handle de la navette à P4

							Poste3.handlesShuttles.pop_front();
							Poste3.destinationsShuttles.pop_front();
							Poste3.productShuttles.pop_front();

							Poste3.handlesShuttlesMain.pop_front();
							Poste3.destinationsShuttlesMain.pop_front();
							Poste3.productShuttlesMain.pop_front();
						}
					}

					else{	

						ROS_INFO("Un produit est deja en court de traitement");		

						Poste3.ShStart.publish(Poste3.num_STOP);

						while(Poste3.PS2_past && Poste3.PS2){	// Attente du front descendant du capteur PS2
							ros::spinOnce();
						}

						Poste3.PS2_past = Poste3.PS2;
						Poste3.poste_libre = 1;

						Poste3.pubSendShuttle.publish(num_handle); // Envoi handle de la navette à P4
						
						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste3.handlesShuttles.pop_front();
						Poste3.destinationsShuttles.pop_front();
						Poste3.productShuttles.pop_front();

						Poste3.handlesShuttlesMain.pop_front();
						Poste3.destinationsShuttlesMain.pop_front();
						Poste3.productShuttlesMain.pop_front();

					}
				}

				else{	

					if(NextProduct==0){

						ROS_INFO("Navette vide presente");	
						
						empty_shuttle.data = 1;

						Poste3.pubPinOn.publish(Poste3.num_PIN);	// Sortir les ergots

						Poste3.pubEmptyShuttleReady.publish(num_handle);

						Poste3.handlesShuttlesMain.pop_front();
						Poste3.destinationsShuttlesMain.pop_front();
						Poste3.productShuttlesMain.pop_front();
					}

					else{

						ROS_INFO("Navette non vide - Redemarrage");

						Poste3.ShStart.publish(Poste3.num_STOP);

						while(Poste3.PS2_past && Poste3.PS2){
							ros::spinOnce();
						}

						Poste3.PS2_past = Poste3.PS2;
						Poste3.poste_libre = 1;	

						Poste3.pubSendShuttle.publish(num_handle);  // Envoi handle de la navette à P4

						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste3.handlesShuttles.pop_front();
						Poste3.destinationsShuttles.pop_front();
						Poste3.productShuttles.pop_front();

						Poste3.handlesShuttlesMain.pop_front();
						Poste3.destinationsShuttlesMain.pop_front();
						Poste3.productShuttlesMain.pop_front();
					}
				}
			}

			else{

				while(Poste3.poste_libre==0){
					ros::spinOnce();
				}

				ROS_INFO("Ne doit pas s'arreter en P3");	

				Poste3.poste_libre = 0;

				while(!Poste3.PS2){
					ros::spinOnce();
				}
		
				Poste3.PS2_past = Poste3.PS2;

				while(Poste3.PS2_past && Poste3.PS2){
					ros::spinOnce();
				}
			
				Poste3.PS2_past = Poste3.PS2;
				Poste3.poste_libre = 1;

				Poste3.pubSendShuttle.publish(num_handle);  // Envoi handle de la navette à P4

				//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé
				Poste3.handlesShuttles.pop_front();
				Poste3.destinationsShuttles.pop_front();
				Poste3.productShuttles.pop_front();

				Poste3.handlesShuttlesMain.pop_front();
				Poste3.destinationsShuttlesMain.pop_front();
				Poste3.productShuttlesMain.pop_front();
			}
		}


		ros::spinOnce(); //permet aux fonction callback de ros dans les objets d'êtres appelées
		loop_rate.sleep(); //permet de synchroniser la boucle while. Il attend le temps qu'il reste pour faire le 25Hz (ou la fréquence indiquée dans le loop_rate)
	}

	return 0;

}



	

