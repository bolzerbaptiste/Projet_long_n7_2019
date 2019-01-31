/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include <ros/ros.h>
#include <unistd.h>
#include "Poste2.h"
#include <std_msgs/Int32.h>

using namespace std;


void SensorCallback()
{
	cout<<"~~~~~~~~Capteur actif~~~~~~~~~~"<<endl;
}


int main(int argc, char **argv)
{	

//initialisation du noeud ros et création d'un handle associé au noeud
	ros::init(argc, argv, "Poste2");	
	ros::NodeHandle nh;
	
	Poste2 Poste2(nh, argv[0]);

	ros::Rate loop_rate(25); //fréquence de la boucle 

 	aiguillages::ExchangeSh num_handle;
	std_msgs::Int32 handle;
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
		cout <<"         Poste 2         "<<endl;
		cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		
	

	while (ros::ok()){

		if (!Poste2.handlesShuttlesMain.empty()){

			// On lit la première ligne des listes
			num_handle.handle = Poste2.handlesShuttlesMain.front();
			handle.data = num_handle.handle;
			NextHandle = num_handle.handle;
			destination.data = Poste2.destinationsShuttlesMain.front();
			NextDestination = destination.data;
			product.data = Poste2.productShuttlesMain.front();
			NextProduct = product.data;

			if(NextDestination == 2){
				while(Poste2.poste_libre==0){
					ros::spinOnce();	// Pour lire les fonctions Callback
				}
			
				Poste2.poste_libre = 0;
				Poste2.ShStop.publish(Poste2.num_STOP);

				while(!Poste2.PS22){
					ros::spinOnce();
				}
		
				Poste2.PS22_past = Poste2.PS22;

	
				if(Poste2.tache==0){
					if(Poste2.prod_recup==0){

						ROS_INFO("Navette presente au poste 2");		

						std::map<int,ProductPost*>::iterator it;
		
						it = Poste2.ProductsMap.find(NextProduct);	// find() améne l'itérateur à l'emplacement permetant la bonne clé

						if (it != Poste2.ProductsMap.end()) {		// Vrai si l'itérateur n'est pas hors de la liste
						
							Poste2.pubPinOn.publish(Poste2.num_PIN);	// Sortir les ergots
							
							Poste2.pubProductInPost.publish(handle);
							Poste2.pubProductToTask.publish(product);

							Poste2.handlesShuttlesMain.pop_front();
							Poste2.destinationsShuttlesMain.pop_front();
							Poste2.productShuttlesMain.pop_front();

						}
						else{
							
							Poste2.ShStart.publish(Poste2.num_STOP);
							while(Poste2.PS22_past && Poste2.PS22){	// Attente du front descendant du capteur PS22
								ros::spinOnce();
							}

							Poste2.PS22_past = Poste2.PS22;
							Poste2.poste_libre = 1;
							ROS_WARN("Ce n'est pas le bon produit");	



							Poste2.pubSendShuttle.publish(num_handle); // Envoi handle de la navette à A12

							Poste2.handlesShuttles.pop_front();
							Poste2.destinationsShuttles.pop_front();
							Poste2.productShuttles.pop_front();

							Poste2.handlesShuttlesMain.pop_front();
							Poste2.destinationsShuttlesMain.pop_front();
							Poste2.productShuttlesMain.pop_front();
						}
					}

					else{	

						ROS_INFO("Un produit est deja en court de traitement");		

						Poste2.ShStart.publish(Poste2.num_STOP);

						while(Poste2.PS22_past && Poste2.PS22){	// Attente du front descendant du capteur PS22
							ros::spinOnce();
						}

						Poste2.PS22_past = Poste2.PS22;
						Poste2.poste_libre = 1;

						Poste2.pubSendShuttle.publish(num_handle); // Envoi handle de la navette à A12
						
						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste2.handlesShuttles.pop_front();
						Poste2.destinationsShuttles.pop_front();
						Poste2.productShuttles.pop_front();

						Poste2.handlesShuttlesMain.pop_front();
						Poste2.destinationsShuttlesMain.pop_front();
						Poste2.productShuttlesMain.pop_front();

					}
				}

				else{	
					
					if(NextProduct==0){
						
						ROS_INFO("Navette vide presente");	
						
						empty_shuttle.data = 1;
						Poste2.pubPinOn.publish(Poste2.num_PIN);	// Sortir les ergots

						Poste2.pubEmptyShuttleReady.publish(handle);

						Poste2.handlesShuttlesMain.pop_front();
						Poste2.destinationsShuttlesMain.pop_front();
						Poste2.productShuttlesMain.pop_front();
					}

					else{

						ROS_INFO("Navette non vide - Redemarrage");

						Poste2.ShStart.publish(Poste2.num_STOP);

						while(Poste2.PS22_past && Poste2.PS22){
							ros::spinOnce();
						}

						Poste2.PS22_past = Poste2.PS22;
						Poste2.poste_libre = 1;	

						Poste2.pubSendShuttle.publish(num_handle);  // Envoi handle de la navette à A12

						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste2.handlesShuttles.pop_front();
						Poste2.destinationsShuttles.pop_front();
						Poste2.productShuttles.pop_front();

						Poste2.handlesShuttlesMain.pop_front();
						Poste2.destinationsShuttlesMain.pop_front();
						Poste2.productShuttlesMain.pop_front();
					}
				}
			}

			else{
				
				while(Poste2.poste_libre==0){
					ros::spinOnce();
				}

				ROS_INFO("Ne doit pas s'arreter en P2");	

				Poste2.poste_libre = 0;

				while(!Poste2.PS22){
					ros::spinOnce();
				}
		
				Poste2.PS22_past = Poste2.PS22;

				while(Poste2.PS22_past && Poste2.PS22){
					ros::spinOnce();
				}
			
				Poste2.PS22_past = Poste2.PS22;
				Poste2.poste_libre = 1;

			
				Poste2.pubSendShuttle.publish(num_handle);  // Envoi handle de la navette à A12

				//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé
				Poste2.handlesShuttles.pop_front();
				Poste2.destinationsShuttles.pop_front();
				Poste2.productShuttles.pop_front();

				Poste2.handlesShuttlesMain.pop_front();
				Poste2.destinationsShuttlesMain.pop_front();
				Poste2.productShuttlesMain.pop_front();
			}
		}


		ros::spinOnce(); //permet aux fonction callback de ros dans les objets d'êtres appelées
		loop_rate.sleep(); //permet de synchroniser la boucle while. Il attend le temps qu'il reste pour faire le 25Hz (ou la fréquence indiquée dans le loop_rate)
	}

	return 0;

}



	

