#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

void servoMotorControl(int gpio)
{
		pinMode(gpio,OUTPUT);
		softPwmCreate(gpio,0,200);

		for(;;){
				softPwmWrite(gpio,25);
				delay(800);
				softPwmWrite(gpio,5);
				delay(800);
		};

		softPwmWrite(gpio, 0);
}

int main(int argc, char **argv)
{
		int gno = atoi(argv[1]);
		wiringPiSetup();
		servoMotorControl(gno);
		return 0;
}
