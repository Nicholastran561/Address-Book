#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

void to_lowercase(char *str)
{
	while (*str)
	{
		*str = tolower((unsigned char)*str);
		str++;
	}
}

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


    if (address_book->count == 0)
    {
        printf("\nNo contacts available.\n");
        return e_success;
    }

    printf("\n===============================================================================================================");
    printf("\n: S.No : Name                             : Phone No                       : Email ID                         :");
    printf("\n===============================================================================================================");

    if (mode == e_list)
    {
        for (int i = 0; i < address_book->count; i++)
        {
            ContactInfo tempUser = address_book->list[i];

            printf("\n: %-4d : %-32s : %-30s : %-32s :", tempUser.si_no, tempUser.name, tempUser.phone_numbers[0], tempUser.email_addresses[0]);

            for (int j = 1; j < MAX_PHONE_NUMBERS || j < MAX_EMAILS; j++)
            {
                if (strlen(tempUser.phone_numbers[j]) > 0 || strlen(tempUser.email_addresses[j]) > 0)
                {
                    printf("\n: %-4s : %-32s : %-30s : %-32s :", "", "", (strlen(tempUser.phone_numbers[j]) > 0) ? tempUser.phone_numbers[j] : "", (strlen(tempUser.email_addresses[j]) > 0) ? tempUser.email_addresses[j] : "");
                }
            }

            printf("\n===============================================================================================================");
        }
    }

    char input[MAX_INPUT_LENGTH];
    do
    {
        printf("\nPress [q] to continue: ");
        scanf("%s", input);
    } while (strcmp(input, "q") != 0);

    return e_success;

}

void menu_header(const char *str)
{
	fflush(stdout);

	//If your on windows use "cls"
	//If your on linux/mac use "clear"
	//system("clear");
	#ifdef _WIN32
	system("cls");
	#else
	system("clear");
	#endif

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

bool checkForBadChars(const char str[]) {
	int i = 0;

	if (strstr(str, ",") != NULL) return false;

	return true;
}

Status getContactInfo(ContactInfo *wList, const int *_si_no) {
	int amountOfNumbers;
	char numbs[10];
	char eNumbs[10];

	char *ptr;
	char *ePtr;

	printf("\n\n### Adding data to contact list. ###");

	//fflush(stdin);
	do
	{
		printf("\nWhat is the contact's name?: ");
		scanf("%s", wList->name);//, sizeof(wList->name), stdin);
	} while (!checkForBadChars(wList->name));
	
	//scanf("%s", wList->name);
	printf("%s", wList->name);

	//Phone numbers
	do
	{
		printf("\nHow many phone numbers does the contact have? (Max numbers: %i): ", MAX_PHONE_NUMBERS);
		scanf("%s", numbs);//fgets(numbs, sizeof(numbs), stdin);
		amountOfNumbers = atoi(numbs);

		if (amountOfNumbers <= 0) amountOfNumbers = MAX_PHONE_NUMBERS;

		if (amountOfNumbers >= MAX_PHONE_NUMBERS) printf("\nYou entered too much or a non integer value! Retry.\n");
	} while (amountOfNumbers >= MAX_PHONE_NUMBERS);

	int i = 0;
	for (; i < MAX_PHONE_NUMBERS; ++i)
	{
		if (i >= amountOfNumbers)
		{
			wList->phone_numbers[i][0] = ' ';
			wList->phone_numbers[i][1] = '\0';
			continue;
		}

		printf("\nEnter number %i of %s's numbers.: ", i + 1, wList->name);
		//fgets(wList->phone_numbers[i], sizeof(wList->phone_numbers[i]), stdin);
		scanf("%s", wList->phone_numbers[i]);
	}

	//Email addresses
	do
	{
		printf("\nHow many email addresses does the contact have? (Max numbers: %i): ", MAX_EMAILS);
		scanf("%s", eNumbs);
		amountOfNumbers = atoi(eNumbs);
		//fgets(eNumbs, sizeof(eNumbs), stdin);
		//amountOfNumbers = strtol(eNumbs, &ePtr, 10);
		if (amountOfNumbers <= 0) amountOfNumbers = MAX_EMAILS;

		if (amountOfNumbers >= MAX_EMAILS) printf("\nYou entered too much or a non integer value! Retry.\n");
	} while (amountOfNumbers > MAX_EMAILS);

	i = 0;
	for (; i < MAX_EMAILS; ++i)
	{
		if (i >= amountOfNumbers)
		{
			wList->email_addresses[i][0] = ' ';
			wList->email_addresses[i][1] = '\0';
			continue;
		}

		printf("\nEnter number %i of %s's emails.: ", i + 1, wList->name);
		//fgets(wList->email_addresses[i], sizeof(wList->email_addresses[i]), stdin);
		scanf("%s", wList->email_addresses[i]);
	}

	wList->si_no = *_si_no;

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	menu_header("Add Contacts:\n");
	
	printf("\nFirst allocating memory.");

	int lCount = address_book->count;
	int cCount = lCount; //TO compare;
	ContactInfo *nList = address_book->list; //Not sure if malloc fails it will overwrite the data.
	ContactInfo *nPointer;

	lCount += 1;
	address_book->count = lCount;

	//If there are no contacts with in the book at this moment.
	if (cCount == 0)
	{
		//Allocate memory within the list.
		nList = (ContactInfo*) malloc(lCount * sizeof(ContactInfo));

		if (nList == NULL) //Failed
		{
			printf("\nFailed to add the first person to contacts. Not enough memory.\n");
			return e_fail;
		}
		else //Success
		{
			nPointer = (nList + cCount);
			getContactInfo(nPointer, &lCount);
		}
	}
	else
	{
		nList = (ContactInfo*) realloc(nList, lCount * sizeof(ContactInfo)); //Reallocate enough memory in storage;

		if (nList == NULL)
		{
			printf("\nFailed to add the person to contacts. Not enough memory.\n");
			return e_fail;
		}
		else //Add
		{
			nPointer = (nList + cCount);
			getContactInfo(nPointer, &lCount);
		}
	}

	address_book->list = nList;
	
	/*
	char input[MAX_INPUT_LENGTH];
	while(strcmp(input, "q") != 0)
	{
		printf("\nPress: [q] to Cancel: ");
		scanf("%s", input);
		to_lowercase(input);
	}
	*/
	return e_success;
}
Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	if (address_book->count == 0)
    {
        printf("\nNo contacts available to search.\n");
        return e_success;
    }

    ContactInfo *results[address_book->count];
    int result_count = 0;

    for (int i = 0; i < address_book->count; i++)
    {
        ContactInfo *contact = &address_book->list[i];
        int match_found = 0;

        if ((field == 1 || field == 0) && (strcasecmp(contact->name, str) == 0 || strstr(contact->name, str) != NULL))
        {
            match_found = 1;
        }

        for (int j = 0; j < MAX_PHONE_NUMBERS && !match_found; j++)
        {
            if ((field == 2 || field == 0) && strlen(contact->phone_numbers[j]) > 0 && strstr(contact->phone_numbers[j], str) != NULL)
            {
                match_found = 1;
            }
        }

        for (int j = 0; j < MAX_EMAILS && !match_found; j++)
        {
            if ((field == 3 || field == 0) && strlen(contact->email_addresses[j]) > 0 && strstr(contact->email_addresses[j], str) != NULL)
            {
                match_found = 1;
            }
        }

		if (contact->si_no == atoi(str))
		{
			match_found = 1;
		}

        if (match_found)
        {
            results[result_count++] = contact;
        }
    }

    if (result_count == 0)
    {
        printf("\nNo matching contacts found.\n");
        return e_success;
    }

	menu_header("Search By Contact:\n");

    printf("\n===============================================================================================================");
    printf("\n: S.No : Name                             : Phone No                       : Email ID                         :");
    printf("\n===============================================================================================================");

    for (int i = 0; i < result_count; i++)
    {
        ContactInfo *contact = results[i];
        printf("\n: %-4d : %-32s : %-30s : %-32s :",
                contact->si_no, contact->name, contact->phone_numbers[0], contact->email_addresses[0]);

        for (int j = 1; j < MAX_PHONE_NUMBERS; j++)
        {
            if (strlen(contact->phone_numbers[j]) > 0 || strlen(contact->email_addresses[j]) > 0)
            {
                printf("\n: %-4s : %-32s : %-30s : %-32s :", "", "", contact->phone_numbers[j], contact->email_addresses[j]);
            }
        }
        printf("\n===============================================================================================================");
    }

	return e_success;
}

Status search_contact(AddressBook *address_book)
{
	menu_header("Search Contacts:\n");

    if (address_book->count == 0)
    {
        printf("\nNo contacts available to search.\n");
        return e_success;
    }

    int search_option;
    char search_term[MAX_INPUT_LENGTH];

    printf("\nSearch by: \n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("4. Serial No\n");
    printf("Enter option (1-4): ");
    scanf("%d", &search_option);
    getchar();

    if (search_option < 1 || search_option > 4)
    {
        printf("\nInvalid option!\n");
        return e_success;
    }
	else if (search_option == 1)
	{
			printf("\nEnter the Name: ");
	}
	else if (search_option == 2)
	{
		printf("\nEnter the Phone Number: ");
	}
	else if (search_option == 3)
	{
		printf("\nEnter the Email: ");
	}
	else
	{
		printf("\nEnter the Serial No: ");
	}

    fgets(search_term, MAX_INPUT_LENGTH, stdin);
    search_term[strcspn(search_term, "\n")] = '\0';

    search(search_term, address_book, 0, search_option, "", e_list);

    char input[MAX_INPUT_LENGTH];
    do
    {
        printf("\nPress [q] to return to the main menu: ");
        scanf("%s", input);
    } while (strcmp(input, "q") != 0);

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
			printf("Enter the Name: ");
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
			char tempEmail[EMAIL_ID_LEN];
			printf("Enter the Phone Number: ");
			scanf("%s", tempEmail);
			for(int i = 0; i < address_book->count; i++)
			{
				ContactInfo currentContact = address_book->list[i];
				for (int j = 0; j < MAX_EMAILS; j++)
				{
					if(strcmp(currentContact.email_addresses[j], tempEmail) == 0)
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
		else if (strcmp(input, "4") == 0)
		{
			char tempSiNo[NUMBER_LEN];
			printf("Enter the Serial Number: ");
			scanf("%s", tempSiNo);
			int tempSN = atoi(tempSiNo);
			for(int i = 0; i < address_book->count; i++)
			{
				ContactInfo currentContact = address_book->list[i];
				if(currentContact.si_no == tempSN)
				{
					if (tempBook->count <= address_book->count)
					{
						tempBook->list[tempBook->count] = currentContact;
						tempBook->count++;
					}
				}
			}
		}
		if (tempBook->count > 0)
			{
				list_contacts(tempBook, "", 0, "", e_list);

				strcpy(input, "0");
				printf("Select a Serial Number (S. No) to Edit [Press 0 to Exit]: ");
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
				if (editContact.si_no == tempSiNo)
				{
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
					printf("Invalid Serial Number\n\n");
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
    system("cls");
    char input[NAME_LEN];
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }

    while (1)
    {
        printf("\nEnter name, phone, or email to search for deleting (Q to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 1 && (input[0] == 'Q' || input[0] == 'q'))
        {
            break;
        }

		printf("Searching for: [%s]\n", input);

        system("cls");
        printf("#######  Search results  #######\n");
        printf("===============================================================================================\n");
        printf(": %-5s\t: %-15s: %-20s: %-30s\n", "S.No", "Name", "Phone", "Email");
        printf("===============================================================================================\n");

        for (int i = 0; i < address_book->count; i++)
        {
            ContactInfo *contact = &address_book->list[i];

            if (strstr(contact->name, input) ||
                strstr(contact->phone_numbers[0], input) ||
                strstr(contact->email_addresses[0], input))
            {
                printf(": %-5d\t: %-15s: %-20s: %-30s\n",
                    contact->si_no,
                    contact->name,
                    contact->phone_numbers[0],
                    contact->email_addresses[0]);
            }
        }

        printf("\nEnter S.No of contact to delete. (Q to quit): ");
        fgets(input, sizeof(input), stdin);
        strtok(input, "\n");
        if (strlen(input) == 1 && (input[0] == 'Q' || input[0] == 'q'))
        {
            break;
        }

        int sno = atoi(input);
        ContactInfo *contact = &address_book->list[sno - 1];

        for (int i = sno - 1; i < address_book->count - 1; i++)
        {
            address_book->list[i] = address_book->list[i + 1];
            address_book->list[i].si_no = i + 1;
        }
        address_book->count--;
        printf("Contact deleted successfully.\n");
    }
    return e_success;
}