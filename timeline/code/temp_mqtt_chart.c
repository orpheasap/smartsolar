#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define SIZE 1
#define NUMELEM 74

int main(int argc, char** argv)
{
    FILE* fp = NULL;
    char buff[100];
    char temp_raw[7];
    float temp_c, temp_chart[12] = { 0 };
    char mosquitto_cmd[1024];
    int min, sec, i, ii;
    // char temp_chart_s[256];
    time_t now;

    memset(buff, 0, sizeof(buff));
    memset(temp_raw, 0, sizeof(temp_raw));
    /*Enable Temp*/
    system("sudo modprobe w1-gpio");
    system("sudo modprobe w1-therm");

    for(;;) {

		fp = fopen("/sys/bus/w1/devices/28-01144eec7eaa/w1_slave", "r");

		if(NULL == fp) {
			printf("\n fopen Error!!!\n\n");

		} else if(SIZE * NUMELEM != fread(buff, SIZE, NUMELEM, fp)) {
			printf("\n fread() failed\n");
			fclose(fp);
		} else {
			fclose(fp);
			temp_raw[0] = buff[69];
			temp_raw[1] = buff[70];
			temp_raw[2] = buff[71];
			temp_raw[3] = buff[72];
			temp_raw[4] = buff[73];
			temp_raw[5] = buff[74];
			temp_c = atof(temp_raw) / 1000;
			//printf("\nTemp Is: %f DegC", temp_c);
			sprintf(mosquitto_cmd, "mosquitto_pub -t temp -m %f", temp_c);
			system(mosquitto_cmd);
			time(&now);
			struct tm* local = localtime(&now);
			min = local->tm_min;
			sec = local->tm_sec;
			//printf("Time is : %02d:%02d\n", min, sec);
			if((min==0 && sec<=2) || (min==15 && sec<=2) || (min==30 && sec<=2) || (min==45 && sec<=2)) {
				for(ii = 11; ii > 0; ii--) {
					temp_chart[ii] = temp_chart[ii - 1];
				}
				temp_chart[0] = temp_c;
				//printf("Time is : %02d:%02d %.2f %d\n", min, sec, temp_chart[0], i);
				sprintf(mosquitto_cmd, "mosquitto_pub -r -t temp_chart -m \"%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\"",
				temp_chart[0], temp_chart[1], temp_chart[2], temp_chart[3], temp_chart[4], temp_chart[5],
				temp_chart[6], temp_chart[7], temp_chart[8], temp_chart[9], temp_chart[10], temp_chart[11]);
				//printf(mosquitto_cmd);
				//printf("\n");
				system(mosquitto_cmd);
				i++;
				i = i % 12;
			}
		}
		sleep(2); // wait 2 seconds
	}
	return 0;
}
