#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"


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

	menu_header("List Result:\n");
	printf("\n===============================================================================================================");
	printf("\n: S.No : Name                             : Phone No                       : Email ID                         :");
	if (mode == e_list)
	{
		char buffer[NAME_LEN] = " ";
		for (int i = 0; i < address_book->count; i++)
		{
			ContactInfo tempUser = address_book->list[i];
			printf("\n===============================================================================================================");
			printf("\n: %-4d : %-32s : %-30s : %-32s :", tempUser.si_no, tempUser.name, tempUser.phone_numbers, tempUser.email_addresses);
			for (int j = 1; j < MAX_PHONE_NUMBERS; j++)
			{
				printf("\n: %-4s : %-32s : %-30s : %-32s :", buffer, buffer, tempUser.phone_numbers[j], tempUser.email_addresses[j]);
			}
		}
		printf("\n===============================================================================================================");
	}

	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "q") != 0) 
	{
		printf("\nPress: [q] to Continue: ");
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
	menu_header("Add Contacts:\n");
	/* Add the functionality for adding contacts here */
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
	menu_header("Search Contacts:\n");
	/* Add the functionality for search contacts here */
	/* Add the functionality for adding contacts here */
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
	menu_header("Search Contact to Edit by:\n");
	/* Add the functionality for edit contacts here */
	/* Add the functionality for adding contacts here */
	

	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "0") != 0) 
	{
		strcpy(input, "");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone Number\n");
		printf("3. Email Address\n");
		printf("4. Serial Number\n");
		printf("\nPlease select an option: ");
		scanf("%s", input);
		
		AddressBook *tempBook = (AddressBook *)malloc(sizeof(AddressBook));
		tempBook->list = (ContactInfo *)malloc(sizeof(ContactInfo) * address_book->count);
		tempBook->count = 0;
		//char tempName[NAME_LEN];
		if (strcmp(input, "1") == 0)
		{
			char tempName[NAME_LEN];
			printf("Enter the name: ");
			scanf("%s", tempName);
			for(int i = 0; i < address_book->count; i++)
			{
				ContactInfo currentContact = address_book->list[i]; 
				if(strcmp(currentContact.name, tempName) == 0)
				{
					if (tempBook->count <= address_book->count)
					{
						tempBook->list[tempBook->count] = currentContact;
						tempBook->count++;
					}
					
				}
			}
			
		}
		else if (strcmp(input, "2") == 0)
		{
			char tempNumber[NUMBER_LEN];
			printf("Enter the Phone Number: ");
			scanf("%s", tempNumber);
			for(int i = 0; i < address_book->count; i++)
			{
				ContactInfo currentContact = address_book->list[i]; 
				for (int j = 0; j < MAX_PHONE_NUMBERS; j++)
				{
					if(strcmp(currentContact.phone_numbers[j], tempNumber) == 0)
					{
						if (tempBook->count <= address_book->count)
						{
							tempBook->list[tempBook->count] = currentContact;
							tempBook->count++;
						}
						
					}
				}
			}
		}
		else if (strcmp(input, "3") == 0)
		{

		}
		else if (strcmp(input, "4") == 0)
		{

		}
		if (tempBook->count > 0)
			{
				list_contacts(tempBook, "", 0, "", e_list);

				strcpy(input, "0");
				printf("Select a Serial Number (S. No) to Edit: ");
				scanf("%s", input);
				int tempSiNo = atoi(input);
				
				ContactInfo editContact;
				for(int i = 0; i <= tempBook->count; i++)
				{
					ContactInfo currentContact = tempBook->list[i];
					if (tempSiNo == currentContact.si_no)
					{
						editContact = currentContact;
					}
				}
				while(strcmp(input, "0") != 0)
				{
					menu_header("Edit Contact:\n");
					strcpy(input, "");
					printf("0. Back\n");
					printf("1. Name       : %s\n", editContact.name);
					printf("2. Phone No 1 : %s\n", editContact.phone_numbers[0]);
					for(int i = 1; i < MAX_PHONE_NUMBERS; i++)
					{
						if(strcmp(editContact.phone_numbers[i], "\0") != 0)
						{
							printf("            %d : %s\n", i + 1, editContact.phone_numbers[i]);
						}
					}
					printf("3. Email ID 1 : %s\n", editContact.email_addresses[0]);
					for(int i = 1; i < MAX_EMAILS; i++)
					{
						if(strcmp(editContact.email_addresses[i], "\0") != 0)
						{
							printf("            %d : %s\n", i + 1, editContact.email_addresses[i]);
						}
					}
					printf("\nPlease select an option: ");
					char editChoice[MAX_INPUT_LENGTH];
					scanf("%s", editChoice);

					if (strcmp(editChoice, "0") == 0)
					{
						strcpy(input, editChoice);
					}
					else if (strcmp(editChoice, "1") == 0)
					{
						char newName[NAME_LEN];
						printf("Enter New Name: ");
						scanf("%s", newName);
						strcpy(editContact.name, newName);
					}
					else if (strcmp(editChoice, "2") == 0)
					{
						char newNumber[NUMBER_LEN];
						char phoneIndex[MAX_INPUT_LENGTH];
						printf("Enter Phone Number index to be changed [Max 5]: ");
						scanf("%s", phoneIndex);
						int pIndex = atoi(phoneIndex) - 1;
						printf("Enter Phone Number %s [Just enter removes the entry]: ", phoneIndex);
						scanf("%s", newNumber);
						strcpy(editContact.phone_numbers[pIndex], newNumber);
					}
					else if (strcmp(editChoice, "3") == 0)
					{
						char newEmail[EMAIL_ID_LEN];
						char emailIndex[MAX_INPUT_LENGTH];
						printf("Enter Email Address index to be changed [Max 5]: ");
						scanf("%s", emailIndex);
						int eIndex = atoi(emailIndex) - 1;
						printf("Enter Email Address %s [Just enter removes the entry]: ", emailIndex);
						scanf("%s", newEmail);
						strcpy(editContact.email_addresses[eIndex], newEmail);
					}
					address_book->list[editContact.si_no - 1] = editContact;
				}
			}
			else
			{
				printf("No such entry exists, try again:\n\n");
			}
	}
	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	menu_header("Delete Contacts:\n");
	/* Add the functionality for delete contacts here */
	/* Add the functionality for adding contacts here */
	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "q") != 0) 
	{
		printf("\nPress: [q] to Cancel: ");
		scanf("%s", input);
	}
	return e_success;
}
