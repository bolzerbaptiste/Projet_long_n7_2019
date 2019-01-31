/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include "Poste1.h"

using namespace std;


void SensorCallback()
{
	cout<<"~~~~~~~~Capteur actif~~~~~~~~~~"<<endl;
}

// Initialisation du main
int main(int argc, char **argv)
{

// Récupération du chemin vers le Working_Folder, permet de travailler en chemin relatif
int count = 0 ;
int pos = 0 ;
std::string executionPath = argv[0];
while (count < 4) // le chemin sous linux est normalement standard d'où la présence de la constante 4, il est possible qu'il faille faire évoluer ce point si ce n'est plus le cas
	{
	if(executionPath[pos] == '/') count++;  // on cherche dans la chaine le 4ème '/' qui permet de récupérer le chemin absolu du Working Folder
	pos++;					// Cela est normalement garanti par le faite que le setup install toujours dans le dossier racine de l'utilisateur
	}
	
std::string Working_Folder = executionPath.substr(0,pos);
ROS_INFO ("$%s$", Working_Folder.c_str()) ;

	
//Initialisation des produits à l'aide du fichier de configuration

	//Définition du chemin du fichier de config et log
std::string configFile = Working_Folder + "/ProductConfiguration.config";
std::string logFile = Working_Folder + "/Statistic.txt";	

	
	// Initialisation du noeud ros et création d'un handle associé au noeud
	ros::init(argc, argv, "Poste1");	
	ros::NodeHandle nh;
	
	Poste1 Poste1(nh, argv[0]);

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
		cout <<"         Poste 1         "<<endl;
		cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		
	

	while (ros::ok()){

		if (!Poste1.handlesShuttlesMain.empty()){  // Si la liste contenant les n° des identifiants des navettes n'est pas vide

			// On lit la première ligne des listes
			num_handle.data = Poste1.handlesShuttlesMain.front();
			NextHandle = num_handle.data;
			destination.data = Poste1.destinationsShuttlesMain.front();
			NextDestination = destination.data;
			product.data = Poste1.productShuttlesMain.front();
			NextProduct = product.data;

			if(NextDestination == 1){
				while(Poste1.poste_libre==0){	// Tant que le poste n'est pas libre
					ros::spinOnce();	// Permet aux fonction callback de ros dans les objets d'êtres appelées
				}
			
				Poste1.poste_libre = 0;
				Poste1.ShStop.publish(Poste1.num_STOP); // Pour dire à la commande le numéro de l'actionneur stop à activer

				while(!Poste1.PS21){	// Tant que le capteur stop PS21 n'est pas actif
					ros::spinOnce();	
				}
		
				Poste1.PS21_past = Poste1.PS21;

	
				if(Poste1.tache==0){	
					if(Poste1.prod_recup==0){

						ROS_INFO("Navette presente au poste 1");	

						std::map<int,ProductPost*>::iterator it;
		
						it = Poste1.ProductsMap.find(NextProduct);	// find() améne l'itérateur à l'emplacement permetant la bonne clé

						// Teste si le produit présent doit être traité
						if (it != Poste1.ProductsMap.end()) {		// Vrai si l'itérateur n'est pas hors de la liste
						
							Poste1.pubPinOn.publish(Poste1.num_PIN);	// Sortir les ergots

		std::ofstream StatsFile(logFile.c_str(), std::ios::out | std::ios::app);
		if(StatsFile)  // si l'ouverture a réussi...
			{

			//ROS_INFO("Statistic.txt file ok");
			char logLine[1000];
			// Construction Ligne avec notamment la date de lancement 
			sprintf(logLine, "Produit entrain d'être traité au poste 1");
			StatsFile << logLine; // Ecriture dans le fichier 
		       	StatsFile.close();  // on referme le fichier Statistic.txt

			}

	       	else ROS_ERROR("Impossible de creer ou ouvrir le fichier Statistic.txt !");




							Poste1.pubProductInPost.publish(num_handle); //Publie l'handle de la navette à la commande
							Poste1.pubProductToTask.publish(product);	// Publie à tâche le n° du produit

							// Pour supprimer la première ligne des listes 'Main'
							Poste1.handlesShuttlesMain.pop_front();
							Poste1.destinationsShuttlesMain.pop_front();
							Poste1.productShuttlesMain.pop_front();

						}
						else{
							Poste1.ShStart.publish(Poste1.num_STOP);
							while(Poste1.PS21_past && Poste1.PS21){	// Attente du front descendant du capteur PS21
								ros::spinOnce();
							}

							Poste1.PS21_past = Poste1.PS21;
							Poste1.poste_libre = 1;
							ROS_WARN("Ce n'est pas le bon produit");	

							Poste1.pubSendShuttle.publish(num_handle); // Envoi handle de la navette à P2

							// Pour supprimer la première ligne des listes 
							Poste1.handlesShuttles.pop_front();
							Poste1.destinationsShuttles.pop_front();
							Poste1.productShuttles.pop_front();

							Poste1.handlesShuttlesMain.pop_front();
							Poste1.destinationsShuttlesMain.pop_front();
							Poste1.productShuttlesMain.pop_front();
						}
					}

					else{	
						ROS_INFO("Un produit est deja en court de traitement");	

						Poste1.ShStart.publish(Poste1.num_STOP);

						while(Poste1.PS21_past && Poste1.PS21){	// Attente du front descendant du capteur PS21
							ros::spinOnce();
						}

						Poste1.PS21_past = Poste1.PS21;
						Poste1.poste_libre = 1;

						Poste1.pubSendShuttle.publish(num_handle); // Envoi handle de la navette à P2
						
						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste1.handlesShuttles.pop_front();
						Poste1.destinationsShuttles.pop_front();
						Poste1.productShuttles.pop_front();

						Poste1.handlesShuttlesMain.pop_front();
						Poste1.destinationsShuttlesMain.pop_front();
						Poste1.productShuttlesMain.pop_front();
					}
				}

				else{	

					if(NextProduct==0){

						ROS_INFO("Navette vide presente");	
						
						empty_shuttle.data = 1;

						Poste1.pubPinOn.publish(Poste1.num_PIN);	// Sortir les ergots

						Poste1.pubEmptyShuttleReady.publish(num_handle); // Signale à la commande qu'une navette vide est présente

						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste1.handlesShuttlesMain.pop_front();
						Poste1.destinationsShuttlesMain.pop_front();
						Poste1.productShuttlesMain.pop_front();
					}

					else{

						ROS_INFO("Navette non vide - Redemarrage");	

						Poste1.ShStart.publish(Poste1.num_STOP);

						while(Poste1.PS21_past && Poste1.PS21){
							ros::spinOnce();
						}

						Poste1.PS21_past = Poste1.PS21;
						Poste1.poste_libre = 1;	

						Poste1.pubSendShuttle.publish(num_handle);  // Envoi handle de la navette à P2

						//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé				
						Poste1.handlesShuttles.pop_front();
						Poste1.destinationsShuttles.pop_front();
						Poste1.productShuttles.pop_front();

						Poste1.handlesShuttlesMain.pop_front();
						Poste1.destinationsShuttlesMain.pop_front();
						Poste1.productShuttlesMain.pop_front();
					}
				}
			}

			else{

				while(Poste1.poste_libre==0){
					ros::spinOnce();
				}
				ROS_INFO("Ne doit pas s'arreter en P1");	

				Poste1.poste_libre = 0;

				while(!Poste1.PS21){
					ros::spinOnce();
				}
		
				Poste1.PS21_past = Poste1.PS21;

				while(Poste1.PS21_past && Poste1.PS21){
					ros::spinOnce();
				}
			
				Poste1.PS21_past = Poste1.PS21;
				Poste1.poste_libre = 1;

				Poste1.pubSendShuttle.publish(num_handle);  // Envoi handle de la navette à P2

				//Suppression de la première ligne des listes qui correspond aux infos du handle envoyé
				Poste1.handlesShuttles.pop_front();
				Poste1.destinationsShuttles.pop_front();
				Poste1.productShuttles.pop_front();

				Poste1.handlesShuttlesMain.pop_front();
				Poste1.destinationsShuttlesMain.pop_front();
				Poste1.productShuttlesMain.pop_front();
			}
		}


		ros::spinOnce(); //permet aux fonction callback de ros dans les objets d'êtres appelées
		loop_rate.sleep(); //permet de synchroniser la boucle while. Il attend le temps qu'il reste pour faire le 25Hz (ou la fréquence indiquée dans le loop_rate)
	}

	return 0;

}



	

