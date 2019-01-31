#include "A12.h"

using namespace std;

A12::A12(ros::NodeHandle nh)
{
	cout<<"Initialisation"<<endl;


	client_get_vrep_time = nh.serviceClient<vrep_common::simRosGetInfo>("/vrep/simRosGetInfo");

	VREPsubSensor = nh.subscribe("vrep/StopSensor", 1000, &A12::SensorCallback, this);
	VREPsubSwitchSensor = nh.subscribe("vrep/SwitchSensor", 1000, &A12::SwitchSensorCallback, this);

	ShStop = nh.advertise<std_msgs::Int32>("/commande/ArretNavette", 1000);
	ShStart = nh.advertise<std_msgs::Int32>("/commande/DemarrerNavette", 1000);
	AigDev = nh.advertise<std_msgs::Int32>("/commande/DeverouilleAiguillage", 1000);
	AigVer = nh.advertise<std_msgs::Int32>("/commande/VerouilleAiguillage", 1000);
	AigGauche = nh.advertise<std_msgs::Int32>("/commande/AiguillageGauche", 1000);
	AigDroit = nh.advertise<std_msgs::Int32>("/commande/AiguillageDroit", 1000);

	cout<<"time : "<<this->get_time()<<endl;

	SendShuttle = nh.advertise<aiguillages::ExchangeSh>("/IOShuttle/A12_A1", 1000);

	//ReceiveShuttle_d = nh.subscribe("/IOShuttle/P2_A12", 1000, &A12::NewShuttleCallBack_d, this);//avec les postes
	ReceiveShuttle_d = nh.subscribe("/IOShuttle/A11_P1", 1000, &A12::NewShuttleCallBack_d, this);//sans les postes
	ReceiveShuttle_g = nh.subscribe("/IOShuttle/A11_A12", 1000, &A12::NewShuttleCallBack_g, this);


	
	Dt=0.7;

	PS_past=0;

	Nav_PS= 0;
	PSG=0;
	PSD=0;

	num_aiguillage = 12;
	num_stop_droit = 24;
	num_stop_gauche = 23;
	num_capt_sortie = 1;


	num_STOPg.data=num_stop_gauche;
	num_STOPd.data=num_stop_droit;

	num_AIG.data=num_aiguillage;

	
	usleep(1000000);
	this->STOP_DROIT();
	this->STOP_GAUCHE();

	
}
 



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Callback////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void A12::SensorCallback(const std_msgs::Int32::ConstPtr& msg)
{


	bool PSG_test,PSD_test;
	
	PSG_test = (msg->data & (int32_t)pow(2,num_stop_gauche -1)) > 0;
	PSD_test = (msg->data & (int32_t)pow(2,num_stop_droit -1)) > 0;
	PS = (msg->data & (int32_t)pow(2,num_capt_sortie -1)) > 0;
	
	if(PSG_test) PSG=1;
	if(PSD_test) PSD=1;


	PS = (msg->data & (int32_t)pow(2,num_capt_sortie -1)) > 0;

		
	

	if(PS ==0)
	{
		if(PS_past)
		{
			PS_past=PS;
			Nav_PS =1;
		}
	}
	else
	{
		PS_past=PS;
	}
	
}

//SwitchSensor
void A12::SwitchSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	Aig_D = (msg->data & (int32_t)pow(2,2*num_aiguillage-2)) > 0;
	Aig_G = (msg->data & (int32_t)pow(2,2*num_aiguillage-1)) > 0;
}


void A12::NewShuttleCallBack_d(const aiguillages::ExchangeSh::ConstPtr& msg)
{
	std_msgs::Header h = msg->header;
	cout<<"Handler de la navette"<<msg->handle<<endl;
	cout<<"heure reception"<<h.seq<<endl;

	Sh* newShuttle = new Sh(msg->handle,h.seq);

	ShuttlesMap.insert(std::pair<int,Sh*>(1,newShuttle));
	

	//// Affichage
	std::map<int,Sh*>::iterator it;
	Sh* shuttlePointer;	
	
	 std::pair <std::multimap<int,Sh*>::iterator, std::multimap<int,Sh*>::iterator> ret2;
   	 ret2 = ShuttlesMap.equal_range(1);
   	 cout<<"handle des navettes dans la map venant de droite:"<<endl;
   	 for (std::multimap<int,Sh*>::iterator it=ret2.first; it!=ret2.second; ++it)
	{
		shuttlePointer = it->second;	
      		std::cout << " " << shuttlePointer->get_handle();
   		 std::cout << endl;
	}

}

void A12::NewShuttleCallBack_g(const aiguillages::ExchangeSh::ConstPtr& msg)
{
	std_msgs::Header h = msg->header;
	cout<<"Handler de la navette"<<msg->handle<<endl;
	cout<<"heure reception"<<h.seq<<endl;
	

	Sh* newShuttle = new Sh(msg->handle,h.seq);

	ShuttlesMap.insert(std::pair<int,Sh*>(-1,newShuttle));
	
	//// Affichage
	std::map<int,Sh*>::iterator it;
	Sh* shuttlePointer;	
	
	 std::pair <std::multimap<int,Sh*>::iterator, std::multimap<int,Sh*>::iterator> ret2;
   	 ret2 = ShuttlesMap.equal_range(-1);
   	 cout<<"handle des navettes dans la map venant de gauche:"<<endl;
   	 for (std::multimap<int,Sh*>::iterator it=ret2.first; it!=ret2.second; ++it)
	{
		shuttlePointer = it->second;	
      		std::cout << " " << shuttlePointer->get_handle();
   		 std::cout << endl;
	}

}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Commande Aiguillage/////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void A12::STOP_DROIT(){
	ShStop.publish(num_STOPd);
}
void A12::STOP_GAUCHE(){
	ShStop.publish(num_STOPg);
}


void A12::START_DROIT(){
	ShStart.publish(num_STOPd);
}
void A12::START_GAUCHE(){
	ShStart.publish(num_STOPg);
}


void A12::Gauche()
{
	
	
	if(!Aig_G)
	{
		//Deverouillage de l'aiguillage	
		AigDev.publish(num_AIG);

		usleep(1000000);

		//Envoie ordre mouvement à gauche
		AigGauche.publish(num_AIG);


		//Attente...
		while(!Aig_G)
		{
		
			ros::spinOnce();
			if(Aig_D) AigGauche.publish(num_AIG);
		}

		//Verouillage de l'aiguillage	
		AigVer.publish(num_AIG);
	}
	usleep(1000000);
}

void A12::Droit()
{
	
	if(!Aig_D)
	{
		//Deverouillage de l'aiguillage	
		AigDev.publish(num_AIG);

		usleep(1000000);

		//Envoie ordre mouvement à droite
		AigDroit.publish(num_AIG);


		//Attente...
		while(!Aig_D)
		{
		
			ros::spinOnce();
			if(Aig_G) AigDroit.publish(num_AIG);
			usleep(100000);
		}	

		//Verouillage de l'aiguillage
		AigVer.publish(num_AIG);
	}

	usleep(1000000);
	
}
	
	


void A12::Aiguille_Navette()
{
		
		if(PSG &&  this->get_Sh_Handle(-1)!=-1)
		{
			

			this->STOP_DROIT();

			this->STOP_GAUCHE();
			
			this->Gauche();
			
			this->START_GAUCHE();

			// Attente en fonction du temps de Vrep
			wait_vrep(Dt);
			this->STOP_GAUCHE();
			PSG=0;
			Send_Sh(-1);

			// Attente que la navette passe jusqu'à ce que PS6 s'active
			while(!Nav_PS)
			{
			
				ros::spinOnce();

			}
			wait_vrep(0.5);
			// Remise à zéro PS1
			Nav_PS=0;
			
		}else if(PSD &&  this->get_Sh_Handle(1)!=-1)
		{
			this->STOP_DROIT();

			this->STOP_GAUCHE();

			this->Droit();

			this->START_DROIT();

			// Attente en fonction du temps de Vrep		
			wait_vrep(Dt);
			this->STOP_DROIT();

			PSD=0;
			Send_Sh(1);


			// Attente que la navette passe jusqu'à ce que PS6 s'active
			while(!Nav_PS)
			{
				ros::spinOnce();
			}
			
			// Remise à zéro PS1
			wait_vrep(0.5);
			Nav_PS=0;
		}
}




int A12::get_Sh_Handle(int origine)
{
	std::map<int,Sh*>::iterator it;

	Sh* shuttlePointer;	
	
	std::pair <std::multimap<int,Sh*>::iterator, std::multimap<int,Sh*>::iterator> ret2;
   	ret2 = ShuttlesMap.equal_range(origine);
   	cout<<"handle des navettes dans la map venant de :"<<origine<<" --> "<<endl;
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


void A12::Send_Sh(int origine)
{
	std::map<int,Sh*>::iterator it;
	int handle_min;
	
	handle_min=this->get_Sh_Handle(origine);

	HandleShuttle.handle=handle_min;
	SendShuttle.publish(HandleShuttle);

	Sh* shuttlePointer;	
	
	std::pair <std::multimap<int,Sh*>::iterator, std::multimap<int,Sh*>::iterator> ret2;
   	ret2 = ShuttlesMap.equal_range(origine);
   	 for (std::multimap<int,Sh*>::iterator it=ret2.first; it!=ret2.second; ++it)
	{
		shuttlePointer = it->second;
		if(shuttlePointer->get_handle()==handle_min)
		{
			ShuttlesMap.erase(it);
		}
   		
	}


}

float A12::get_time()
{
	client_get_vrep_time.call(srv_get_time);
	return (float) srv_get_time.response.simulationTime;

}

void A12::wait_vrep(float dt)
{
	float t=this->get_time();
	while(this->get_time()-t<dt)
	{
		ros::spinOnce();
	}

}

