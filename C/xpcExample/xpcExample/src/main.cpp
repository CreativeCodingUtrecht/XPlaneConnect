//
//  main.cpp
//  xpcExample
//
//  Created by Chris Teubert on 3/27/14.
//  Copyright (c) 2014 Chris Teubert. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "xplaneConnect.h"
#ifdef WIN32
#include <Windows.h>
#define sleep(n) Sleep(n * 1000)
#endif

int main()
{
	printf("XPlaneConnect Example Script\n- Setting up Simulation\n");

	// Open Socket
	const char* IP = "172.28.0.13";      //IP Address of computer running X-Plane
	XPCSocket sock = openUDP(IP);
	float tVal[1];
	int tSize = 1;
	if (getDREF(sock, "sim/test/test_float", tVal, &tSize) < 0)
	{
		printf("Error establishing connecting. Unable to read data from X-Plane.");
		return EXIT_FAILURE;
	}

    /*
	// Set Location/Orientation (sendPOSI)
	// Set Up Position Array
	double POSI[9] = { 0.0 };
	POSI[0] = 37.524;     // Lat
	POSI[1] = -122.06899; // Lon
	POSI[2] = 2500;       // Alt
	POSI[3] = 0;          // Pitch
	POSI[4] = 0;          // Roll
	POSI[5] = 0;          // Heading
	POSI[6] = 1;          // Gear

	// Set position of the player aircraft
	sendPOSI(sock, POSI, 7, 0);

	POSI[0] = 37.52465;   // Move a second aircraft a bit North of us
	POSI[4] = 20;         // Give that aircraft a bit or right roll
	// Set position of a multiplayer aircraft
	sendPOSI(sock, POSI, 7, 1);

	// Set Rates (sendDATA)
	float data[3][9] = { 0 };
	// Initialize data values to -998 to not overwrite values.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			data[i][j] = -998;
		}
	}
	// Set up Data Array (first item in row is item number (example: 20=position)
	data[0][0] = 18; // Alpha
	data[0][1] = 0;
	data[0][3] = 0;

	data[1][0] = 3;  //Velocity
	data[1][1] = 130;
	data[1][2] = 130;
	data[1][3] = 130;
	data[1][4] = 130;

	data[2][0] = 16; //PQR
	data[2][1] = 0;
	data[2][2] = 0;
	data[2][3] = 0;

	sendDATA(sock, data, 3);

    */
     
    /*
	// Set throttle on the player aircraft using sendCTRL
	float CTRL[5] = { 0.0 };
	CTRL[3] = 0.8; // Throttle
	sendCTRL(sock, CTRL, 5, 0);
    
    sleep(10);
    
    CTRL[3] = 0;
    sendCTRL(sock, CTRL, 5, 0);

	// pauseSim
//	pauseSim(sock, 1); // Sending 1 to pause
//	sleep(5); // Pause for 5 seconds

	// Unpause
//	pauseSim(sock, 0); // Sending 0 to unpause
//	printf("- Resuming Simulation\n");

	// Simulate for 10 seconds
	sleep(10);
     */

    // Show outside
//    printf("- Show outside\n");
//    sendCOMM(sock, "sim/view/spot");
    
    // Show X-Camera view 1
    printf("- Show X-Camera view 1\n");
    sendCOMM(sock, "SRS/X-Camera/Select_View_ID_1");


    // Set to night
    printf("- Make it night\n"); // only writable
    float val = 34000;
    sendDREF(sock, "sim/time/zulu_time_sec", &val, 1);

    sleep(2);
    
    printf("- Flare lights\n");
    sendCOMM(sock, "FJS/Q4XP/Switches/FLARE_LIGHTS");
    
    sleep(1);
    
    printf("- Position lights\n");
    sendCOMM(sock, "FJS/Q4XP/Switches/POSN_LIGHTS");
    
    sleep(1);

    printf("- Taxi lights\n");
    sendCOMM(sock, "FJS/Q4XP/Switches/TAXI_LIGHTS");
    
    
    sleep (1);
    
    // SendCOMM (Taxi lights off)
    printf("- Taxi lights \n");
    sendCOMM(sock, "FJS/Q4XP/Switches/TAXI_LIGHTS");

    sleep(1);
    
    printf("- Position lights\n");
    sendCOMM(sock, "FJS/Q4XP/Switches/POSN_LIGHTS");
    
    sleep(1);

    
    printf("- Flare lights\n");
    sendCOMM(sock, "FJS/Q4XP/Switches/FLARE_LIGHTS");

    
    sleep (2);
    
    // Set to noon
    printf("- Make it noon\n");
    val = 68000;
    sendDREF(sock, "sim/time/zulu_time_sec", &val, 1);
    
    sleep(2);

    // Show X-Camera view 1
    printf("- Show X-Camera view 1\n");
    sendCOMM(sock, "SRS/X-Camera/Momentary_Select_View_ID_1");

    sleep(4);
    
    // Show X-Camera view 10
    printf("- Show X-Camera view 10\n");
    sendCOMM(sock, "SRS/X-Camera/Momentary_Select_View_ID_10");

    sleep(4);
    
    // Show cockpit
    printf("- Show cockpit\n");
    sendCOMM(sock, "sim/view/track_weapon");


    
    
//    sleep (10);
    
    /*
    // SendDREF (Landing Gear)
	printf("- Stowing Landing Gear\n");

	const char* dref = "sim/cockpit/switches/gear_handle_status"; // Gear handle data reference
	float gear = 0; // Stow gear
	sendDREF(sock, dref, &gear, 1); // Set gear to stow

	// Simulate for 10 seconds
	sleep(10);

	// Check Landing gear, Pause
	printf("- Confirming Gear Status\n");
	const char* drefs[2] =
	{
		"sim/cockpit/switches/gear_handle_status",
		"sim/operation/override/override_planepath"
	};
	float* results[2];
	int sizes[2] = { 20, 20 };
	for (int i = 0; i < 2; ++i)
	{
		results[i] = (float*)malloc(20 * sizeof(float));
	}
	getDREFs(sock, drefs, results, 2, sizes);

	if (results[0][0] == 0)
	{
		printf("\tGear Stowed\n");
	}
	else
	{
		printf("\tERROR: Gear Stowage unsuccessful\n");
	}

    */
	printf("---End Program---\n");

	return 0;
}
