#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

extern AddressBook *tempAddressBook;
extern ContactInfo *tempContactInfo;

int get_option(int type, const char *msg)
{
	char option[MAX_INPUT_LENGTH];
	char *ptr;
	int result = 0;
	printf("%s", msg);
	if (type != NONE) {
		scanf("%s", option);
	}
	if (type == NUM) {
    	result = atoi(option);
		printf("%d", result);
	}
	if (type == CHAR) {
    	result = strtol(option, &ptr, 10);
		printf("%d\n", result);
		printf("%s\n", ptr);
		return *ptr;
	} 
	return result;
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	//FIX THIS TO LOOK LIKE THE PDF LATER ON
	printf("\nYou listed contacts");
	for (int i = 0; i < tempAddressBook->count; i++) {   
		ContactInfo *ptr = tempAddressBook->list;
		printf("\n %d, %s", (i+ptr)->si_no, (i+ptr)->name);
		for (int j = 0; j < MAX_PHONE_NUMBERS; j++) {
			printf(",%s", (i+ptr)->phone_numbers[j]);
		}
		for (int j = 0; j < MAX_EMAILS; j++) {
			printf(",%s", (i+ptr)->email_addresses[j]);
		}
	}

	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "q") != 0) 
	{
		printf("\nPress: [q] to Cancel: ");
		scanf("%s", input);
	}
	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	//If your on windows use "cls" 
	//If your on linux/mac use "clear"
	//system("clear");
	system("cls");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				list_contacts(address_book, "", 0, "", e_list);
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	printf("\nYou added contacts");
	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "q") != 0) 
	{
		printf("\nPress: [q] to Cancel: ");
		scanf("%s", input);
	}
	return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	return e_success;
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	/* Add the functionality for adding contacts here */
	printf("\nYou searched contacts");
	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "q") != 0) 
	{
		printf("\nPress: [q] to Cancel: ");
		scanf("%s", input);
	}
	return e_success;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	/* Add the functionality for adding contacts here */
	printf("\nYou edited contacts");
	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "q") != 0) 
	{
		printf("\nPress: [q] to Cancel: ");
		scanf("%s", input);
	}
	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	/* Add the functionality for adding contacts here */
	printf("\nYou deleted contacts");
	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "q") != 0) 
	{
		printf("\nPress: [q] to Cancel: ");
		scanf("%s", input);
	}
	return e_success;
}
