/*
 ============================================================================
 Name        : Vehicle_ctrl_system.c
 Author      : Taha Mohamed
 Version     :
 Copyright   : Your copyright notice
 Description : vehicle control system
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
/*global variable needed for the program to be saved and changed in all code scopes*/
int ch;
int vehicle_speed;
char vehicle_light;
float temperature_room;
float engine_temp;
int engine_temp_controller_state;
int AC = FALSE;
int ENGINE = FALSE;

/*functions prototypes*/
void engine_menu(int*);
void turn_on_engine();
void input(int*);
void display();
void traffic();
void temperature();
void engine();

/*main function*/
int main(void) {
	/*to execute printf immediately*/
	setbuf(stdout, NULL);
	/*set global variables to initial values*/
	vehicle_speed = 60;
	temperature_room = 25;
	engine_temp = 120;
	input(&ch);
	/*looping till the user quit the system by himself*/

	while (1) {

		switch (ch) {
		case 1:
			printf("you choose to turn on vehicle\n");
			turn_on_engine(&ch);

			break;
		case 2:
			printf("it's already off\n");
			printf("you choose to turn off vehicle\n");
			input(&ch);
			break;
		case 3:

			printf("you choose to quit the system\n");

			return 0;

		}
	}

	return 0;
}

/*first menu to be shown to the user */
void input(int *c) {
	printf("<-----------Vehicle Control System--------->\n\n\n");
	printf("1.Turn on vehicle\n");
	printf("2.Turn off vehicle\n");
	printf("3.quit the system\n\n");
	printf("please enter your choice (1 or 2 or 3)\n");
	do {

		scanf("%d", c);
	} while (*c != 1 && *c != 2 && *c != 3);

}
/*second menu will be shown to user when he start engine*/
void engine_menu(int *ch2) {
	printf("  <===sensors_set_menu===>  \n\n");

	printf("1.turn off engine\n");
	printf("2.set the traffic light color\n");
	printf("3.set the room temperature\n");
	printf("4.set the engine temperature\n");
	printf("please enter your choice (1 or 2 or 3 or 4)\n");
	do {
		scanf("%d", ch2);
	} while (*ch2 != 1 && *ch2 != 2 && *ch2 != 3 && *ch2 != 4);
}

/*if user choose to start engine we will call this function*/
void turn_on_engine() {
	int ch2;
	ENGINE = TRUE;
	int *x = &ch;
	engine_menu(&ch2);
	while (1) {
		switch (ch2) {
		case 1:
			ENGINE=FALSE;
			display();
			*x = 2;

			return;
		case 2:
			traffic();
			display();
			engine_menu(&ch2);
			break;
		case 3:
			temperature();
			display();
			engine_menu(&ch2);
			break;
		case 4:
			engine();
			display();
			engine_menu(&ch2);
			break;
		}
	}
}

/*display function for showing state of AC and engine and room and engine temperature and vehicle speed*/
void display() {
	if (vehicle_speed == 30) {
		if (AC == 0) {
			AC = 1;

		}
		temperature_room = temperature_room * (1.25) + 1;
		if (engine_temp_controller_state == FALSE) {
			engine_temp_controller_state = TRUE;

		}
		engine_temp = engine_temp * (1.25) + 1;
	}

	printf("---------Vehicle Current State---------\n\n\n");
	if (ENGINE == TRUE) {
		printf("the engine state is [ON]\n");
	} else {
		printf("the engine state is [OFF]\n");
	}
	if (AC == TRUE) {
		printf("the AC is [ON]\n");
	} else {
		printf("the AC is [OFF]\n");
	}
	printf("Vehicle speed is [%d]\n", vehicle_speed);
	printf("Room temperature is [%f]\n", temperature_room);
	if(engine_temp_controller_state == TRUE){
	printf("Engine temperature controller state is [ON]\n");
	}
	else{
		printf("Engine temperature controller state is [OFF]\n");
	}
	printf("Engine temperature is [%f]\n\n\n", engine_temp);

}

/*function to set vehicle speed by user choose one character*/
void traffic() {
	printf(
			"please enter character to set vehicle speed\nG for 100\nO for 30\nR for 0\n");
	do {

		scanf("%c", &vehicle_light);
	} while (vehicle_light != 'G' && vehicle_light != 'O'
			&& vehicle_light != 'R');
	if (vehicle_light == 'G') {
		vehicle_speed = 100;
	} else if (vehicle_light == 'O') {
		vehicle_speed = 30;

	} else if (vehicle_light == 'R') {
		vehicle_speed = 0;

	}
}

/*function to get temperature from user as sensor read*/
void temperature() {
	printf("please enter sensor read to set room temperature\n");
	do {

		scanf("%f", &temperature_room);
	} while (temperature_room < 0 || temperature_room > 100);

	if (temperature_room <= 10 || temperature_room > 30) {
		AC = 1;
		temperature_room = 20;
	} else {
		AC = 0;
		//temperature_room=0;
		printf("the AC turned off");
	}
}
/*function to get engine temperature from user as sensor read*/

void engine() {

	printf("please enter sensor read to set engine temperature\n");

	scanf("%f", &engine_temp);

	if (engine_temp < 100 || engine_temp > 150) {
		engine_temp_controller_state=TRUE;
		engine_temp = 125;
	} else {
		engine_temp_controller_state=FALSE;
		printf("engine turned off");
	}

}
