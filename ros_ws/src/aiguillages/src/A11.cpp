#include "A11.h"  

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Constructeur////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
A11::A11(ros::NodeHandle nh)
{
	cout<<"Initialisation"<<endl;

	client_get_vrep_time = nh.serviceClient<vrep_common::simRosGetInfo>("/vrep/simRosGetInfo");
	client_SetShuttleState = nh.serviceClient<shuttles::srvGetShuttleStatus>("/commande_navette/srvGetShuttleStatus");

	VREPsubStopSensor = nh.subscribe("vrep/StopSensor", 1000, &A11::StopSensorCallback, this);
	VREPsubRailSensor = nh.subscribe("vrep/RailSensor", 1000, &A11::RailSensorCallback, this);
	VREPsubSwitchSensor = nh.subscribe("vrep/SwitchSensor", 1000, &A11::SwitchSensorCallback, this);

	
	Dt=0.7;

	SendShuttle_g = nh.advertise<aiguillages::ExchangeSh>("/IOShuttle/A11_A12", 1000);
	SendShuttle_d = nh.advertise<aiguillages::ExchangeSh>("/IOShuttle/A11_P1", 1000);
	ReceiveShuttle = nh.subscribe("/IOShuttle/A10_A11", 1000, &A11::NewShuttleCallBack, this);


	



	ShStop = nh.advertise<std_msgs::Int32>("/commande/ArretNavette", 1000);
	ShStart = nh.advertise<std_msgs::Int32>("/commande/DemarrerNavette", 1000);
	AigDev = nh.advertise<std_msgs::Int32>("/commande/DeverouilleAiguillage", 1000);
	AigVer = nh.advertise<std_msgs::Int32>("/commande/VerouilleAiguillage", 1000);
	AigGauche = nh.advertise<std_msgs::Int32>("/commande/AiguillageGauche", 1000);
	AigDroit = nh.advertise<std_msgs::Int32>("/commande/AiguillageDroit", 1000);

	
	cout<<"time : "<<this->get_time()<<endl;

	
	Nav_CPD=0;
	Nav_CPG=0;
	PS=0;


	//Numéro des capteurs et de l'aiguillage
	num_aiguillage=11;//aiguillage
	num_capt_stop=20;//capteur et stop en entrée de l'aiguillage
	num_capt_droit=9;//capteur en sorti de l'aiguillage droit
	num_capt_gauche=10;//capteur en sorti de l'aiguillage gauche

	Aig_D=1;//Aiguillage à droite au démarrage de la navette

	num_AIG.data=num_aiguillage;
	num_STOP.data=num_capt_stop;

	usleep(1000000);
	this->STOP();



}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Callback////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//StopSensor
void A11::StopSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	bool PS_test;

	 PS_test = (msg->data & (int32_t)pow(2,num_capt_stop-1)) > 0;
	if(PS_test) PS=1;

}

//RailSensor
void A11::RailSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	CPD = (msg->data & (int32_t)pow(2,num_capt_droit-1)) > 0;
	CPG = (msg->data & (int32_t)pow(2,num_capt_gauche-1)) > 0;
	
	//Detection passage d'une navette en CP9
	if(CPD)
	{
		if(!CPD_past)
		{
			CPD_past=CPD;
			Nav_CPD=1;
		}
	}else
	{
		CPD_past=CPD;
	}

	//Detection passage d'une navette en CP10
	if(CPG)
	{
		
		if(!CPG_past)
		{
			
			CPG_past=CPG;
			Nav_CPG=1;
		}
	}else
	{
		CPG_past=CPG;
	}

}


//SwitchSensor
void A11::SwitchSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	Aig_D = (msg->data & (int32_t)pow(2,2*num_aiguillage-2)) > 0;
	Aig_G = (msg->data & (int32_t)pow(2,2*num_aiguillage-1)) > 0;
}


void A11::NewShuttleCallBack(const aiguillages::ExchangeSh::ConstPtr& msg)
{
	std_msgs::Header h = msg->header;
	cout<<"Handler de la navette"<<msg->handle<<endl;
	cout<<"heure reception"<<h.seq<<endl;


	Sh* newShuttle = new Sh(msg->handle,h.seq);

	ShuttlesMap.insert(std::pair<int,Sh*>(0,newShuttle));
	
	//// Affichage
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

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Commande Aiguillage/////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void A11::STOP()
{
	ShStop.publish(num_STOP);
}

void A11::START()
{
	ShStart.publish(num_STOP);
}




void A11::Gauche()
{
	
	if(!Aig_G)
	{
		//Deverouillage de l'aiguillage	
		AigDev.publish(num_AIG);

		usleep(100000);

		//Envoie ordre mouvement à gauche
		AigGauche.publish(num_AIG);


		//Attente...
		while(!Aig_G)
		{
			ros::spinOnce();
			usleep(100000);
			if(Aig_D) AigGauche.publish(num_AIG);
		}


		//Verouillage de l'aiguillage
		AigVer.publish(num_AIG);
	}

	usleep(100000);	
	
}



void A11::Droit()
{
	
	if(!Aig_D)
	{
		
		//Deverouillage de l'aiguillage	
		AigDev.publish(num_AIG);

		usleep(100000);

		//Envoie ordre mouvement à droite
		AigDroit.publish(num_AIG);


		//Attente...
		while(!Aig_D)
		{
			ros::spinOnce();
			usleep(100000);
			if(Aig_G) AigDroit.publish(num_AIG);
		}

		//Verouillage de l'aiguillage
		AigVer.publish(num_AIG);
	}

	usleep(100000);
	
}


void A11::Aiguille_Navette()
{
	if(PS && this->get_Sh_Handle()!=-1)
	{
		
		/*if(this->get_Sh_Handle()%54<27)
		{
			this->STOP();

			this->Gauche();

			this->START();

			// Attente en fonction du temps de Vrep
			wait_vrep(Dt);
			this->STOP();

			PS=0;
			Send_Sh(-1);

			// Attente que la navette passe jusqu'à ce que CP2 s'active
			while(!Nav_CPG)
			{
				ros::spinOnce();
			}

			// Remise à zéro de CP10
			Nav_CPG=0;

		}
		else if(this->get_Sh_Handle()%54>=27)
		{
			this->STOP();
			
			this->Droit();

			this->START();

			// Attente en fonction du temps de Vrep
			wait_vrep(Dt);
			this->STOP();

			PS=0;
			Send_Sh(1);

			// Attente que la navette passe jusqu'à ce que CP9 s'active
			while(!Nav_CPD)
			{
				ros::spinOnce();
			}

			// Remise à zéro de CP9
			Nav_CPD=0;
		}*/

	

		srv_SetShuttleState.request.handle=this->get_Sh_Handle();
		client_SetShuttleState.call(srv_SetShuttleState);
		int destination = srv_SetShuttleState.response.destination;
		cout<<"destination : "<<destination<<endl;
		if(destination==1 || destination==2)
		{
			this->STOP();
			
			this->Droit();

			this->START();

			// Attente en fonction du temps de Vrep
			wait_vrep(Dt);
			this->STOP();

			PS=0;
			Send_Sh(1);

			// Attente que la navette passe jusqu'à ce que CP9 s'active
			while(!Nav_CPD)
			{
				ros::spinOnce();
			}

			// Remise à zéro de CP9
			Nav_CPD=0;
		}else
		{
			this->STOP();

			this->Gauche();

			this->START();

			// Attente en fonction du temps de Vrep
			wait_vrep(Dt);
			this->STOP();

			PS=0;
			Send_Sh(-1);

			// Attente que la navette passe jusqu'à ce que CP2 s'active
			while(!Nav_CPG)
			{
				ros::spinOnce();
			}

			// Remise à zéro de CP10
			Nav_CPG=0;
		}
	}
}




int A11::get_Sh_Handle()
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


void A11::Send_Sh(int destination)
{
	std::map<int,Sh*>::iterator it;
	int handle_min;
	
	handle_min=this->get_Sh_Handle();

	HandleShuttle.handle=handle_min;
	if(destination==1)
	{
		SendShuttle_d.publish(HandleShuttle);
	}else if(destination==-1)
	{
		SendShuttle_g.publish(HandleShuttle);
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


float A11::get_time()
{
	client_get_vrep_time.call(srv_get_time);
	return (float) srv_get_time.response.simulationTime;

}

void A11::wait_vrep(float dt)
{
	float t=this->get_time();
	while(this->get_time()-t<dt)
	{
		ros::spinOnce();
	}

}
