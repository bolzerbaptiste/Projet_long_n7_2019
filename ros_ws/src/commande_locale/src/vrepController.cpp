/*
 * ********************************* *
 * Copyright 2016, STEC Projet Long. *
 * All rights reserved.  	     *
 * ********************************* *
 * Mise à jour par le Projet Long    *
 * ENSEEIHT 2017		     *
 * ********************************* *
*/

#include "vrepController.h"

// Initialisation du nombre de plateformes F
vrepController::vrepController(){
	nShuttleF = 0;
}

// PAUSE
void vrepController::pause()
{
	client_simRosPauseSimulation.call(srv_PauseSimulation);
}

// PLAY
void vrepController::play()
{
	client_simRosStartSimulation.call(srv_StartSimulation);				
}

// SHUTTLE (pour charger une plateforme dans la simulation: plateforme aléatoire puis couleur de plateforme aléatoire)
int vrepController::LoadShuttle(char shuttleNumber, int type, int firstDestination)
{

// Pour charger une plateforme F avec une couleur aléatoire

		std::string shuttleName = "models/montrac/shuttle"+std::string(&shuttleNumber,1)+".ttm";
		//ROS_INFO("------------ ShuttleName: %s" , shuttleName.c_str());
		srv_LoadModel.request.fileName = shuttleName;

// Choix du type de produit (changement de la couleur)
		int shuttleColor ;		
		if (type == -1){
				shuttleColor = (rand() % 7)*10;
		}else {
				shuttleColor = type;
				ROS_INFO("%d",type);
		}
				srv_ModelColor.request.signalValue = shuttleColor;

		//ROS_INFO("------------ ShuttleColor: %i" , shuttleColor);


		std::string shuttleNameComplete, platformNameComplete;
		if (nShuttleF == 0) {
			shuttleNameComplete = "Shuttle"+std::string(&shuttleNumber,1);
			platformNameComplete = "PlatformUp"+std::string(&shuttleNumber,1);
		}
		else{
			char aux = nShuttleF - 1 + '0';	 // transformation int -> char
			//ROS_INFO("-------- Aux : %c" ,aux);
			shuttleNameComplete = "Shuttle"+std::string(&shuttleNumber,1)+"#"+ std::string(&aux,1);
			platformNameComplete = "PlatformUp"+std::string(&shuttleNumber,1)+"#"+ std::string(&aux,1);
		}
		//ROS_INFO("------ ShuttleNameComplete: %s" , shuttleNameComplete.c_str());
		nShuttleF ++;
		

		client_simRosLoadModel.call(srv_LoadModel);	

//Recuperation nom signal couleur : <handle de la navette>_color
		
		int handle_navette = srv_LoadModel.response.baseHandle;	
		char intStr[1000];
		sprintf (intStr, "%d", handle_navette);
		
		std::cout<<"test : "<<*intStr<<std::endl;
		int dim;
		
		dim=floor(log10(handle_navette))+1;
		std::cout<<"dim : "<<dim<<std::endl;
		
		std::string shuttleColorSignal= std::string(intStr,dim) + "_color"; ;
		
		
		
		std::cout<<"test : "<<shuttleColorSignal<<std::endl;
		//ROS_INFO("-------- ShuttleColorSignal: %s" , shuttleColorSignal.c_str());

		
		do
		{
			srv_ModelColor.request.signalName = shuttleColorSignal;
			
			client_simRosModelColor.call(srv_ModelColor);
			
			srv_ModelColor_Verif.request.signalName = shuttleColorSignal;
			client_simRosModelColorVerif.call(srv_ModelColor_Verif);
			std::cout<<"retour couleur : "<<srv_ModelColor_Verif.response.signalValue<<std::endl;
		}while(srv_ModelColor_Verif.response.signalValue!=shuttleColor);

		
		int32_t handle_plateforme = vrepController::getObjectHandle(platformNameComplete);

		// std::cout << "Handle de la plateforme: " <<handle_plateforme <<std::endl;
		
		addNewShuttle(handle_navette, handle_plateforme,shuttleColor, firstDestination );

		Sh_Handle.handle = handle_navette;
		pub_Shuttle_Handle.publish(Sh_Handle);
		

		return handle_navette;

					
}

void vrepController::addNewShuttle(int handle_navette, int handle_plateforme, int type, int destination) {

	
	char aux[1000]; 
	sprintf(aux,"Shuttle%d",handle_navette);
	std::string name(aux);

	Cr_Shuttle.name = name;
	Cr_Shuttle.product = type;
	Cr_Shuttle.destination = destination;
	Cr_Shuttle.handle = handle_navette;
	Cr_Shuttle.handlePlatform = handle_plateforme;
	Cr_Shuttle.zone = 0;

	ROS_INFO( "Ajout navette d'handle : %d",handle_navette);
	createShuttle.publish(Cr_Shuttle);
}

// Chargement des modèles dans la simulation lors de son lancement
void vrepController::loadModelInit(char shuttleNumber)
{
	if(shuttleNumber>54 || shuttleNumber<48) printf(" ATTENTION, LE NUMERO DU SHUTTLE DOIT ETRE COMPRIS ENTRE 0 ET 6 \n");
	else {		
		if(shuttleNumber == 48) shuttleNumber = char(74); // SI 0 -> ShuttleZ
		shuttleNumber = char(shuttleNumber+16);
		std::string shuttleName = "models/montrac/shuttle"+std::string(&shuttleNumber)+".ttm";
		srv_LoadModelInit.request.fileName = shuttleName;	
		
		client_simRosLoadModelInit.call(srv_LoadModelInit); 
	}
}



// Suppression des modèles dans la simulation
void vrepController::removeModel(int handle)
	
//objectName (string): name of the object. If possibe, don't rely on the automatic name adjustment mechanism, and always specify the full object name, including the #: if the object is "myJoint", specify "myJoint#", if the object is "myJoint#0", specify "myJoint#0", etc.
{
        srv_RemoveModel.request.handle = handle;
        client_simRosRemoveModel.call(srv_RemoveModel);
}

//Obtention d'un handle d'objet dans la simulation
int32_t vrepController::getObjectHandle(std::string objectName)
{
	srv_GetObjectHandle.request.objectName = objectName;
	client_simRosGetObjectHandle.call(srv_GetObjectHandle);
	return srv_GetObjectHandle.response.handle;
}


// On ferme le processus vrep
void vrepController::close()
{
	system("pkill vrep");
}

//Callback de suppression
void vrepController::deleteShuttleCallBack(const aiguillages::ExchangeSh::ConstPtr& msg)
{
	this->removeModel(msg->handle);
}

// Callback couleur
void vrepController::ColorCallBack(const commande_locale::Msg_Color::ConstPtr& msg)
{
	int Handle;
	Handle=msg->Handle;
	int Color;
	Color=msg->Color;

	
	char intStr[1000];
	sprintf (intStr, "%d", Handle);
		
		
	int dim;
		
	dim=floor(log10(Handle))+1;
	std::string shuttleColorSignal= std::string(intStr,dim) + "_color"; ;

	std::cout<<"test : "<<shuttleColorSignal<<std::endl;
	ROS_INFO("-------- ShuttleColorSignal: %s" , shuttleColorSignal.c_str());

	srv_ModelColor.request.signalValue = Color;
	do
	{
		srv_ModelColor.request.signalName = shuttleColorSignal;
			
		client_simRosModelColor.call(srv_ModelColor);
			
		srv_ModelColor_Verif.request.signalName = shuttleColorSignal;
		client_simRosModelColorVerif.call(srv_ModelColor_Verif);
		std::cout<<"retour couleur : "<<srv_ModelColor_Verif.response.signalValue<<std::endl;
	}while(srv_ModelColor_Verif.response.signalValue!=Color);
	
}

void vrepController::init(ros::NodeHandle n,std::string executionPath, std::string simulationFileName)
{

// Launch of V-Rep
	int count = 0 ;
	int pos = 0 ;
	while (count < 4)
	{
		if(executionPath[pos] == '/') count++;
		pos++;
	}
	std::string VRepPath = executionPath.substr(0,pos)+ "V-Rep";
	ROS_INFO ("$%s$", VRepPath.c_str()) ;
	
	char final_command[1000];
	sprintf(final_command, "cd %s &&(./vrep.sh -h ../sim/%s.ttt &)", VRepPath.c_str(), simulationFileName.c_str());
	system(final_command); // On execute VREP sans afficher la fenetre

//Launch of the different services
	sleep(2);
	client_simRosLoadModelInit = n.serviceClient<vrep_common::simRosLoadModel>("/vrep/simRosLoadModel");
	client_simRosRemoveModel = n.serviceClient<vrep_common::simRosRemoveModel>("/vrep/simRosRemoveModel");
	client_simRosGetObjectHandle = n.serviceClient<vrep_common::simRosGetObjectHandle>("/vrep/simRosGetObjectHandle");
	client_simRosStartSimulation = n.serviceClient<vrep_common::simRosStartSimulation>("/vrep/simRosStartSimulation");	
	client_simRosPauseSimulation = n.serviceClient<vrep_common::simRosPauseSimulation>("/vrep/simRosPauseSimulation");
	client_simRosModelColor = n.serviceClient<vrep_common::simRosSetIntegerSignal>("/vrep/simRosSetIntegerSignal");
	client_simRosModelColorVerif = n.serviceClient<vrep_common::simRosGetIntegerSignal>("/vrep/simRosGetIntegerSignal");
	client_simRosLoadModel = n.serviceClient<vrep_common::simRosLoadModel>("/vrep/simRosLoadModel");

	pub_Shuttle_Handle = n.advertise<aiguillages::ExchangeSh>("/commande_locale/New_Shuttle_Handle", 10);
	
	DeleteShuttle = n.subscribe("/commande_locale/Delete_Shuttle", 10, &vrepController::deleteShuttleCallBack, this);

	createShuttle = n.advertise<shuttles::msgShuttleCreate>("/commande_navette/AddShuttle",10);

	ChangeColor = n.subscribe("/commande_locale/Change_Color", 10, &vrepController::ColorCallBack, this);
}

void vrepController::setSimulationFile(std::string fileName){
	this->SimulationFileName = fileName;
}
