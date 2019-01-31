/*
 * ********************************* *
 * Copyright 2016, STEC Projet Long. *
 * All rights reserved.  	     *
 * ********************************* *
*/


#include "UI.h"

const std::string trackbarname ="Product type";
const std::string winname = "Simulation";
int value = 0;
int numberOfProduct = 6;
int typeNextShuttle_aux;


// Button sizes
// Ici on defini la taille des boutons qui seront presents dans la simulation (on defini juste les tailles et non les boutons)

	int playButton_x_size = 110; 	// colum                     	BOUTON PLAY
	int playButton_y_size = 25; 	// row				BOUTON PLAY
	int pauseButton_x_size = 110; 	// colum			BOUTON PAUSE
	int pauseButton_y_size = 25; 	// row				BOUTON PAUSE	
	int shuttleButton_x_size = 110; // colum			BOUTON NAVETTE
	int shuttleButton_y_size = 25; 	// row				BOUTON NAVETTE
	int modeButton_x_size = 110; 	// colum			BOUTON MODE
	int modeButton_y_size = 25; 	// row				BOUTON MODE

	int TERbutton_x_size = 110; 	// colum			BOUTON TER
	int TERbutton_y_size = 25;  	// row				BOUTON TER

// Button positions
// Ici on defini la position des differents boutons qui seront present dans la simulation (on defini juste les position et non les boutons mêmes)

	int playButton_x_0 = 400-15; 	// colum			BOUTON PLAY
	int playButton_y_0 = 570;	// row				BOUTON PLAY
	int pauseButton_x_0 = 550-15; 	// colum			BOUTON PAUSE
	int pauseButton_y_0 = 570; 	// row				BOUTON PAUSE
	int shuttleButton_x_0 = 700-15; // colum			BOUTON NAVETTE
	int shuttleButton_y_0 = 570; 	// row				BOUTON NAVETTE
	int modeButton_x_0 = 475-15; 	// colum			BOUTON MODE
	int modeButton_y_0 = 570+50; 	// row				BOUTON MODE

	int TERbutton_x_0 = 625-15;	// colum			BOUTON TER
	int TERbutton_y_0 = 570+50;	// row 				BOUTON TER

// To activate and desactivate the Trackbar positions
//bool activeProduct[7]= {true, false, false, false, false, false, false};

// l'UI doit pouvoir controller la simu (Play & Pause) on defini ici le constructeur de UI
UI::UI(vrepController* VREPContrl,  Configuration* config)
{
	VREPController = VREPContrl;
	configuration = config;
}

// On actualise les aiguillages (On dessine des cercles gris, sur lequel on rajoute une droite ou un arc de cercle pour afficher l'etat de l'aiguillage)  
void UI::DrawSwitchSensorImg(commande_locale::Msg_SensorState SensorState)
{
	circle(imageTot, cv::Point(21+78, 241+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A01
	circle(imageTot, cv::Point(270+78, 252+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A02
	circle(imageTot, cv::Point(378+78, 235+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A03
	circle(imageTot, cv::Point(642+78, 235+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A04
	circle(imageTot, cv::Point(751+78, 252+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A05
	circle(imageTot, cv::Point(1002+78, 240+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A06
	circle(imageTot, cv::Point(1000+78, 126+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A07
	circle(imageTot, cv::Point(752+78, 111+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A08
	circle(imageTot, cv::Point(645+78, 126+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A09
	circle(imageTot, cv::Point(377+78, 129+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A10
	circle(imageTot, cv::Point(269+78, 112+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A11
	circle(imageTot, cv::Point(22+78, 125+570), 	17, 	cv::Scalar(200,200,200), -1); 		//A12

	if(SensorState.DD[1]) line(imageTot, 	cv::Point(14+78, 227+570), 	cv::Point(14+78, 255+570), 	cv::Scalar(0,100,0), 3); 	//A01
	if(SensorState.DG[1]) ellipse(imageTot, cv::Point(37+78, 220+570),	cv::Size(23,23),0,92,163,	cv::Scalar(0,100,0), 3);
	if(SensorState.DD[2]) ellipse(imageTot, cv::Point(290+78, 268+570),	cv::Size(23,23),0,183,255,	cv::Scalar(0,100,0), 3);	//A02
	if(SensorState.DG[2]) line(imageTot, 	cv::Point(257+78, 245+570), 	cv::Point(283+78, 245+570), 	cv::Scalar(0,100,0), 3);
	if(SensorState.DD[3]) line(imageTot, 	cv::Point(365+78, 243+570), 	cv::Point(391+78, 243+570), 	cv::Scalar(0,100,0), 3); 	//A03
	if(SensorState.DG[3]) ellipse(imageTot, cv::Point(358+78, 221+570),	cv::Size(23,23),0,73,1,		cv::Scalar(0,100,0), 3);
	if(SensorState.DD[4]) line(imageTot, 	cv::Point(629+78, 243+570), 	cv::Point(655+78, 243+570), 	cv::Scalar(0,100,0), 3); 	//A04
	if(SensorState.DG[4]) ellipse(imageTot, cv::Point(665+78, 220+570),	cv::Size(23,23),0,113,181,	cv::Scalar(0,100,0), 3);
	if(SensorState.DD[5]) ellipse(imageTot, cv::Point(732+78, 265+570),	cv::Size(23,23),0,284,363,	cv::Scalar(0,100,0), 3);	//A05
	if(SensorState.DG[5]) line(imageTot, 	cv::Point(738+78, 245+570), 	cv::Point(764+78, 245+570), 	cv::Scalar(0,100,0), 3); 
	if(SensorState.DD[6]) line(imageTot, 	cv::Point(1008+78, 226+570), 	cv::Point(1008+78, 253+570), 	cv::Scalar(0,100,0), 3);	//A06
	if(SensorState.DG[6]) ellipse(imageTot, cv::Point(985+78, 221+570),	cv::Size(23,23),0,83,12,	cv::Scalar(0,100,0), 3);
	if(SensorState.DD[7]) line(imageTot, 	cv::Point(1008+78, 113+570), 	cv::Point(1008+78, 139+570), 	cv::Scalar(0,100,0), 3); 	//A07
	if(SensorState.DG[7]) ellipse(imageTot, cv::Point(985+78, 145+570),	cv::Size(23,23),0,271,348,	cv::Scalar(0,100,0), 3);
	if(SensorState.DD[8]) ellipse(imageTot, cv::Point(733+78, 96+570),	cv::Size(23,23),0,75,3,		cv::Scalar(0,100,0), 3);	//A08
	if(SensorState.DG[8]) line(imageTot, 	cv::Point(740+78, 121+570), 	cv::Point(764+78, 121+570), 	cv::Scalar(0,100,0), 3); 
	if(SensorState.DD[9]) line(imageTot, 	cv::Point(631+78, 121+570), 	cv::Point(659+78, 121+570), 	cv::Scalar(0,100,0), 3); 	//A09
	if(SensorState.DG[9]) ellipse(imageTot, cv::Point(665+78, 143+570),	cv::Size(23,23),0,184,256,	cv::Scalar(0,100,0), 3);
	if(SensorState.DD[10]) line(imageTot, 	cv::Point(363+78, 122+570), 	cv::Point(390+78, 122+570), 	cv::Scalar(0,100,0), 3); 	//A10
	if(SensorState.DG[10]) ellipse(imageTot,cv::Point(358+78, 144+570),	cv::Size(23,23),0,282,357,	cv::Scalar(0,100,0), 3);
	if(SensorState.DD[11]) ellipse(imageTot,cv::Point(290+78, 98+570),	cv::Size(23,23),0,110,183,	cv::Scalar(0,100,0), 3); 	//A11
	if(SensorState.DG[11]) line(imageTot, 	cv::Point(257+78, 121+570), 	cv::Point(281+78, 121+570), 	cv::Scalar(0,100,0), 3);
	if(SensorState.DD[12]) line(imageTot, 	cv::Point(14+78, 112+570), 	cv::Point(14+78 , 138+570), 	cv::Scalar(0,100,0), 3); 	//A12
	if(SensorState.DG[12]) ellipse(imageTot,cv::Point(38+78, 145+570),	cv::Size(23,23),0,194,268,	cv::Scalar(0,100,0), 3);

	update();
}

// On actualise l'etat des capteurs des stations de travail (cercle rouge ou vert)
void UI::DrawStationSensorImg(commande_locale::Msg_SensorState SensorState)
{
    	circle(imageTot, cv::Point(88+78, 345+570), 5, cv::Scalar(0,255*SensorState.CPI[1],255-255*SensorState.CPI[1]), -1, 8 );
    	circle(imageTot, cv::Point(172+78, 345+570), 5, cv::Scalar(0,255*SensorState.CPI[2],255-255*SensorState.CPI[2]), -1, 8 );
    	circle(imageTot, cv::Point(860+78, 344+570), 5, cv::Scalar(0,255*SensorState.CPI[3],255-255*SensorState.CPI[3]), -1, 8 );
    	circle(imageTot, cv::Point(945+78, 346+570), 5, cv::Scalar(0,255*SensorState.CPI[4],255-255*SensorState.CPI[4]), -1, 8 );
    	circle(imageTot, cv::Point(908+78, 22+570), 5, cv::Scalar(0,255*SensorState.CPI[5],255-255*SensorState.CPI[5]), -1, 8 );
    	circle(imageTot, cv::Point(825+78, 22+570), 5, cv::Scalar(0,255*SensorState.CPI[6],255-255*SensorState.CPI[6]), -1, 8 );
    	circle(imageTot, cv::Point(169+78, 20+570), 5, cv::Scalar(0,255*SensorState.CPI[7],255-255*SensorState.CPI[7]), -1, 8 );
    	circle(imageTot, cv::Point(83+78, 20+570), 5, cv::Scalar(0,255*SensorState.CPI[8],255-255*SensorState.CPI[8]), -1, 8 );

	update();
}

// On actualise l'etat des capteurs des rails (cercle rouge ou vert)
void UI::DrawRailSensorImg(commande_locale::Msg_SensorState SensorState)
{
	circle(imageTot, cv::Point(45+78, 349+570), 5, cv::Scalar(0,255*SensorState.CP[1],255-255*SensorState.CP[1]), -1, 8 );
	circle(imageTot, cv::Point(122+78, 231+570), 5, cv::Scalar(0,255*SensorState.CP[2],255-255*SensorState.CP[2]), -1, 8 );
  	circle(imageTot, cv::Point(447+78, 231+570), 5, cv::Scalar(0,255*SensorState.CP[3],255-255*SensorState.CP[3]), -1, 8 );
	circle(imageTot, cv::Point(788+78, 348+570), 5, cv::Scalar(0,255*SensorState.CP[4],255-255*SensorState.CP[4]), -1, 8 );
	circle(imageTot, cv::Point(806+78, 230+570), 5, cv::Scalar(0,255*SensorState.CP[5],255-255*SensorState.CP[5]), -1, 8 );
	circle(imageTot, cv::Point(981+78, 18+570), 5, cv::Scalar(0,255*SensorState.CP[6],255-255*SensorState.CP[6]), -1, 8 );
	circle(imageTot, cv::Point(878+78, 135+570), 5, cv::Scalar(0,255*SensorState.CP[7],255-255*SensorState.CP[7]), -1, 8 );
	circle(imageTot, cv::Point(576+78, 135+570), 5, cv::Scalar(0,255*SensorState.CP[8],255-255*SensorState.CP[8]), -1, 8 );
	circle(imageTot, cv::Point(236+78, 16+570), 5, cv::Scalar(0,255*SensorState.CP[9],255-255*SensorState.CP[9]), -1, 8 );
	circle(imageTot, cv::Point(190+78, 135+570), 5, cv::Scalar(0,255*SensorState.CP[10],255-255*SensorState.CP[10]), -1, 8 );

	update();
}

// On actualise l'etat des capteurs des stops (cercle rouge ou vert)
void UI::DrawStopSensorImg(commande_locale::Msg_SensorState SensorState)
{
    	circle(imageTot, cv::Point(27+78, 181+570), 	5, 	cv::Scalar(0,255*SensorState.PS[1],255-255*SensorState.PS[1]), 	-1, 8 );
   	circle(imageTot, cv::Point(115+78, 345+570),	5, 	cv::Scalar(0,255*SensorState.PS[2],255-255*SensorState.PS[2]), 	-1, 8 );
    	circle(imageTot, cv::Point(198+78, 345+570),	5, 	cv::Scalar(0,255*SensorState.PS[3],255-255*SensorState.PS[3]), 	-1, 8 );
    	circle(imageTot, cv::Point(241+78, 230+570), 	5, 	cv::Scalar(0,255*SensorState.PS[4],255-255*SensorState.PS[4]), 	-1, 8 );
    	circle(imageTot, cv::Point(248+78, 342+570), 	5, 	cv::Scalar(0,255*SensorState.PS[5],255-255*SensorState.PS[5]), 	-1, 8 );
    	circle(imageTot, cv::Point(326+78, 230+570), 	5, 	cv::Scalar(0,255*SensorState.PS[6],255-255*SensorState.PS[6]), 	-1, 8 );
    	circle(imageTot, cv::Point(572+78, 231+570), 	5, 	cv::Scalar(0,255*SensorState.PS[7],255-255*SensorState.PS[7]), 	-1, 8 );
    	circle(imageTot, cv::Point(700+78, 231+570), 	5, 	cv::Scalar(0,255*SensorState.PS[8],255-255*SensorState.PS[8]), 	-1, 8 );
    	circle(imageTot, cv::Point(834+78, 345+570), 	5, 	cv::Scalar(0,255*SensorState.PS[9],255-255*SensorState.PS[9]), 	-1, 8 );
    	circle(imageTot, cv::Point(922+78, 347+570), 	5, 	cv::Scalar(0,255*SensorState.PS[10],255-255*SensorState.PS[10]),-1, 8 );
    	circle(imageTot, cv::Point(934+78, 232+570), 	5, 	cv::Scalar(0,255*SensorState.PS[11],255-255*SensorState.PS[11]),-1, 8 );
    	circle(imageTot, cv::Point(992+78, 339+570), 	5, 	cv::Scalar(0,255*SensorState.PS[12],255-255*SensorState.PS[12]),-1, 8 );
    	circle(imageTot, cv::Point(995+78, 189+570),	5, 	cv::Scalar(0,255*SensorState.PS[13],255-255*SensorState.PS[13]),-1, 8 );
    	circle(imageTot, cv::Point(934+78, 21+570), 	5, 	cv::Scalar(0,255*SensorState.PS[14],255-255*SensorState.PS[14]),-1, 8 );
    	circle(imageTot, cv::Point(852+78, 22+570), 	5, 	cv::Scalar(0,255*SensorState.PS[15],255-255*SensorState.PS[15]),-1, 8 );
    	circle(imageTot, cv::Point(783+78, 135+570), 	5, 	cv::Scalar(0,255*SensorState.PS[16],255-255*SensorState.PS[16]),-1, 8 );
    	circle(imageTot, cv::Point(770+78, 28+570), 	5, 	cv::Scalar(0,255*SensorState.PS[17],255-255*SensorState.PS[17]),-1, 8 );
    	circle(imageTot, cv::Point(701+78, 136+570), 	5, 	cv::Scalar(0,255*SensorState.PS[18],255-255*SensorState.PS[18]),-1, 8 );
    	circle(imageTot, cv::Point(454+78, 135+570), 	5, 	cv::Scalar(0,255*SensorState.PS[19],255-255*SensorState.PS[19]),-1, 8 );
    	circle(imageTot, cv::Point(321+78, 135+570), 	5, 	cv::Scalar(0,255*SensorState.PS[20],255-255*SensorState.PS[20]),-1, 8 );
    	circle(imageTot, cv::Point(195+78, 20+570), 	5, 	cv::Scalar(0,255*SensorState.PS[21],255-255*SensorState.PS[21]),-1, 8 );
    	circle(imageTot, cv::Point(109+78, 20+570), 	5, 	cv::Scalar(0,255*SensorState.PS[22],255-255*SensorState.PS[22]),-1, 8 );
    	circle(imageTot, cv::Point(66+78, 135+570), 	5, 	cv::Scalar(0,255*SensorState.PS[23],255-255*SensorState.PS[23]),-1, 8 );
    	circle(imageTot, cv::Point(29+78, 26+570), 	5, 	cv::Scalar(0,255*SensorState.PS[24],255-255*SensorState.PS[24]),-1, 8 );

    	update();

}

// On intègre le stream de la simu et l'état des capteurs et aiguillage dans l'UI
void UI::update()
{
	//imageSimu.copyTo(imageTot.rowRange(294-128,294+128).colRange(590-256,590+256));
	imageSimu.copyTo(imageTot.rowRange(18+20,530+20).colRange(78,1102));
 	//imageSensor.copyTo(imageTot.rowRange(570,936).colRange(78,1102));

	// To change the value of the trackbar if the user put a forbiden value
	if (!configuration->activeProduct[typeNextShuttle_aux]) {
		std::cout << "Value forbiden"<< std::endl;
		
		do{
			typeNextShuttle_aux --;
		}while(!configuration->activeProduct[typeNextShuttle_aux]);
		std::cout << "next value available: "<< typeNextShuttle_aux <<std::endl;
		cv::setTrackbarPos(trackbarname, winname, typeNextShuttle_aux);
	}

	if ( modeShuttle == 2 )
	{
		typeNextShuttle = typeNextShuttle_aux *10;
	}

	cv::imshow("Simulation", imageTot);
}

// Fonction Callback du Stream de la simu
void UI::getSimuStream(const sensor_msgs::ImageConstPtr& msg)
{
	imageSimu = cv_bridge::toCvShare(msg, "bgr8")->image;
	update();
}

// Fonction callback des infos sur la souris
void onMouse(int event, int x, int y, int, void* userdata)
{
    UI* ui = static_cast<UI*>(userdata);
    ui->onMouse_internal(event, x, y);
}

/* Fonction appellée pour mettre Play ou Pause à la simu 
et changer l'etat des boutons, en fonction de la position de la souris, contrôle aussi le bouton pour ajouter une plateforme à la simu */
void UI::onMouse_internal( int event, int x, int y)
{
	static vrep_common::simRosStartSimulation srv_StartSimulation;		
	static vrep_common::simRosPauseSimulation srv_PauseSimulation;
	static vrep_common::simRosLoadModel srv_LoadModel;

	switch(event) {
		case cv::EVENT_LBUTTONDOWN :   // Event lorsque l'on clique sur le bouton gauche de la souris 
   		if(y>playButton_y_0 && y < playButton_y_0+playButton_y_size && x>playButton_x_0 && x < playButton_x_0 + playButton_x_size && mode!= 1) {
					playButton_Down.copyTo(imageTot.rowRange(playButton_y_0,playButton_y_0+playButton_y_size).colRange(playButton_x_0,playButton_x_0+playButton_x_size));
					pauseButton.copyTo(imageTot.rowRange(pauseButton_y_0,pauseButton_y_0+pauseButton_y_size).colRange(pauseButton_x_0,pauseButton_x_0+pauseButton_x_size));
					VREPController->play();  //On lance la simu si on clique sur le bouton play
					mode = 1; }
    		else if(y>pauseButton_y_0 && y < pauseButton_y_0+pauseButton_y_size && x>pauseButton_x_0 && x < pauseButton_x_0 + pauseButton_x_size  && mode !=0) {
					playButton.copyTo(imageTot.rowRange(playButton_y_0,playButton_y_0+playButton_y_size).colRange(playButton_x_0,playButton_x_0+playButton_x_size));
					pauseButton_Down.copyTo(imageTot.rowRange(pauseButton_y_0,pauseButton_y_0+pauseButton_y_size).colRange(pauseButton_x_0,pauseButton_x_0+pauseButton_x_size));
					shuttleButton_Down.copyTo(imageTot.rowRange(shuttleButton_y_0,shuttleButton_y_0+shuttleButton_y_size).colRange(shuttleButton_x_0,shuttleButton_x_0+shuttleButton_x_size));
					VREPController->pause(); // On met la simu en pause si on clique sur le bouton pause
					mode = 0; }
		else if(y>shuttleButton_y_0 && y < shuttleButton_y_0+shuttleButton_y_size && x>shuttleButton_x_0 && x < shuttleButton_x_0 + shuttleButton_x_size && mode!= 0 && modeShuttle !=1 && modeShuttle !=0) {
					shuttleButton_Down.copyTo(imageTot.rowRange(shuttleButton_y_0,shuttleButton_y_0+shuttleButton_y_size).colRange(shuttleButton_x_0,shuttleButton_x_0+shuttleButton_x_size));
					configuration->ProductAdd('F', typeNextShuttle);
					}

		else if(y>modeButton_y_0 && y < modeButton_y_0+shuttleButton_y_size && x>modeButton_x_0 && x < modeButton_x_0 + modeButton_x_size && modeShuttle == 0 && mode!=1 && modeTER == 0)
		{
				modeAutoButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
				shuttleButton_Down.copyTo(imageTot.rowRange(shuttleButton_y_0,shuttleButton_y_0+shuttleButton_y_size).colRange(shuttleButton_x_0,shuttleButton_x_0+shuttleButton_x_size));
				modeShuttle = 1;
				std_msgs::Bool modeMsg;
				modeMsg.data = true;
				pubStateButton.publish(modeMsg);
		}		
		else if(y>modeButton_y_0 && y < modeButton_y_0+shuttleButton_y_size && x>modeButton_x_0 && x < modeButton_x_0 + modeButton_x_size && modeShuttle == 1 && mode!=1 && modeTER == 0)
		{
				modeManuButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
				modeShuttle = 2;
				
				std_msgs::Bool modeMsg;
				modeMsg.data = false;
				pubStateButton.publish(modeMsg);
		}
		else if(y>modeButton_y_0 && y < modeButton_y_0+shuttleButton_y_size && x>modeButton_x_0 && x < modeButton_x_0 + modeButton_x_size && modeShuttle == 2 && mode!=1 && modeTER == 0)
		{
				modeRandButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
				modeShuttle = 3;
				typeNextShuttle = -1 ;
				std_msgs::Bool modeMsg;
				modeMsg.data = false;
				pubStateButton.publish(modeMsg);
		}
		else if(y>modeButton_y_0 && y < modeButton_y_0+shuttleButton_y_size && x>modeButton_x_0 && x < modeButton_x_0 + modeButton_x_size && modeShuttle == 3 && mode!=1 && modeTER == 0)
		{
				modeAutoButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
				shuttleButton_Down.copyTo(imageTot.rowRange(shuttleButton_y_0,shuttleButton_y_0+shuttleButton_y_size).colRange(shuttleButton_x_0,shuttleButton_x_0+shuttleButton_x_size));
				modeShuttle = 1;
				std_msgs::Bool modeMsg;
				modeMsg.data = true;
				pubStateButton.publish(modeMsg);
		}
		else if(y>TERbutton_y_0 && y < TERbutton_y_0+TERbutton_y_size && x>TERbutton_x_0 && x < TERbutton_x_0+TERbutton_x_size && modeTER == 0)
		{
				TERbutton_on.copyTo(imageTot.rowRange(TERbutton_y_0,TERbutton_y_0+TERbutton_y_size).colRange(TERbutton_x_0,TERbutton_x_0+TERbutton_x_size));
				modeTER = 1;
				std_msgs::Bool modeTERmsg;
				modeTERmsg.data = true;
				pubStateTERbutton.publish(modeTERmsg);
		}
		else if(y>TERbutton_y_0 && y < TERbutton_y_0+TERbutton_y_size && x>TERbutton_x_0 && x < TERbutton_x_0+TERbutton_x_size && modeTER == 1)
		{
				TERbutton.copyTo(imageTot.rowRange(TERbutton_y_0,TERbutton_y_0+TERbutton_y_size).colRange(TERbutton_x_0,TERbutton_x_0+TERbutton_x_size));
				modeTER = 0;
				std_msgs::Bool modeTERmsg;
				modeTERmsg.data = false;
				pubStateTERbutton.publish(modeTERmsg);
		}	
		
		break;

		case cv::EVENT_MOUSEMOVE :
   		if(y>playButton_y_0 && y < playButton_y_0+playButton_y_size && x>playButton_x_0 && x < playButton_x_0 + playButton_x_size && mode!= 1)
					playButton_On.copyTo(imageTot.rowRange(playButton_y_0,playButton_y_0+playButton_y_size).colRange(playButton_x_0,playButton_x_0+playButton_x_size));
				else if (mode!= 1)
					playButton.copyTo(imageTot.rowRange(playButton_y_0,playButton_y_0+playButton_y_size).colRange(playButton_x_0,playButton_x_0+playButton_x_size));

    		if(y>pauseButton_y_0 && y < pauseButton_y_0+pauseButton_y_size && x>pauseButton_x_0 && x < pauseButton_x_0 + pauseButton_x_size && mode !=0)
					pauseButton_On.copyTo(imageTot.rowRange(pauseButton_y_0,pauseButton_y_0+pauseButton_y_size).colRange(pauseButton_x_0,pauseButton_x_0+pauseButton_x_size));
				else if (mode!= 0)
					pauseButton.copyTo(imageTot.rowRange(pauseButton_y_0,pauseButton_y_0+pauseButton_y_size).colRange(pauseButton_x_0,pauseButton_x_0+pauseButton_x_size));

		if(y>shuttleButton_y_0 && y < shuttleButton_y_0+shuttleButton_y_size && x>shuttleButton_x_0 && x < shuttleButton_x_0 + shuttleButton_x_size && mode!= 0 && modeShuttle != 0 && modeShuttle != 1)
					shuttleButton_On.copyTo(imageTot.rowRange(shuttleButton_y_0,shuttleButton_y_0+shuttleButton_y_size).colRange(shuttleButton_x_0,shuttleButton_x_0+shuttleButton_x_size));
			else if (mode!= 0 && modeShuttle != 0 && modeShuttle != 1)
					shuttleButton.copyTo(imageTot.rowRange(shuttleButton_y_0,shuttleButton_y_0+shuttleButton_y_size).colRange(shuttleButton_x_0,shuttleButton_x_0+shuttleButton_x_size));


		if(y>modeButton_y_0 && y < modeButton_y_0+shuttleButton_y_size && x>modeButton_x_0 && x < modeButton_x_0 + modeButton_x_size && modeShuttle == 0 && mode != 1)
					modeButton_On.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
				else if (modeShuttle == 0 && mode !=1)
					modeButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
		if(y>modeButton_y_0 && y < modeButton_y_0+shuttleButton_y_size && x>modeButton_x_0 && x < modeButton_x_0 + modeButton_x_size && modeShuttle == 1 && mode != 1)
					modeAutoButton_On.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
				else if (modeShuttle == 1 && mode !=1)
					modeAutoButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
		if(y>modeButton_y_0 && y < modeButton_y_0+shuttleButton_y_size && x>modeButton_x_0 && x < modeButton_x_0 + modeButton_x_size && modeShuttle == 2 && mode != 1)
					modeManuButton_On.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
				else if (modeShuttle == 2 && mode !=1)
					modeManuButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
		if(y>modeButton_y_0 && y < modeButton_y_0+shuttleButton_y_size && x>modeButton_x_0 && x < modeButton_x_0 + modeButton_x_size && modeShuttle == 3 && mode != 1)
					modeRandButton_On.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
				else if (modeShuttle == 3 && mode !=1)
					modeRandButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
		if(y>TERbutton_y_0 && y < TERbutton_y_0+TERbutton_y_size && x>TERbutton_x_0 && x < TERbutton_x_0+TERbutton_x_size && modeTER == 0)
					TERbutton_down.copyTo(imageTot.rowRange(TERbutton_y_0,TERbutton_y_0+TERbutton_y_size).colRange(TERbutton_x_0,TERbutton_x_0+TERbutton_x_size));
				else if (modeTER == 0)
					TERbutton.copyTo(imageTot.rowRange(TERbutton_y_0,TERbutton_y_0+TERbutton_y_size).colRange(TERbutton_x_0,TERbutton_x_0+TERbutton_x_size));
			
		break;
	}
}


static void onChangeTrackbar(int, void*){
	//std::cout << value << std::endl;
	typeNextShuttle_aux = value;
}


void UI::init(ros::NodeHandle nh){   // Fonction d'initialisation de l'ui 

// Search of the images for the GUI
	// 1) Sensor image
	std::string path_ImageSensor = ros::package::getPath("commande_locale") + "/img/Schema_cellule.png";

	// 2) Play Button
	std::string path_PlayButton = ros::package::getPath("commande_locale") + "/img/PlayButton.png";
	std::string path_PlayButton_Down = ros::package::getPath("commande_locale") + "/img/PlayButton_Down.png";
	std::string path_PlayButton_On = ros::package::getPath("commande_locale") + "/img/PlayButton_On.png";

	// 3) Pause Button
	std::string path_PauseButton = ros::package::getPath("commande_locale") + "/img/PauseButton.png";
	std::string path_PauseButton_Down = ros::package::getPath("commande_locale") + "/img/PauseButton_Down.png";
	std::string path_PauseButton_On = ros::package::getPath("commande_locale") + "/img/PauseButton_On.png";

	// 4) Shuttle Button
	std::string path_ShuttleButton = ros::package::getPath("commande_locale") + "/img/ShuttleButton.png";
	std::string path_ShuttleButton_Down = ros::package::getPath("commande_locale") + "/img/ShuttleButton_Down.png";
	std::string path_ShuttleButton_On = ros::package::getPath("commande_locale") + "/img/ShuttleButton_On.png";

	// 5) Mode Button
	std::string path_ModeButton = ros::package::getPath("commande_locale") + "/img/ModeButton.png";
	std::string path_ModeButton_On = ros::package::getPath("commande_locale") + "/img/ModeButton_On.png";
	std::string path_AutoButton 	= ros::package::getPath("commande_locale") + "/img/AutoButton.png";
	std::string path_AutoButton_On 	= ros::package::getPath("commande_locale") + "/img/AutoButton_On.png";
	std::string path_ManualButton 	= ros::package::getPath("commande_locale") + "/img/ManualButton.png";
	std::string path_ManualButton_On = ros::package::getPath("commande_locale") + "/img/ManualButton_On.png";
	std::string path_RandomButton 	= ros::package::getPath("commande_locale") + "/img/RandomButton.png";
	std::string path_RandomButton_On = ros::package::getPath("commande_locale") + "/img/RandomButton_On.png";

	// 6) TER button
	std::string path_TERbutton = ros::package::getPath("commande_locale") + "/img/TERbutton.png";
	std::string path_TERbutton_down = ros::package::getPath("commande_locale") + "/img/TERbutton_down.png";
	std::string path_TERbutton_on = ros::package::getPath("commande_locale") + "/img/TERbutton_on.png";


// Upload of the images to the internal variables
	imageSensor = cv::imread(path_ImageSensor,CV_LOAD_IMAGE_COLOR);
	imageSimu = cv::Mat::zeros(512, 1024, CV_8UC3 );
	//imageSimu = cv::Mat::zeros(256, 512, CV_8UC3);
	imageTot = cv::Mat::zeros(950, 1180, CV_8UC3 );
	imageTot.setTo(cv::Scalar(200,200,200));

	playButton = cv::imread(	path_PlayButton,	CV_LOAD_IMAGE_COLOR);
	playButton_Down = cv::imread(	path_PlayButton_Down,	CV_LOAD_IMAGE_COLOR);
	playButton_On = cv::imread(	path_PlayButton_On,	CV_LOAD_IMAGE_COLOR);

	pauseButton = cv::imread(	path_PauseButton,	CV_LOAD_IMAGE_COLOR);
	pauseButton_Down = cv::imread(	path_PauseButton_Down,	CV_LOAD_IMAGE_COLOR);
	pauseButton_On = cv::imread(	path_PauseButton_On,	CV_LOAD_IMAGE_COLOR);

	shuttleButton = cv::imread(	path_ShuttleButton,	CV_LOAD_IMAGE_COLOR);
	shuttleButton_Down = cv::imread(path_ShuttleButton_Down,CV_LOAD_IMAGE_COLOR);
	shuttleButton_On = cv::imread(	path_ShuttleButton_On,	CV_LOAD_IMAGE_COLOR);

	modeButton = cv::imread(	path_ModeButton,	CV_LOAD_IMAGE_COLOR);
	modeButton_On = cv::imread(	path_ModeButton_On,	CV_LOAD_IMAGE_COLOR);
	modeAutoButton = cv::imread(	path_AutoButton,	CV_LOAD_IMAGE_COLOR);
	modeAutoButton_On = cv::imread(	path_AutoButton_On,	CV_LOAD_IMAGE_COLOR);
	modeManuButton = cv::imread(	path_ManualButton,	CV_LOAD_IMAGE_COLOR);
	modeManuButton_On = cv::imread(	path_ManualButton_On,	CV_LOAD_IMAGE_COLOR);
	modeRandButton = cv::imread(	path_RandomButton,	CV_LOAD_IMAGE_COLOR);
	modeRandButton_On = cv::imread(	path_RandomButton_On,	CV_LOAD_IMAGE_COLOR);

	TERbutton = cv::imread(		path_TERbutton,		CV_LOAD_IMAGE_COLOR);
	TERbutton_down = cv::imread(	path_TERbutton_down,	CV_LOAD_IMAGE_COLOR);
	TERbutton_on = cv::imread(	path_TERbutton_on,	CV_LOAD_IMAGE_COLOR);

// Check for invalid input in the images
	if(! imageSensor.data )		{std::cout <<  "Could not open or find the image 'Schema_cellule.png'" << std::endl ;}

	if(! playButton.data )		{std::cout <<  "Could not open or find the image 'PlayButton.png'" << std::endl ;}
	if(! playButton_Down.data )	{std::cout <<  "Could not open or find the image 'PlayButton_Down.png'" << std::endl ;}
	if(! playButton_On.data )	{std::cout <<  "Could not open or find the image 'PlayButton_On.png'" << std::endl ;}

	if(! pauseButton.data )		{std::cout <<  "Could not open or find the image 'PauseButton.png'" << std::endl ;}
	if(! pauseButton_Down.data )	{std::cout <<  "Could not open or find the image 'PauseButton_Down.png'" << std::endl ;}
	if(! pauseButton_On.data )	{std::cout <<  "Could not open or find the image 'PauseButton_On.png'" << std::endl ;}


	if(! shuttleButton.data )	{std::cout <<  "Could not open or find the image 'ShuttleButton.png'" << std::endl ;}
	if(! shuttleButton_Down.data )	{std::cout <<  "Could not open or find the image 'ShuttleButton_Down.png'" << std::endl ;}
	if(! shuttleButton_On.data )	{std::cout <<  "Could not open or find the image 'ShuttleButton_On.png'" << std::endl ;}

	if(! modeButton.data )		{std::cout <<  "Could not open or find the image 'ModeButton.png'" << std::endl ;}
	if(! modeButton_On.data )	{std::cout <<  "Could not open or find the image 'ModeButton_On.png'" << std::endl ;}
	if(! modeAutoButton.data )	{std::cout <<  "Could not open or find the image 'ModeAutoButton.png'" << std::endl ;}
	if(! modeAutoButton_On.data )	{std::cout <<  "Could not open or find the image 'ModeAutoButton_On.png'" << std::endl ;}
	if(! modeManuButton.data )	{std::cout <<  "Could not open or find the image 'ModeManuButton.png'" << std::endl ;}
	if(! modeManuButton_On.data )	{std::cout <<  "Could not open or find the image 'ModeManuButton_On.png'" << std::endl ;}
	if(! modeRandButton.data )	{std::cout <<  "Could not open or find the image 'ModeRandButton.png'" << std::endl ;}
	if(! modeRandButton_On.data )	{std::cout <<  "Could not open or find the image 'ModeRandButton_On.png'" << std::endl ;}

	if(! TERbutton.data ) 		{std::cout <<  "Could not open or find the image 'TERbutton.png'"<< std::endl ;}
	if(! TERbutton_down.data ) 		{std::cout <<  "Could not open or find the image 'TERbutton_down.png'"<< std::endl ;}
	if(! TERbutton_on.data ) 		{std::cout <<  "Could not open or find the image 'TERbutton_on.png'"<< std::endl ;}

	// Initialisation of the sensor background image
	imageSensor.copyTo(imageTot.rowRange(570,936).colRange(78,1102));

	// Initialisation of the necessary buttons
	rectangle(imageTot, cv::Point(75,15+20), cv::Point(1105,533+20),cv::Scalar(100,100,100),2);
	playButton.copyTo(imageTot.rowRange(playButton_y_0,playButton_y_0+playButton_y_size).colRange(playButton_x_0,playButton_x_0+playButton_x_size));
	pauseButton_Down.copyTo(imageTot.rowRange(pauseButton_y_0,pauseButton_y_0+pauseButton_y_size).colRange(pauseButton_x_0,pauseButton_x_0+pauseButton_x_size));	
	shuttleButton_Down.copyTo(imageTot.rowRange(shuttleButton_y_0,shuttleButton_y_0+shuttleButton_y_size).colRange(shuttleButton_x_0,shuttleButton_x_0+shuttleButton_x_size));
	modeButton.copyTo(imageTot.rowRange(modeButton_y_0,modeButton_y_0+modeButton_y_size).colRange(modeButton_x_0,modeButton_x_0+modeButton_x_size));
	TERbutton.copyTo(imageTot.rowRange(TERbutton_y_0,TERbutton_y_0+TERbutton_y_size).colRange(TERbutton_x_0,TERbutton_x_0+TERbutton_x_size));
 
	// Cadre des produits

	rectangle(imageTot, cv::Point(590-205, 936), cv::Point(590+205, 936-75), cv::Scalar(100,0,100), 2 );
	cv::putText(imageTot, "Produits a fabriquer :", cv::Point(590-205+5, 936-75+15), 2, 0.5, cv::Scalar(0,0,0), 1, 8, false);

	// Window
	cv::namedWindow("Simulation", 7);
	cv::startWindowThread();
	cv::moveWindow("Simulation",0,0);
	cv::setMouseCallback("Simulation", onMouse,this);
	

	// Trackbar
	int test = cv::createTrackbar(trackbarname, winname,&value, numberOfProduct, onChangeTrackbar);	
	onChangeTrackbar( value, 0 );
		// Text for the product type of the trackbar
			//putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness=1, int lineType=8, bool bottomLeftOrigin=false )
		cv::putText(imageTot, "Empty", cv::Point(90,22), 4, 0.5, cv::Scalar(0,0,0),1, 8,false );
	
		if(configuration->activeProduct[1]) cv::putText(imageTot, "A", cv::Point(286,25), 2, 0.8, cv::Scalar(0,0,0), 1, 8,false );
		if(configuration->activeProduct[2]) cv::putText(imageTot, "B", cv::Point(460,25), 2, 0.8, cv::Scalar(0,0,0), 1, 8,false );
		if(configuration->activeProduct[3]) cv::putText(imageTot, "C", cv::Point(634,25), 2, 0.8, cv::Scalar(0,0,0), 1, 8,false );
		if(configuration->activeProduct[4]) cv::putText(imageTot, "D", cv::Point(807,25), 2, 0.8, cv::Scalar(0,0,0), 1, 8,false );
		if(configuration->activeProduct[5]) cv::putText(imageTot, "E", cv::Point(982,25), 2, 0.8, cv::Scalar(0,0,0), 1, 8,false );
		if(configuration->activeProduct[6]) cv::putText(imageTot, "F", cv::Point(1155,25), 2, 0.8, cv::Scalar(0,0,0), 1, 8,false );


	// Subscribe
	image_transport::ImageTransport it(nh);
	subImage = it.subscribe("vrep/VisionSensorData", 1, &UI::getSimuStream, this);
	pubStateButton = nh.advertise<std_msgs::Bool>("/ordonnancement/On_Off",10);
	pubStateTERbutton = nh.advertise<std_msgs::Bool>("/ordonnancement/TER_on_off",10);

	mode = 0; // Mode 0 : Pause - Mode 1 : Play
	modeShuttle = 0;
	modeTER = 0;

	TxtNomProduits = "Liste des produits a faire : ";

	subNombreDeProduits = nh.subscribe("/ordonnancement/NombreDeProduits",1,&UI::NombreDeProduitsCallBack,this);
	subNomProduits = nh.subscribe("/ordonnancement/NomProduits",100,&UI::NomProduitsCallBack,this);
}


// On ferme la fenetre de Simulation
void UI::close(){
	cv::destroyWindow("Simulation");
}

// On ferme la fenetre de Simulation
bool UI::checkWindow(){
	int verif= 0; 
	
	 try
	  {
	    verif = cv::getWindowProperty("Simulation", 0);
	  }
	  catch (cv::Exception & e)
	  {	
		system("clear");
		std::cout << "-----------------------------------------------------"<< std::endl; 
		std::cout << "    The simulation window was closed by the user     "<< std::endl;
		std::cout << "                Good luck with the TER :)            "<< std::endl;
		std::cout << "-----------------------------------------------------"<< std::endl; 
		return false;
	  }
	return true;
}

// ON ajoute le nombre de produits à l'interface



void UI::NombreDeProduitsCallBack(const std_msgs::Int32::ConstPtr& NbMsg){

	int Nb = NbMsg-> data;
	std::string texte;
	//std::string text = "" + Nb;
	char numstr[23];
	sprintf(numstr, "%d", Nb);
	texte = "Produits a fabriquer : ";
	texte += numstr;
	cv::putText(imageTot, texte, cv::Point(590-205+5, 936-75+15), 2, 0.5, cv::Scalar(0,0,0), 1, 8, false);
}

void UI::NomProduitsCallBack(const std_msgs::String::ConstPtr& NomMsg){

	std::string ajout = NomMsg->data;	
	TxtNomProduits += ajout;
	TxtNomProduits += " ";
	std::cout << TxtNomProduits << std::endl;
	cv::putText(imageTot, TxtNomProduits, cv::Point(590-205+5, 966-75+15), 2, 0.5, cv::Scalar(0,0,0), 1, 8, false);
}
	

