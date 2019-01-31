/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include <ros/ros.h>
#include <unistd.h>
#include "Poste4.h"
#include <std_msgs/Int32.h>

using namespace std;


void SensorCallback()
{
	cout<<"~~~~~~~~Capteur actif~~~~~~~~~~"<<endl;
}


int main(int argc, char **argv)
{	

//initialisation du noeud ros et création d'un handle associé au noeud
	ros::init(argc, argv, "Poste4");	
	ros::NodeHandle nh;
	
	Poste4 Poste4(nh, argv[0]);

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
		cout <<"         Poste 4         "<<endl;
		cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		
	

	while (ros::ok()){

		if (!Poste4.handlesShuttlesMain.empty()){

			// On lit la première ligne des listes
			num_handle.handle = Poste4.handlesShuttlesMain.front();
			handle.data = num_handle.handle;
			NextHandle = num_handle.handle;
			destination.data = Poste4.destinationsShuttlesMain.front();
			NextDestination = destination.data;
			product.data = Poste4.productShuttlesMain.front();
			NextProduct = product.data;

			if(NextDestination == 4){
				while(Poste4.poste_libre==0){
					ros::spinOnce();	// Pour lire les fonctions Callback
				}
			
				Poste4.poste_libre = 0;
				Poste4.ShStop.publish(Poste4.num_STOP);

				while(!Poste4.PS3){
					ros::spinOnce();
				}
		
				Poste4.PS3_past = Poste4.PS3;

	
				if(Poste4.tache==0){
					if(Poste4.prod_recup==0){

						ROS_INFO("Navette presente au poste 4");		

						std::map<int,ProductPost*>::iterator it;
		
						it = Poste4.ProductsMap.find(NextProduct);	// find() améne l'itérateur à l'emplacement permetant la bonne clé

						if (it != Poste4.ProductsMap.end()) {		// Vrai si l'itérateur n'est pas hors de la liste
						
							Poste4.pubPinOn.publish(Poste4.num_PIN);	// Sortir les ergots

							Poste4.pubProductInPost.publish(handle);
							Poste4.pubProductToTask.publish(product);

							Poste4.handlesShuttlesMain.pop_front();
							Poste4.destinationsShuttlesMain.pop_front();
							Poste4.productShuttlesMain.pop_front();

						}
						else{
							Poste4.ShStart.publish(Poste4.num_STOP);
							while(Poste4.PS3_past && Poste4.PS3){	// Attente du front descendant du capteur PS3
								ros::spinOnce();
							}

							Poste4.PS3_past = Poste4.PS3;
							Poste4.poste_libre = 1;
							ROS_WARN("Ce n'est pas le bon produit");	



							Poste4.pubSendShuttle.publish(num_handle); // Envoi handle de la navette à A2

							Poste4.handlesShuttles.pop_front();
							Poste4.destinationsShuttles.pop_front();
							Poste4.productShuttles.pop_front();

							Poste4.handlesShuttlesMain.pop_front();
							Poste4.destinationsShuttlesMain.pop_front();
							Poste4.productShuttlesMain.pop_front();
						}
					}

					else{	

						ROS_INFO("Un produit est deja en court de traitement");		

						Poste4.ShStart.publish(Poste4.num_STOP);

						while(Poste4.PS3_past && Poste4.PS3){	// Attente du front descendant du capteur PS3
							ros::spinOnce();
						}

						Poste4.PS3_past = Poste4.PS3;
						Poste4.poste_libre = 1;

						Poste4.pubSendShuttle.publish(num_handle); // Envoi handle de la navette à A2
						
						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste4.handlesShuttles.pop_front();
						Poste4.destinationsShuttles.pop_front();
						Poste4.productShuttles.pop_front();

						Poste4.handlesShuttlesMain.pop_front();
						Poste4.destinationsShuttlesMain.pop_front();
						Poste4.productShuttlesMain.pop_front();

					}
				}

				else{	

					if(NextProduct==0){

						ROS_INFO("Navette vide presente");	
						
						empty_shuttle.data = 1;
						
						Poste4.pubPinOn.publish(Poste4.num_PIN);	// Sortir les ergots

						Poste4.pubEmptyShuttleReady.publish(handle);

						Poste4.handlesShuttlesMain.pop_front();
						Poste4.destinationsShuttlesMain.pop_front();
						Poste4.productShuttlesMain.pop_front();
					}

					else{

						ROS_INFO("Navette non vide - Redemarrage");

						Poste4.ShStart.publish(Poste4.num_STOP);

						while(Poste4.PS3_past && Poste4.PS3){
							ros::spinOnce();
						}

						Poste4.PS3_past = Poste4.PS3;
						Poste4.poste_libre = 1;	

						Poste4.pubSendShuttle.publish(num_handle);  // Envoi handle de la navette à A2

						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste4.handlesShuttles.pop_front();
						Poste4.destinationsShuttles.pop_front();
						Poste4.productShuttles.pop_front();

						Poste4.handlesShuttlesMain.pop_front();
						Poste4.destinationsShuttlesMain.pop_front();
						Poste4.productShuttlesMain.pop_front();
					}
				}
			}

			else{

				while(Poste4.poste_libre==0){
					ros::spinOnce();
				}

				ROS_INFO("Ne doit pas s'arreter en P4");	

				Poste4.poste_libre = 0;

				while(!Poste4.PS3){
					ros::spinOnce();
				}
		
				Poste4.PS3_past = Poste4.PS3;

				while(Poste4.PS3_past && Poste4.PS3){
					ros::spinOnce();
				}
			
				Poste4.PS3_past = Poste4.PS3;
				Poste4.poste_libre = 1;

				Poste4.pubSendShuttle.publish(num_handle);  // Envoi handle de la navette à A2

				//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé
				Poste4.handlesShuttles.pop_front();
				Poste4.destinationsShuttles.pop_front();
				Poste4.productShuttles.pop_front();

				Poste4.handlesShuttlesMain.pop_front();
				Poste4.destinationsShuttlesMain.pop_front();
				Poste4.productShuttlesMain.pop_front();
			}
		}


		ros::spinOnce(); //permet aux fonction callback de ros dans les objets d'êtres appelées
		loop_rate.sleep(); //permet de synchroniser la boucle while. Il attend le temps qu'il reste pour faire le 25Hz (ou la fréquence indiquée dans le loop_rate)
	}

	return 0;

}



	

