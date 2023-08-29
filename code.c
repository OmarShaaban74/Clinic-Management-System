/*
 ============================================================================
 Name        : Clinic_system.c
 Author      : Omar shaaban
 Version     : 28/8/2023
 Copyright   : Your copyright notice
 Description : Clinic System
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum reserved {
	not_reserved, reseved
};
unsigned short slot[5] = { not_reserved };/*initially all slots are not reserved*/

#define SIZE 50

typedef struct patient patient;
struct patient {
	char name[SIZE];
	unsigned int age;
	char gender;
	unsigned int id;
	patient *next;
	short reservation_slot;
};
patient *head = NULL; /*Head of linked list*/
patient *current = NULL; /*ptr that move over all linked list nodes*/
/*Functions Prototypes*/
void Begining_ask(void);
void display_begining_list(void);
void admin_mode(void);
void add(void);
void edit(void);
void reserve(void);
void cancel(void);
void user_mode(void);
void view_information(void);
void print_today_reservations(void);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	Begining_ask();
	return 0;
}
void Begining_ask(void) {
	int flag;
	char first_user_input;
	do{
	flag=1;
	printf("a. Admin Mode\n");
	printf("b. User Mode\n");
	scanf(" %c", &first_user_input);
	switch (first_user_input) {
	case 'a':
	case 'A':
		admin_mode();
		break;
	case 'b':
	case 'B':
		user_mode();
		break;
	default:
		printf("Wrong input!!, please try again\n");
		flag=0;
	}
	}while(flag==0);
}

void admin_mode(void) {
	unsigned int password;
	short wrong_temps = 0;
	printf("Enter The Password\n");
	while(wrong_temps!=4) {
		scanf("%d", &password);
		if(password==1234){
			break;
		}
		else{
		wrong_temps++;
		if (wrong_temps == 3) {
			printf("You Entered wrong passwored 3 times!!!\nThe system will shutdown\n");
			return;
		}
		printf("Incorrect password, please try again\n");
		}
	}
	printf("Login Successfully\n\n");
	display_begining_list();

}
void display_begining_list(void) {
	char chosen_feature;
	int flag;
	do{
		flag=1;
	printf("a. Add new patient record\n");
	printf("b. Edit patient record\n");
	printf("c. Reserve a slot with the doctor\n");
	printf("d. Cancel reservation\n");
	printf("e. Main menu\n");
	printf("f. Exit\n");
	scanf(" %c", &chosen_feature);
	switch (chosen_feature) {
	case 'a':
	case 'A':
		add();
		break;
	case 'b':
	case 'B':
		edit();
		break;
	case 'c':
	case 'C':
		reserve();
		break;
	case 'd':
	case 'D':
		cancel();
		break;
	case'e':
	case'E':
		Begining_ask();
		break;
	case'f':
	case'F':
		printf("Quit the system\n");
		exit(1);
	default:
		printf("Wrong input!! , please try again\n");
		flag=0;
	}
	}while(flag==0);
}
void add(void) {
	int flag;
	unsigned int temp_id;
	patient *link=NULL;
	do{
	flag=1;
	link = (patient*) malloc(sizeof(patient));/*To add new node at linked list*/
	if (link == NULL) {
		printf("Memory allocation failed\n");
		return;
	}
	link->reservation_slot=0;
	printf("Enter patient Name:\n");
	scanf(" %[^\n]%*c", link->name);
	printf("Enter patient age:\n");
	scanf(" %u", &(link->age));
	printf("Enter patient gender (M) or (F):\n");
	scanf(" %c", &(link->gender));
	printf("Enter patient unique ID:\n\n");
	scanf("%u", &temp_id);
	current = head;
	while (current != NULL) {/*Find the input id is exist or not*/
		if ((current->id) == temp_id) {
			printf("This ID is already exists,please try again\n");
			flag=0;
			break;
		}
		current = current->next;
	}
	}while(flag==0);
	link->id = temp_id;
	link->next = head;
	head = link;
	printf("Patient added successfully\n\n");
	display_begining_list();

}

void edit(void) {
	unsigned int temp_id;
	int flag;
	do{
		flag=1;

	printf("Enter patinet ID to be edited\n");
	scanf("%u", &temp_id);
	current = head;
	while (current != NULL) {
		if (current->id == temp_id) {
			printf("ID is Found!\n");
			printf("You can edit information now\n\n");
			printf("Edit patient name:\n");
			scanf(" %[^\n]%*c", current->name);
			printf("Edit patient age:\n");
			scanf(" %u", &(current->age));
			printf("Edit patient gender (M) or (F):\n");
			scanf(" %c", &(current->gender));
			printf("Edited successfully\n");
			display_begining_list();
		}

		else {
			current = current->next;
		}
	}
	if(current==NULL){
	printf("Error! ID not found , please try again\n");
		flag=0;
	}
}while(flag==0);
}
void reserve(void) {
	unsigned int chosen_slot;
	unsigned int temp_id;
		int flag;
		do{
			flag=1;

	printf("Available slots are:\n\n");
	if (slot[0] == not_reserved)/*To control if the slot available or not */
		printf("Slot 1 From 2:00 pm To 2:30 pm\n");

	if (slot[1] == not_reserved)
		printf("Slot 2 From 2:30 pm To 3:00 pm\n");

	if (slot[2] == not_reserved)
		printf("Slot 3 From 3:00 pm To 3:30 pm\n");

	if (slot[3] == not_reserved)
		printf("Slot 4 From 4:00 pm To 4:30 pm\n");

	if (slot[4] == not_reserved)
		printf("Slot 5 From 5:00 pm To 5:30 pm\n");

	printf("Enter patient ID to reserve a slot:\n");

	scanf("%u", &temp_id);
	current = head;
	while (current != NULL) {
		if (current->id == temp_id) {
			printf("Enter a slot number to be reserved:\n");
			scanf(" %u", &chosen_slot);
			switch (chosen_slot) {
			case 1:
				if(!(current->reservation_slot)){
				slot[0] = reseved;
				current->reservation_slot = 1;
				printf("slot reserved successfully\n");
				display_begining_list();}
				else{
					printf("Error! This patient already reserved slot %d \n",current->reservation_slot);
					display_begining_list();
				}
				break;
			case 2:
				if(!(current->reservation_slot)){
				slot[1] = reseved;
				current->reservation_slot = 2;
				printf("slot reserved successfully\n");
				display_begining_list();}
				else{
					printf("Error! This patient already reserved slot %d \n",current->reservation_slot);
						display_begining_list();
				}
				break;
			case 3:
				if(!(current->reservation_slot)){
				slot[2] = reseved;
				current->reservation_slot = 3;
				printf("slot reserved successfully\n");
				display_begining_list();}
				else {
					printf("Error! This patient already reserved slot %d \n",current->reservation_slot);
					display_begining_list();
				}
				break;
			case 4:
				if(!(current->reservation_slot)){
				slot[3] = reseved;
				current->reservation_slot = 4;
				printf("slot reserved successfully\n");
				display_begining_list();}
				else {
					printf("Error! This patient already reserved slot %d \n",current->reservation_slot);
					display_begining_list();
				}
				break;
			case 5:
				if(!(current->reservation_slot)){
				slot[4] = reseved;
				current->reservation_slot = 5;
				printf("slot reserved successfully\n");
				display_begining_list();}
			else {
				printf("Error! This patient already reserved slot %d \n",current->reservation_slot);
				display_begining_list();
			}
				break;

			}

		}
		current = current->next;
	}
	if (current == NULL) {
		printf("Error! ID not found, please try again\n");
		flag=0;
	}
		}while(flag==0);
}

void cancel(void) {
	unsigned int temp_id;
	int flag;
	do{
		flag=1;

	printf("Enter patient ID to cancel reservation:\n");

	scanf(" %u", &temp_id);
	current = head;
	while (current != NULL) {
		if (current->id == temp_id) {

			slot[current->reservation_slot - 1] = not_reserved;
			current->reservation_slot = 0;
			printf("cancelled successfully\n");
			display_begining_list();

		}
		current = current->next;
	}
	if (current == NULL) {
		printf("Error! ID not found, Please try again\n");
		flag=0;
	}
	}while(flag==0);
}

void user_mode(void) {
	char user_input;
	int flag;
	do{
		flag=1;

	printf("a. View patient record\n");
	printf("b. View today's reservations\n");
	scanf(" %c", &user_input);
	switch (user_input) {
	case 'a':
	case 'A':
		view_information();
		break;
	case 'b':
	case 'B':
		print_today_reservations();
		break;
	default:
		printf("Wrong input!!, please try again\n");
		flag=0;

	}
	}while(flag==0);
}
void view_information(void){
	unsigned int temp_id;
	int flag;
	do{
		flag=1;

	printf("Enter patient id to view his/her information:\n");

			scanf(" %u", &temp_id);
			current = head;
			while (current != NULL) {
				if (current->id == temp_id) {

					printf("Patient Name: %s\n", current->name);
					printf("Patient age: %u\n", current->age);
					printf("Patient gender: %c\n", current->gender);
					if(current->reservation_slot){
						printf("Reserved slot no. %d\n",current->reservation_slot);
					}
					else{
						printf("Not reserved yet\n");
					}
					display_begining_list();
				}
				current = current->next;
			}
			if (current == NULL) {
				printf("Error! ID not found, please try again\n");
				flag=0;
			}
	}while(flag==0);
	}
void print_today_reservations(void){
	int i;

	for (i = 1; i <= 5; i++) {
		current = head;
		while (current != NULL) {
			if (current->reservation_slot==i) {
				printf("Slot %d reserved by patient with id %u\n", i,current->id);
				break;

			}
			else {
				current=current->next;

			}


		}

		if(current==NULL){
			printf("Slot %d Not reserved\n", i);
		}

	}
	display_begining_list();
return;
}

