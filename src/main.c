/*
* Author: Slavomir Svorada
* File: main.c
* Description: Getting data from xplane 11 using plugin Xplane Connect Toolbox.
*/


#include "../src/xplaneConnect.h"
#include "stdio.h"
#include <stdlib.h>

int main(void)
{
	while (1)
	{
		//--------------------------------------------getDREFs() ENGINE-----------------------------------------------------
		const char* drefs[1] = {
			"sim/cockpit2/engine/indicators/prop_speed_rpm"
		};

		float* values[1];
		unsigned char count = 1;

		values[0] = (float*)malloc(8 * sizeof(float));

		int sizes[1] = { 8 };

		//-------------------------------------------------------------------------------------------------

		// AIRSPEED
		char* airspeed = "sim/flightmodel/position/indicated_airspeed";
		float getSpeeed = 0.0F;

		// PITCH
		char* pitch = "sim/flightmodel/position/true_theta";
		float getPitch = 0.0F;

		// ROLL
		char* roll = "sim/flightmodel/position/true_phi";
		float getRoll = 0.0F;

		// HEADING
		char* heading = "sim/flightmodel/position/mag_psi";
		float getHeading = 0.0F;

		// GROUNDSPEED TODO
		char* groundspeed = "sim/flightmodel/position/groundspeed";
		float getGroundspeed = 0.0F;

		// ALTITUDE
		char* altitude = "sim/cockpit2/gauges/indicators/altitude_ft_pilot";
		float getAltitude = 0.0F;

		// QNH TODO
		char* qnh = "sim/cockpit2/gauges/actuators/barometer_setting_in_hg_pilot";
		float getQnh = 0.0F;

		// TRUE AIRSPEED and SOUND for MACH NUMBER
		char* trueAirspeed = "sim/flightmodel/position/true_airspeed";
		float getTrueairspeed = 0.0F;
		char* sound = "sim/weather/speed_sound_ms";
		float getSound = 0.0F;

		// G-LOAD
		char* gload = "sim/flightmodel/forces/g_nrml";
		float getGload = 0.0F;

		// AIRPORT INDEX
		//char* airport = "sim/cockpit/gps/course";
		//float getAirport = 0.0F;

		int setSize = 8;

		// Gets the value of the specified dataref.
		//
		// \details dref names and their associated data types can be found on the XPSDK wiki at
		//          http://www.xsquawkbox.net/xpsdk/docs/DataRefs.html. The size of values should match
		//          the size given on that page. XPC currently sends all values as floats regardless of
		//          the type described on the wiki. This doesn't cause any data loss for most datarefs.
		// \param sock   The socket to use to send the command.
		// \param dref   The name of the dataref to get.
		// \param values The array in which the values of the dataref will be stored.
		// \param size   The number of elements in values. The actual number of elements copied in will
		//               be set when the function returns.
		// \returns      0 if successful, otherwise a negative value.

		// FUNCTION:	int getDREF(XPCSocket sock, const char* dref, float values[], int* size);

		// Connect with Xplane
		XPCSocket client = openUDP("127.0.0.1");

		// Get picth and roll from getPOSI function
		float posi[7];
		int test1 = getPOSI(client, posi, 0);
		if (test1 < 0)
		{
			printf("ERROR: getPOSI\n");
			continue;
		}
		printf("POSI: %f | %f \n", posi[3], posi[4]);

		// Airspeed
		int getResult = getDREF(client, airspeed, &getSpeeed, &setSize);

		// Groundspeed
		int getResult1 = getDREF(client, groundspeed, &getGroundspeed, &setSize);

		// Heading
		int getResult2 = getDREF(client, heading, &getHeading, &setSize);

		// Pitch
		//int getResult3 = getDREF(client, pitch, &getPitch, &setSize);

		// Roll
		//int getResult4 = getDREF(client, roll, &getRoll, &setSize);

		// Altitude
		int getResult5 = getDREF(client, altitude, &getAltitude, &setSize);

		// QNH
		int getResult6 = getDREF(client, qnh, &getQnh, &setSize);

		// True Airspeed and Sound
		int getResult8 = getDREF(client, trueAirspeed, &getTrueairspeed, &setSize);
		int getResult9 = getDREF(client, sound, &getSound, &setSize);

		// G-LOAD
		int getResult10 = getDREF(client, gload, &getGload, &setSize);

		// AIRPORT INDEX
		//int getResult11 = getDREF(client, airport, &getAirport, &setSize);

		if ((getResult < 0) || (getResult1 < 0) || (getResult2 < 0) || (getResult5 < 0) || (getResult6 < 0) || (getResult8 < 0) || (getResult9 < 0) || (getResult10 < 0))
		{
			continue;
		}

		if (getDREFs(client, drefs, values, count, sizes) < 0)
		{
		printf("ERROR: negative return values. \n");
		}
		else
		{
		printf("ENGINE = %.f | %.f | %.f | %.f \n", values[0][0], values[0][1], values[0][2], values[0][3]);
		}

		// Print results to console
		printf("AirSpeed: %.f | GroundSpeed: %.f | Heading: %.6f | Pitch: %.6f | Roll: %.6f | Altitude: %.6f | QNH: %.2f \n", getSpeeed, getGroundspeed, getHeading, posi[3], posi[4], getAltitude, getQnh);

		// write data to file
		FILE *fairspeed, *fgroundspeed, *fheading, *fpitch, *froll, *faltitude, *fqnh, *fengine, *fmach, *fgload;

		// AIRSPEED
		fairspeed = fopen("C:\\GETdata\\getAirspeed.txt", "w");
		if (fairspeed == NULL)
		{
			printf("ERROR: opening getAirspeed.txt file");
		}
		else
		{
			if (getSpeeed < 0)
			{
				fprintf(fairspeed, "%.f", (-1 * getSpeeed));
			}
			else
			{
				fprintf(fairspeed, "%.f", getSpeeed);
			}

			fclose(fairspeed);
		}
		// GROUNDSPEED
		fgroundspeed = fopen("C:\\GETdata\\getGroundspeed.txt", "w");
		if (fgroundspeed == NULL)
		{
			printf("ERROR: opening getGroundspeed.txt file");
		}
		else
		{
			if (getGroundspeed < 0)
			{
				fprintf(fgroundspeed, "%.f", ((-1 * getGroundspeed) * 1.943844));
			}
			else
			{
				fprintf(fgroundspeed, "%.f", (getGroundspeed * 1.943844));
			}

			fclose(fgroundspeed);
		}
		// Heading
		fheading = fopen("C:\\GETdata\\getHeading.txt", "w");
		if (fheading == NULL)
		{
			printf("ERROR: opening getHeading.txt file");
		}
		else
		{
			if (getHeading < 0)
			{
				fprintf(fheading, "%.25f", (-1 * getHeading));
			}
			else
			{
				fprintf(fheading, "%.25f", getHeading);
			}

			fclose(fheading);
		}
		// Pitch
		fpitch = fopen("C:\\GETdata\\getPitch.txt", "w");
		if (fpitch == NULL)
		{
			printf("ERROR: opening getPitch.txt file");
		}
		else
		{
			fprintf(fpitch, "%.25f", posi[3]);
			fclose(fpitch);
		}
		// Roll
		froll = fopen("C:\\GETdata\\getRoll.txt", "w");
		if (froll == NULL)
		{
			printf("ERROR: opening getRoll.txt file");
		}
		else
		{
			fprintf(froll, "%.25f", posi[4]);
			fclose(froll);
		}
		// ALTITUDE
		faltitude = fopen("C:\\GETdata\\getAltitude.txt", "w");
		if (faltitude == NULL)
		{
			printf("ERROR: opening getAltitude.txt file");
		}
		else
		{
			fprintf(faltitude, "%.25f", getAltitude);
			fclose(faltitude);
		}

		// QNH
		fqnh = fopen("C:\\GETdata\\getQnh.txt", "w");
		if (fqnh == NULL)
		{
			printf("ERROR: opening getQnh.txt file");
		}
		else
		{
			fprintf(fqnh, "%.2f", getQnh);
			fclose(fqnh);
		}

		// ENGINE PERFORMANCE
		fengine = fopen("C:\\GETdata\\getEngine.txt", "w");
		if (fengine == NULL)
		{
		printf("ERROR: opening getEngine.txt file");
		}
		else
		{
		fprintf(fengine, "%.f | %.f | %.f | %.f", values[0][0], values[0][1], values[0][2], values[0][3]);
		fclose(fengine);
		}

		// MACH NUMBER
		fmach = fopen("C:\\GETdata\\getMach.txt", "w");
		if (fmach == NULL)
		{
			printf("ERROR: opening getMach.txt file");
		}
		else
		{
			float mach_number = (getTrueairspeed / getSound);
			fprintf(fmach, "%.2f", mach_number);
			fclose(fmach);
		}

		// G-LOAD
		fgload = fopen("C:\\GETdata\\getGload.txt", "w");
		if (fgload == NULL)
		{
			printf("ERROR: opening getGload.txt file");
		}
		else
		{
			if (getGload < 0)
			{
				fprintf(fgload, "%.2f", (-1 * getGload));
			}
			else
			{
				fprintf(fgload, "%.2f", getGload);
			}

			fclose(fgload);
		}

		closeUDP(client);
	}

	return 0;
}