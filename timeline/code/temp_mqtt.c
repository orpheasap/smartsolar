#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <mosquitto_plugin.h>

#define SIZE 1
#define NUMELEM 74

int main ()
{
	FILE *fp = NULL;
	char buff[100];
	char temp_raw[7];
	float temp_c;
	char mosquitto_cmd[256];
	
	memset(buff,0,sizeof(buff));
	memset(temp_raw,0,sizeof(temp_raw));
	/*Enable Temp*/
	system("sudo modprobe w1-gpio");
	system("sudo modprobe w1-therm");

	for(;;)
	{
		
		fp = fopen("/sys/bus/w1/devices/28-01144eec7eaa/w1_slave","r");

		if (NULL == fp)
		{
		printf("\n fopen Error!!!\n\n");
		return 1;
		}

		if(SIZE*NUMELEM != fread(buff,SIZE,NUMELEM,fp))
		{
		printf("\n fread() failed\n");
		return 1;
		}

		temp_raw[0] = buff[69];
		temp_raw[1] = buff[70];
		temp_raw[2] = buff[71];
		temp_raw[3] = buff[72];
		temp_raw[4] = buff[73];
		temp_raw[5] = buff[74];
		temp_c=atof(temp_raw)/1000;
		printf("\nTemp Is: %f DegC\n", temp_c); 
		
		sprintf(mosquitto_cmd, 
				"mosquitto_pub -t temp -m %f", temp_c);
				
		system(mosquitto_cmd);

	}
	return 0;
}
