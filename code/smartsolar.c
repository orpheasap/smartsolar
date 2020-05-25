#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "linear_regression.h"

#define SIZE 1
#define NUMELEM 74

int main(int argc, char** argv)
{
    FILE* fp = NULL;
    char buff[100];
    char temp_raw[7];
    float temp_c, temp_chart[12] = { 0 };
    char mosquitto_cmd[1024], file_name[64];
    int minute, sec, i, ii, min_b=0, min_b15=1, hours, year, month, day;
	float x[12], a=0, b=0;
    time_t now;

	//set x[]
	for(i=0; i<12; i++) x[i] = 11-i;

    memset(buff, 0, sizeof(buff));
    memset(temp_raw, 0, sizeof(temp_raw));
    //Enable Temp
    system("sudo modprobe w1-gpio");
    system("sudo modprobe w1-therm");

    for (;;) {

		fp = fopen("/sys/bus/w1/devices/28-01144eec7eaa/w1_slave", "r");

		if(NULL == fp) {
			printf("\n fopen Error!!!\n\n");

		} else if (SIZE * NUMELEM != fread(buff, SIZE, NUMELEM, fp)) {
			printf("\n fread() failed\n");
			fclose(fp);
		} else {
			fclose(fp);
			//get temp_c
			temp_raw[0] = buff[69];
			temp_raw[1] = buff[70];
			temp_raw[2] = buff[71];
			temp_raw[3] = buff[72];
			temp_raw[4] = buff[73];
			temp_raw[5] = buff[74];
			temp_c = atof(temp_raw) / 1000;

			//publish temp_c,a to pi's mqtt
			sprintf(mosquitto_cmd, "mosquitto_pub -t temp -m \"%f %f\"", temp_c, a);
			system(mosquitto_cmd);

			

			//get current mins/sec
			time(&now);
			struct tm* local = localtime(&now);
			minute = local->tm_min;
			sec = local->tm_sec;
			
			// every 15' update table
			if ((minute % 15 == 0) && (min_b15 % 15!=0)) {

				for(ii = 11; ii > 0; ii--) {
					temp_chart[ii] = temp_chart[ii - 1];
				}
				temp_chart[0] = temp_c;

				//find a,b
				regression(x, temp_chart, 12, &a, &b);

				// publish table,a,b to pi's mqtt
				sprintf(mosquitto_cmd, "mosquitto_pub -r -t temp_chart -m \"%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\"",
					temp_chart[0], temp_chart[1], temp_chart[2], temp_chart[3], temp_chart[4], temp_chart[5],
					temp_chart[6], temp_chart[7], temp_chart[8], temp_chart[9], temp_chart[10], temp_chart[11], a, b);
				system(mosquitto_cmd);

				// publish table,a,b to test.mosquitto.org
				sprintf(mosquitto_cmd, "mosquitto_pub -h test.mosquitto.org"
					" -t smartsolar/temp_chart -r -m \"%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\"",
					temp_chart[0], temp_chart[1], temp_chart[2], temp_chart[3], temp_chart[4], temp_chart[5],
					temp_chart[6], temp_chart[7], temp_chart[8], temp_chart[9], temp_chart[10], temp_chart[11], a, b);
				system(mosquitto_cmd);

				//publish temp_c,a to test.mosquitto.org
				sprintf(mosquitto_cmd, "mosquitto_pub -h test.mosquitto.org"
					" -t smartsolar/temp -r -m \"%f %f\"", temp_c, a);
				system(mosquitto_cmd);
				i++;
				i = i % 12;
			}
			min_b15=minute;

			//every min add to output file
	    	if (min_b!=minute) {
                min_b = minute;
                hours = local->tm_hour;
                day = local->tm_mday;        	// get day of month (1 to 31)
                month = local->tm_mon + 1;   	// get month of year (0 to 11)
                year = local->tm_year + 1900;	// get year since 1900
                sprintf(file_name, "/home/pi/Documents/%02d-%02d-%d-temp.dat", day, month, year);
                if (fp = fopen(file_name, "a")) {
                    fprintf(fp, "%02d:%02d:%02d, %f\n", hours, minute, sec, temp_c);
                    fclose(fp);
                }
			}
		}
		sleep(2); // wait 2 seconds
	}
	return 0;
}
