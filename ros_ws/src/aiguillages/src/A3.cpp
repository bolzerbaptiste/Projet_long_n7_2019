#include "A3.h"  

using namespace std;

A3::A3(ros::NodeHandle nh)
{
	cout<<"Initialisation du callback"<<endl;


	VREPsubStopSensor = nh.subscribe("vrep/StopSensor", 10, &A3::StopSensorCallback, this);
	VREPsubSwitchSensor = nh.subscribe("vrep/SwitchSensor", 10, &A3::SwitchSensorCallback, this);
	VREPsubRailSensor = nh.subscribe("vrep/RailSensor", 10, &A3::RailSensorCallback, this);

	Aigok = nh.subscribe("/DemiTour/A10_A3", 10, &A3::AiguillageCallback, this);

	ShStop = nh.advertise<std_msgs::Int32>("/commande/ArretNavette", 10);
	ShStart = nh.advertise<std_msgs::Int32>("/commande/DemarrerNavette", 10);
	AigDev = nh.advertise<std_msgs::Int32>("/commande/DeverouilleAiguillage", 10);
	AigVer = nh.advertise<std_msgs::Int32>("/commande/VerouilleAiguillage", 10);
	AigGauche = nh.advertise<std_msgs::Int32>("/commande/AiguillageGauche", 10);
	AigDroit = nh.advertise<std_msgs::Int32>("/commande/AiguillageDroit", 10);

	client_get_vrep_time = nh.serviceClient<vrep_common::simRosGetInfo>("/vrep/simRosGetInfo");
	client_SetShuttleState = nh.serviceClient<shuttles::srvGetShuttleStatus>("/commande_navette/srvGetShuttleStatus");

	DemiTour = nh.advertise<std_msgs::Int32>("/DemiTour/A3_A10", 10);

	DeleteShuttle = nh.advertise<aiguillages::ExchangeSh>("/commande_locale/Delete_Shuttle", 1000);
	DeleteShuttleScheduler = nh.advertise<std_msgs::Int32>("/A3/ShuttleOut", 1000);
	
	SendShuttle_g = nh.advertise<aiguillages::ExchangeSh>("/IOShuttle/A3_A10", 1000);
	//SendShuttle_d = nh.advertise<aiguillages::ExchangeSh>("/IOShuttle/A1_P3", 1000);//avec les postes
	ReceiveShuttle = nh.subscribe("/IOShuttle/A2_A3", 1000, &A3::NewShuttleCallBack, this);

	subDestroyShuttle = nh.subscribe("/commande_navette/Destroy_Shuttle", 10, &A3::DestroyShuttleCallBack, this);
	

	
	A10_ok = 0;
	
	Dt=0.7;


	CPb_past =0;

	Nav_PSh= 0;
	Nav_CPb=0;

	num_aiguillage = 3;
	num_capt_stop = 6;
	num_capt_sortie_haut = 20;
	num_capt_sortie_bas = 3;


	num_STOP.data=num_capt_stop;

	num_AIG.data=num_aiguillage;

	PS=0;

	
	usleep(1000000);
	this->STOP();

	

	
}
 



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Callback////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void A3::StopSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	bool PS_test;
	 PS_test=(msg->data & (int32_t)pow(2,num_capt_stop-1)) > 0;
	 
	if(PS_test) PS=1;

	
}

//RailSensor
void A3::RailSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	CPb = (msg->data & (int32_t)pow(2,num_capt_sortie_bas -1)) > 0;
	
	//Detection passage d'une navette en CP3
	if(CPb)
	{
		
		if(!CPb_past)
		{
			
			CPb_past=CPb;
			Nav_CPb=1;
		}
	}else
	{
		CPb_past=CPb;
	}

}

//SwitchSensor
void A3::SwitchSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{

	Aig_D = (msg->data & (int32_t)pow(2,2*num_aiguillage-2)) > 0;
	Aig_G = (msg->data & (int32_t)pow(2,2*num_aiguillage-1)) > 0;
}

//Disponibilité de l'aiguillage 10 pour que la navette fasse demi-tour
void A3::AiguillageCallback(const std_msgs::Int32::ConstPtr& msg)
{
	

	//cout<<"L'aiguillage 10 est orienté pour le demi-tour"<<endl;
	A10_ok = msg->data;
	if(A10_ok==-1)
	{
		Nav_PSh=1;
		A10_ok=0;
	}


}


void A3::NewShuttleCallBack(const aiguillages::ExchangeSh::ConstPtr& msg)
{
	std_msgs::Header h = msg->header;
	//cout<<"Handler de la navette"<<msg->handle<<endl;
	//cout<<"heure reception"<<h.seq<<endl;
	//tab_handle[tab_arr]=msg->data;

	Sh* newShuttle = new Sh(msg->handle,h.seq);

	ShuttlesMap.insert(std::pair<int,Sh*>(0,newShuttle));
	
	

	/////affichage
	std::map<int,Sh*>::iterator it;
	Sh* shuttlePointer;	
	
	 std::pair <std::multimap<int,Sh*>::iterator, std::multimap<int,Sh*>::iterator> ret2;
   	 ret2 = ShuttlesMap.equal_range(0);
   	 cout<<"handle des navettes dans la map :"<<endl;
   	 for (std::multimap<int,Sh*>::iterator it=ret2.first; it!=ret2.second; ++it)
	{
		shuttlePointer = it->second;	
      		std::cout << " " << shuttlePointer->get_handle();
   		 std::cout << endl;
	}
}

void A3::DestroyShuttleCallBack(const std_msgs::Int32::ConstPtr& msg)
{
	int del = msg->data;
	if (del) 
	{
		A3::Send_Sh_Bis(1, del);
		ROS_INFO("Navette a detruire !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Commande Aiguillage/////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void A3::STOP(){
	ShStop.publish(num_STOP);
}

void A3::START(){
	ShStart.publish(num_STOP);
}


void A3::Droit()
{

	//Deverouillage de l'aiguillage
	AigDev.publish(num_AIG);

	usleep(100000);

	//Envoie ordre mouvement à droite
	AigDroit.publish(num_AIG);

	usleep(300000);

	//Attente...
		while(!Aig_D)
		{
			if(Aig_G) 
			{
				AigDroit.publish(num_AIG);
				usleep(100000);
			}
			ros::spinOnce();
		}

	//Verouillage de l'aiguillage	
	AigVer.publish(num_AIG);
}

void A3::Gauche()
{
	//On prévient que la navette veut faire demi tour

	this->STOP();
	DemiTour.publish(num_AIG);
	
	//Deverouillage de l'aiguillage	
	AigDev.publish(num_AIG);

	usleep(100000);

	//Envoie ordre mouvement a gauche haut
	AigGauche.publish(num_AIG);

	usleep(300000);

	//Attente...
		while(!Aig_G || (A10_ok!=1))
		{
			if(Aig_D) AigGauche.publish(num_AIG);
			usleep(100000);
			ros::spinOnce();
		}

	//Verouillage des aiguillages	
	AigVer.publish(num_AIG);
	A10_ok=0;


}

void A3::ModeManuel(){
	int aux;
	cout << "\nMode Manuel"<< endl;
	cout << "1) Demi-tour \t 2) Droite "<< endl;
	cin >> aux;

		if(aux==1){
			this->Gauche();
	 	}
		if(aux==2){
			this->Droit();
		}
		
}

void A3::Aiguille_Navette()
{


		
	if(PS && this->get_Sh_Handle()!=-1)
	{

		srv_SetShuttleState.request.handle=this->get_Sh_Handle();
		client_SetShuttleState.call(srv_SetShuttleState);
		int destination = srv_SetShuttleState.response.destination;
		cout<<"destination : "<<destination<<endl;
		if(destination==5)
		{
			cout<<"droite"<<endl;
			this->Droit();
			
			this->START();
			wait_vrep(Dt);
			this->STOP();
			PS=0;
			
			while(!Nav_CPb)
			{
				
				ros::spinOnce();
				
			}
			Send_Sh(1);
			Nav_CPb=0;
		}else
		{
			cout<<"gauche"<<endl;
			this->Gauche();
			usleep(100000);
			
			this->START();
			wait_vrep(Dt);
			this->STOP();
			PS=0;
			Send_Sh(-1);
			while(!Nav_PSh)
			{
				
				ros::spinOnce();
				
			}
			Nav_PSh=0;
		}
	}
		
}


int A3::get_Sh_Handle()
{
	std::map<int,Sh*>::iterator it;
	Sh* shuttlePointer;	
	
	std::pair <std::multimap<int,Sh*>::iterator, std::multimap<int,Sh*>::iterator> ret2;
   	ret2 = ShuttlesMap.equal_range(0);
   	cout<<"handle des navettes dans la map :"<<" --> "<<endl;
	int min=-1;
	int Sh_min=-1;
   	 for (std::multimap<int,Sh*>::iterator it=ret2.first; it!=ret2.second; ++it)
	{
		shuttlePointer = it->second;	
      		std::cout << " " << shuttlePointer->get_handle();
		if(shuttlePointer->get_time()<min || min==-1)
		{
			min=shuttlePointer->get_time();
			Sh_min=shuttlePointer->get_handle();
			
		}
   		 std::cout << endl;
	}
	
	return Sh_min;
}


void A3::Send_Sh(int destination)
{
	std::map<int,Sh*>::iterator it;
	int handle_min;
	
	handle_min=this->get_Sh_Handle();

	HandleShuttle.handle=handle_min;
	if(destination==-1)
	{
		SendShuttle_g.publish(HandleShuttle);
	}else if(destination==1)
	{
		DeleteSh.data=HandleShuttle.handle;
		cout<<"delete shuttle"<<HandleShuttle<<endl;
		DeleteShuttle.publish(HandleShuttle);
		DeleteShuttleScheduler.publish(DeleteSh);
	}

	Sh* shuttlePointer;	
	
	std::pair <std::multimap<int,Sh*>::iterator, std::multimap<int,Sh*>::iterator> ret2;
   	ret2 = ShuttlesMap.equal_range(0);
   	 for (std::multimap<int,Sh*>::iterator it=ret2.first; it!=ret2.second; ++it)
	{
		shuttlePointer = it->second;
		if(shuttlePointer->get_handle()==handle_min)
		{
			ShuttlesMap.erase(it);
		}
   		
	}

}

void A3::Send_Sh_Bis(int destination, int handle)
{
	std::map<int,Sh*>::iterator it;
	int handle_min;
	
	handle_min=handle;

	HandleShuttle.handle=handle_min;
	if(destination==-1)
	{
		SendShuttle_g.publish(HandleShuttle);
	}else if(destination==1)
	{
		DeleteSh.data=HandleShuttle.handle;
		cout<<"delete shuttle"<<HandleShuttle<<endl;
		DeleteShuttle.publish(HandleShuttle);
		DeleteShuttleScheduler.publish(DeleteSh);
	}

	Sh* shuttlePointer;	
	
	std::pair <std::multimap<int,Sh*>::iterator, std::multimap<int,Sh*>::iterator> ret2;
   	ret2 = ShuttlesMap.equal_range(0);
   	 for (std::multimap<int,Sh*>::iterator it=ret2.first; it!=ret2.second; ++it)
	{
		shuttlePointer = it->second;
		if(shuttlePointer->get_handle()==handle_min)
		{
			ShuttlesMap.erase(it);
		}
   		
	}

}


float A3::get_time()
{
	client_get_vrep_time.call(srv_get_time);
	return (float) srv_get_time.response.simulationTime;


}

void A3::wait_vrep(float dt)
{
	float t=this->get_time();
	while(this->get_time()-t<dt)
	{
		ros::spinOnce();
	}

}

