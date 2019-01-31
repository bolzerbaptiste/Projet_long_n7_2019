#include "A10.h"


using namespace std;

A10::A10(ros::NodeHandle nh)
{
	cout<<"Initialisation du callback"<<endl;



	VREPsubStopSensor = nh.subscribe("vrep/StopSensor", 10, &A10::StopSensorCallback, this);
	VREPsubSwitchSensor = nh.subscribe("vrep/SwitchSensor", 10, &A10::SwitchSensorCallback, this);


	DemiTour = nh.subscribe("/DemiTour/A3_A10", 10, &A10::DemiTourCallback, this);

	client_get_vrep_time = nh.serviceClient<vrep_common::simRosGetInfo>("/vrep/simRosGetInfo");

	ShStop = nh.advertise<std_msgs::Int32>("/commande/ArretNavette", 10);
	ShStart = nh.advertise<std_msgs::Int32>("/commande/DemarrerNavette", 10);
	AigDev = nh.advertise<std_msgs::Int32>("/commande/DeverouilleAiguillage", 10);
	AigVer = nh.advertise<std_msgs::Int32>("/commande/VerouilleAiguillage", 10);
	AigGauche = nh.advertise<std_msgs::Int32>("/commande/AiguillageGauche", 10);
	AigDroit = nh.advertise<std_msgs::Int32>("/commande/AiguillageDroit", 10);

	Aigok = nh.advertise<std_msgs::Int32>("/DemiTour/A10_A3", 10);

	SendShuttle = nh.advertise<aiguillages::ExchangeSh>("/IOShuttle/A10_A11", 1000);

	//ReceiveShuttle_d = nh.subscribe("/IOShuttle/P2_A12", 1000, &A2::NewShuttleCallBack_d, this);//avec les postes
	ReceiveShuttle_d = nh.subscribe("/commande_locale/New_Shuttle_Handle", 1000, &A10::NewShuttleCallBack_d, this);//sans les postes
	ReceiveShuttle_g = nh.subscribe("/IOShuttle/A3_A10", 1000, &A10::NewShuttleCallBack_g, this);

	
	Dt=0.7;
	

	PS_past=0;

	Nav_PS= 0;

	Nav_A3=0;


	num_aiguillage = 10;
	num_capt_stop = 19;
	num_capt_sortie = 20;
	

	num_STOP.data=num_capt_stop;

	num_AIG.data=num_aiguillage;


	usleep(1000000);
	this->STOP();


	
}
 




//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Callback////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void A10::StopSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{

	bool PSD_test= (msg->data & (int32_t)pow(2,num_capt_stop -1)) > 0;
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

void A10::DemiTourCallback(const std_msgs::Int32::ConstPtr& msg)

{
	Nav_A3=1;

}

//SwitchSensor
void A10::SwitchSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	Aig_D = (msg->data & (int32_t)pow(2,2*num_aiguillage-2)) > 0;
	Aig_G = (msg->data & (int32_t)pow(2,2*num_aiguillage-1)) > 0;
}


void A10::NewShuttleCallBack_d(const aiguillages::ExchangeSh::ConstPtr& msg)
{
	std_msgs::Header h = msg->header;
	cout<<"Handler de la navette"<<msg->handle<<endl;
	cout<<"heure reception"<<h.seq<<endl;

	Sh* newShuttle = new Sh(msg->handle,h.seq);

	ShuttlesMap.insert(std::pair<int,Sh*>(1,newShuttle));
	

	/////affichage
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

void A10::NewShuttleCallBack_g(const aiguillages::ExchangeSh::ConstPtr& msg)
{
	std_msgs::Header h = msg->header;
	cout<<"Handler de la navette"<<msg->handle<<endl;
	cout<<"heure reception"<<h.seq<<endl;

	Sh* newShuttle = new Sh(msg->handle,h.seq);

	ShuttlesMap.insert(std::pair<int,Sh*>(-1,newShuttle));
	

	/////affichage
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
	this->Send_Sh(-1);

}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Commande Aiguillage/////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void A10::STOP(){
	ShStop.publish(num_STOP);
}


void A10::START(){
	ShStart.publish(num_STOP);
}




void A10::Droit()
{
	//Deverouillage de l'aiguillage	haut
	if(!Aig_D)
	{
		AigDev.publish(num_AIG);

		usleep(100000);

		//Envoie ordre mouvement a droite haut
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

		//Verouillage des aiguillages	
		AigVer.publish(num_AIG);
	}
	
}

void A10::Gauche()
{
	if(!Aig_G)
	{
		//Deverouillage de l'aiguillage	haut
		AigDev.publish(num_AIG);

		
		usleep(100000);

		//Envoie ordre mouvement a gauche haut
		AigGauche.publish(num_AIG);

		usleep(300000);

		//Attente...
		while(!Aig_G)
		{
			if(Aig_D)
			{
				AigGauche.publish(num_AIG);
				usleep(100000);
			}
			ros::spinOnce();
		}

		//Verouillage des aiguillages	
		AigVer.publish(num_AIG);
	}
}

void A10::ModeManuel(){
	int aux;
	cout << "\nMode Manuel"<< endl;
	cout << "1) Gauche \t 2) Droite "<< endl;
	cin >> aux;

		if(aux==1){
			this->Gauche();
	 	}
		if(aux==2){
			this->Droit();
		}
		
}


void A10::Aiguille_Navette()
{

		if(Nav_A3)
		{
			this->Gauche();

			topic.data = 1;

			Aigok.publish(topic);
			Nav_A3=0;
			while(!Nav_PS)
			{
				usleep(100000);
				ros::spinOnce();
			}
			topic.data = -1;

			Aigok.publish(topic);
			Nav_PS=0;
		
		}else if(PSD  &&  this->get_Sh_Handle(1)!=-1)
		{
			this->Droit();
			
			
			this->START();
			wait_vrep(Dt);
			this->STOP();
			
			
			PSD=0;
			Send_Sh(1);
			while(!Nav_PS)
			{
				usleep(100000);
				ros::spinOnce();
			}
			Nav_PS=0;
		}


}

int A10::get_Sh_Handle(int origine)
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


void A10::Send_Sh(int origine)
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

float A10::get_time()
{
	
	client_get_vrep_time.call(srv_get_time);
	return (float) srv_get_time.response.simulationTime;


}

void A10::wait_vrep(float dt)
{
	
	float t=this->get_time();
	while(this->get_time()-t<dt)
	{
		
		ros::spinOnce();
	}

}

