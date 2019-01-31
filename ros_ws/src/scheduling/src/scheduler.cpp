/**** Maxime Maurin - Projet Long N7 2017 ****/

#include <ros/ros.h>
#include "scheduler.h"

// Construteur
Scheduler::Scheduler()
{
	// Initilisation de quelques valeurs par défaut
	numberOfProduct = 0;
	nextCount = 0;
	lastLaunchDate = 0;
	maxShuttleNumber = 6;
	init_var = true;
	for(int i=0; i<100; i++) {
		nom_produits[i]= "NULL";
	}
}

// Initialisation de l'objet 
bool Scheduler::init(ros::NodeHandle nh, std::string executionPath)
{
	// Services Initialisation
	client_simRosGetInfo = nh.serviceClient<vrep_common::simRosGetInfo>("/vrep/simRosGetInfo");
	client_GetShuttleStatus = nh.serviceClient<shuttles::srvGetShuttleStatus>("/commande_navette/srvGetShuttleStatus");
	// Subscribers Initialisation
	subEndOfProductManufacture = nh.subscribe("/A3/ShuttleOut", 10 , &Scheduler::productOutCallBack,this);
	subManualLaunchOfProduct = nh.subscribe("/scheduling/ManualLaunch", 10 , &Scheduler::ManualLaunchCallBack,this);
	// Publishers Initialisation
	pubCreateShuttle = nh.advertise<scheduling::Msg_LoadShuttle>("/scheduling/NextProduct",10);
	pubDelShuttle = nh.advertise<std_msgs::Int32>("/commande_navette/DelShuttle",10);

	pubNombreDeProduits = nh.advertise<std_msgs::Int32>("/ordonnancement/NombreDeProduits",10);
	pubNomProduits = nh.advertise<std_msgs::String>("/ordonnancement/NomProduits",100);

	// Récupération du chemin vers le Working_Folder, permet de travailler en chemin relatif
	int count = 0 ;
	int pos = 0 ;
	while (count < 4) // le chemin sous linux est normalement standard d'où la présence de la constante 4, il est possible qu'il faille faire évoluer ce point si ce n'est plus le cas
		{
		if(executionPath[pos] == '/') count++;  // on cherche dans la chaine le 4ème '/' qui permet de récupérer le chemin absolu du Working Folder
		pos++;					// Cela est normalement garanti par le faite que le setup install toujours dans le dossier racine de l'utilisateur
		}
	
	std::string Working_Folder = executionPath.substr(0,pos);
	ROS_INFO ("$%s$", Working_Folder.c_str()) ;

	
	//Initialisation des produits à l'aide du fichier de configuration

	//Définition du chemin du fichier de config et log
	configFile = Working_Folder + "/ProductConfiguration.config";
	logFile = Working_Folder + "/Statistic.txt";

	std::ifstream streamConfigFile(configFile.c_str(), std::ios::in); 	// Ouverture en lecture seule du fichier de configuration
	
	// Pour comprendre la suite de la lecture du fichier, il peut etre utile de se référer à http://www.cplusplus.com/reference/iolibrary/
	
	if (streamConfigFile)	//Si l'ouverture à reussi
	{
	std::string pNameFF,destinationPart,launchDatePart,jobTimePart,maxShuttlePart,contents; // string servant à l'extraction d'information

	//saut des lignes d'entêtes, repèrage du start (on passe toutes les lignes tant que le mot Start n'y figure pas)
	
	while(1){
	std::getline(streamConfigFile,contents);
	std::size_t found = contents.find("Start"); 
  	if (found!=std::string::npos)
		{
		break;
		}
	}
	
	//Configuration nombre max de shuttle
	
	std::getline(streamConfigFile,contents);
	//ROS_INFO("%s",contents.c_str())	;
	std::size_t pos0 = contents.find(":");   // repérage caractère ':' 
	maxShuttlePart = contents.substr(pos0+1); // on récupère le string qui se trouve après ':'
	//ROS_INFO("maxShuttlePart =%s",maxShuttlePart.c_str());
	maxShuttleNumber = atoi( maxShuttlePart.c_str()); // atoi = conversion vers integer !
	ROS_INFO("maxShuttleNumber = %d",maxShuttleNumber);

	//Configuration temps entre lancement
	
	std::getline(streamConfigFile,contents);
	//ROS_INFO("%s",contents.c_str())	;
	std::size_t pos1 = contents.find(":"); // même idée que précedemment 
	launchDatePart = contents.substr(pos1+1);
	
	char * cstr1 = new char [launchDatePart.length()+1]; // 
  	std::strcpy (cstr1, launchDatePart.c_str());	// création objet cstring

  		// cstr now contains a c-string copy of str
		int n1 = 0; //compteur sur les dates de lancement 
 	 	char * p1 = std::strtok (cstr1," "); // cf strtok sur cplusplus.com, permet un découpage du cstring fonction de l'espace
  		while (p1!=0)
  			{
    			//ROS_INFO ("p1 = %s",p1) ;
			scheduledLaunchDate[n1++] = atoi(p1);		
			ROS_INFO ("launch time entre %d et %d = %d",n1,n1+1,scheduledLaunchDate[n1-1]);
  			p1 = std::strtok(NULL," ");
  			}
  		delete[] cstr1; // comme la création est dynamique, on supprime l'objet pour libèrer la mémoire
	
	//Configuration Produits

	int incrementation = 0;
	while (std::getline(streamConfigFile, contents))
		{
		if (contents.find(':') != std::string::npos )   // Per ne prendre en considération que les lignes renseignés, ( dans les faits qui contiennent au moins un ':')
			{
			
			//ROS_INFO("%s",contents.c_str())	;
			std::size_t pos2 = contents.find(":"); // même idée que précedemment 
			std::size_t pos3 = contents.find_last_of(":"); // même idée que précedemment 
		
			pNameFF = contents.substr(0,pos2);	// Recupération nom produit
			ROS_INFO("Product %s",pNameFF.c_str());
			destinationPart = contents.substr(pos2+1,pos3-pos2-1);  //recupération du string correspondant aux destinations sur la ligne produit
			//ROS_INFO("destination part =%s",destinationPart.c_str());
			jobTimePart = contents.substr(pos3+1); // récupération du string correspondant aux temps des taches sur la ligne produit
			//ROS_INFO("jobTimePart =%s",jobTimePart.c_str());
			int destination[10]; // initialisation des tableaux locaux destination et Jobtime, il serviront a crée l'objet Produit
			int jobTime[10];
			int manRSize = 0; //manufacturing range size of the produit = number of operation

			char * cstr2 = new char [destinationPart.length()+1]; 
	  		std::strcpy (cstr2, destinationPart.c_str());	// création objet cstring
			char * cstr3 = new char [jobTimePart.length()+1]; 
	  		std::strcpy (cstr3, jobTimePart.c_str());
			//ROS_INFO(" cstr2 =%s ", cstr2);
			//ROS_INFO(" cstr3 =%s ", cstr3); 	

	  		// cstr now contains a c-string copy of str
			int n2 = 0; //compteur sur les destinations
			int n3 = 0; //compteur sur les temps de fabrications
	 	 	
			// même principe que plus haut
			char * p2 = std::strtok (cstr2," ");
	  		while (p2!=NULL)
	  			{
	    			//ROS_INFO ("p2 = %s",p2) ;
				destination[n2++] = atoi(p2);
				manRSize++ ;
				ROS_INFO ("destination %d = %d",n2-1,destination[n2-1]);
	  			p2 = std::strtok(NULL," ");
				//ROS_INFO ("p2 = %s",p2) ;
	  			}

			char * p3 = std::strtok (cstr3," ");
			while (p3!=NULL)
	  			{
	    			//ROS_INFO ("p3 = %s",p3) ;
				jobTime[n3++] = atoi(p3);
				ROS_INFO ("jobTime %d = %d",n3-1,jobTime[n3-1]);
	  			p3 = std::strtok(NULL," ");
				//ROS_INFO ("p3 = %s",p3);
	  			}

	  		delete[] cstr2;
			delete[] cstr3; 


			char charName;
			charName = char(pNameFF.c_str()[0]-16);
			//ROS_INFO("CharNAME = %d",charName);
			int pNumber = atoi(&charName) * 10 ; 
			//ROS_INFO("pNumber = %d",pNumber);
			numberOfProduct++; // on compte le nombre de produit
			
			;
			initProduct(pNameFF,destination[0], pNumber, manRSize,numberOfProduct);  // initialisation de l'objet produit
			nom_produits[incrementation]=pNameFF.c_str();
			incrementation++;
			}
		}
	// Fin config produit 
	
	ROS_INFO("Number of Product = %d", numberOfProduct);
	iteratorPMap = ProductsMap.begin(); // initilise l'iterateur sur la collection de produit
	nextCount = numberOfProduct-1; // Permet de bien placer les delays dans launch next schedule, on va effectuer le délays entre le dernier et le premier produit avant la lancement du premier produit
	client_simRosGetInfo.call(srv_GetInfoVREP); //Recupération des infos sur la simulation Vrep ( temps de simulation notamment)
	lastLaunchDate = srv_GetInfoVREP.response.simulationTime; //Initialise le temps de simulation
	
	streamConfigFile.close(); //fermeture du fichier ProductConfiguration.txt ouvert en lecture//

	
	//Creation du fichier de statistique :
	
	std::ofstream StatsFile(logFile.c_str(), std::ios::out | std::ios::app); // ouverture en append du fichier Statistic.txt, il est crée si inexistant
	if(StatsFile)  // si l'ouverture a réussi...
	        {
		//Récupération date de lancement//////////////////////
		time_t rawtime;
		struct tm * timeinfo;
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		//////////////////////////////////////////////////////
		ROS_INFO("Statistic.txt file ok \n");
		char logLine[1000];
		sprintf(logLine, "\n Nouveau lancement du programme / date : %s\n", asctime(timeinfo));//Construction entête
		ROS_INFO("Nouveau lancement du programme / date : %s\n", asctime(timeinfo));
		StatsFile << logLine; // Ecriture dans le fichier
	       	StatsFile.close();  // on referme le fichier Statistic.txt

        	}
       	else ROS_ERROR("Impossible de creer ou ouvrir le fichier Statistic.txt !");
	return true;

	}
	else ROS_ERROR("Impossible d'ouvrir le fichier ProductConfiguration.txt !");
	return false;
	}

// Destructor
Scheduler::~Scheduler()
{
}


// Scheduling Function
void Scheduler::launchNextSchedule(){

	if (init_var){
		std_msgs::Int32 NbMsg;
		NbMsg.data = numberOfProduct;
		pubNombreDeProduits.publish(NbMsg);
		std_msgs::String NomMsg;
		for (int j=0; j<100; j++){
			if (nom_produits[j] != "NULL"){
				NomMsg.data = nom_produits[j];
				pubNomProduits.publish(NomMsg);
			}
		}
		init_var = false;
	}

	if (maxShuttleNumber >0)
	{

	int nextDelay = scheduledLaunchDate[nextCount]; // définition next delays 

	// Récupération temps VREP ////////////// SERVICE simRosGetInfo de VREP ////////////

		client_simRosGetInfo.call(srv_GetInfoVREP);
		float timeDelta = srv_GetInfoVREP.response.simulationTime - lastLaunchDate;
		
	////////////////////////////////////////////////////////////////////////////////////

	if (timeDelta > nextDelay)
		{

		ROS_INFO("Execution de launchNextSchedule (launch date reach)");
		lastLaunchDate = srv_GetInfoVREP.response.simulationTime;	// récupération temps de simulation
		
		if (iteratorPMap == ProductsMap.end()) // permet de replacer l'iterateur en début de map si celui-ci se trouve en end ( après le dernier élément)
			{

			iteratorPMap = ProductsMap.begin();
			//ROS_WARN("Reset iterateur");

			}

		// Récupération des information sur le produit
		Product* productPointer;
		productPointer = iteratorPMap->second;	
		
		//Creation du message de lancement de produit destiné à la commande_locale
		scheduling::Msg_LoadShuttle mymsg;
		mymsg.shuttleType = 'F';
		mymsg.firstDestination = productPointer->firstDestination;
		mymsg.product = productPointer->productNumber;

		ROS_INFO("ORDO Creation navette avec produit %s numero = %d ",productPointer->name.c_str(), mymsg.product);
		pubCreateShuttle.publish(mymsg);

		//ECRITURE LOG FILE///////////////////////////////////////////////////////////////////////////

		std::ofstream StatsFile(logFile.c_str(), std::ios::out | std::ios::app);
		if(StatsFile)  // si l'ouverture a réussi...
			{

			//ROS_INFO("Statistic.txt file ok");
			char logLine[1000];
			// Construction Ligne avec notamment la date de lancement 
			sprintf(logLine, "Produit %s lance a temps Vrep = %f s\n",productPointer->name.c_str(), srv_GetInfoVREP.response.simulationTime);
			ROS_INFO("Produit %s lance a temps Vrep = %f s",productPointer->name.c_str(), srv_GetInfoVREP.response.simulationTime);
			StatsFile << logLine; // Ecriture dans le fichier 
		       	StatsFile.close();  // on referme le fichier Statistic.txt

			}

	       	else ROS_ERROR("Impossible de creer ou ouvrir le fichier Statistic.txt !");

		/////////////////////////////////////////////////////////////////////////////////////////////
		
		maxShuttleNumber--; 	// diminution du nombre de produit instantiable
		iteratorPMap++;		// avance dans la map produit
		nextCount++; 		// permet d'être en phase vis à vis du tableau des temps entre les lancements des produits
		nextCount = nextCount%numberOfProduct; //permet de revenir à la premier case quand on a fini le tableau 
		nextDelay = scheduledLaunchDate[nextCount]; // juste pour l'affichage...
		ROS_INFO("Je vais attendre = %d s VREP avant le lancement du prochain produit (si le nombre de navette max est atteint, je vais attendre qu'une sorte)",nextDelay);

		}
	}
}

// Création de produit
void Scheduler::initProduct(std::string pName, int pFirstDestination, int initProductNumber, int pManRSize, int order)
{
	ROS_INFO("Creation Produit %s, first destination = %d, numero produit = %d , taille gamme = %d", pName.c_str(), pFirstDestination,initProductNumber, pManRSize);

		// Création dynamique de l'object product
	Product* newProduct = new Product(pName,pFirstDestination,initProductNumber, pManRSize);

		// Insertion dans le map de la classe de la paire <key=handle,T=Product*>

	std::pair<std::map<int,Product*>::iterator,bool> ret;			// ret permet d'avoir un retour de la fonction insert, il est faux si la key existe dèjà dans la map
	ret = ProductsMap.insert(std::pair<int,Product*>(order,newProduct));
	//ROS_INFO("Product pointer : %p ", newProduct);

	if (ret.second==false)	// Si un produit avec le même nom existe dèjà, celui-ci n'est pas ajouté à la collection
	{
    		ROS_WARN("Ordonnanceur : Un produit de ce nom existe deja ! (%s) ", newProduct->name.c_str()); 
  	} 
} 

// Subscribers Callback (Product end of manifacture)

	void Scheduler::productOutCallBack(const std_msgs::Int32::ConstPtr& msg) // on recoit le handle de la navette qui sort de la cellule
	{
		srv_GetShuttleStatus.request.handle = msg->data;	// 
		client_GetShuttleStatus.call(srv_GetShuttleStatus);	// recupération des infos sur la navette ( service du noeud shuttles)
		client_simRosGetInfo.call(srv_GetInfoVREP);		// récupération info sur la simulation Vrep

		std::string finalProductName;	// nom produit fini
		Product* productPointer;	// pointer pour recherche dans la collection
		
		//ROS_INFO ( "srv_GetShuttleStatus.response.product = %d " ,srv_GetShuttleStatus.response.product);	

	for (iteratorPMapOut=ProductsMap.begin(); iteratorPMapOut!=ProductsMap.end(); ++iteratorPMapOut)	// On parcours l'ensemble de la collection
	{
		productPointer = iteratorPMapOut->second;
		if ( productPointer->productNumber == (srv_GetShuttleStatus.response.product - productPointer->manRangeSize)) // Trouve le nom du produit fini
		{
			//ROS_INFO ( "productPointer->manRangeSize = %d ", productPointer->manRangeSize); 
			//ROS_INFO ( "j'ai trouvé le nom du produit !!");
			finalProductName = productPointer->name;
		}
	}
	
	//ECRITURE LOG FILE///////////////////////////////////////////////////////////////////////////
	std::ofstream StatsFile(logFile.c_str(), std::ios::out | std::ios::app);
	if(StatsFile)  // si l'ouverture a réussi...
		{
		ROS_INFO("Statistic.txt file ok");
		char logLine[1000];
		// Construction Ligne avec notamment la date de lancement 

		sprintf(logLine, "Produit %s termine a temps Vrep = %f s\n",finalProductName.c_str(), srv_GetInfoVREP.response.simulationTime);
		ROS_INFO("Produit %s termine a temps Vrep = %f s\n",finalProductName.c_str(), srv_GetInfoVREP.response.simulationTime);

		StatsFile << logLine; // Ecriture dans le fichier 
		StatsFile.close();  // on referme le fichier Statistic.txt
		}
	else ROS_ERROR("Impossible de creer ou ouvrir le fichier Statistic.txt !");
	/////////////////////////////////////////////////////////////////////////////////////////////

	// Suppression de la navette dans le noeud shuttles à l'aide d'un message :
	std_msgs::Int32 msgdel;
	msgdel.data = msg->data;
	pubDelShuttle.publish(msgdel);
	maxShuttleNumber++; // augmentation du nombre de produit instantiable

}

void Scheduler::ManualLaunchCallBack(const std_msgs::Bool::ConstPtr& msg) //permet de garder a jour le nombre de navette présente dans le circuit
{
if (msg->data) maxShuttleNumber--;
}



	
