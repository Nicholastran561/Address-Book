#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"


Status load_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	 */

	ret = access(DEFAULT_FILE, F_OK); // if ret = 0 a file exist otherwise ret = -1
	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 

		char row[MAX_ROW_CHAR];
		int num_rows = 0;

		address_book->fp = fopen(DEFAULT_FILE, "r");

		ContactInfo *tempContactInfo;
		tempContactInfo = (ContactInfo*) malloc(1 * sizeof(ContactInfo));

		address_book->list = tempContactInfo;
		address_book->count = 0;
		
		while (!feof(address_book->fp))
		{
			num_rows++;
			fgets(row, MAX_ROW_CHAR, (FILE*)address_book->fp);
			char *userDataToken;
			userDataToken = strtok (row, FIELD_DELIMITER);
			int index = 0;
			while (userDataToken != NULL)
			{
				index++;
				ContactInfo *currentContact = (address_book->count)+tempContactInfo;
				if (index == 1)
				{
					(currentContact->si_no = atoi(userDataToken));
				}
				if (index == 2)
				{
					strcpy(currentContact->name, userDataToken);
				}
				if (index >= 3 && index <= 7) //Indexes 3-7 are Phone Numebrs
				{
					strcpy(currentContact->phone_numbers[index - 3], userDataToken);
				}
				if (index >= 8 && index <= 12) //Indexes 8-12 are Emails
				{
					strcpy(currentContact->email_addresses[index - 8], userDataToken);
					if (index == 12)
					{
						address_book->count++;
					}
				}
				
				userDataToken = strtok(NULL, ",");
				tempContactInfo = (ContactInfo*) realloc(tempContactInfo, (num_rows + 1) * sizeof(ContactInfo));
				address_book->list = tempContactInfo;
			}
		}
		fclose(address_book->fp);
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w");
		fclose(address_book->fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 
	for (int i = 0; i < address_book->count; i++)
	{
		/*
		Each row in the .csv will look like "si_no,name,phones 1-5,emails 1-5"
		**Note** what I mean by "phones & emails 1-5" I am reffering to the numbers and emails seperated by commas
		*/
		ContactInfo *effectiveAddress = address_book->list + i;
		fprintf(address_book->fp, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\n",
			(effectiveAddress)->si_no,
			(effectiveAddress)->name, 
			(effectiveAddress)->phone_numbers[0],
			(effectiveAddress)->phone_numbers[1],
			(effectiveAddress)->phone_numbers[2],
			(effectiveAddress)->phone_numbers[3],
			(effectiveAddress)->phone_numbers[4],
			(effectiveAddress)->email_addresses[0],
			(effectiveAddress)->email_addresses[1],
			(effectiveAddress)->email_addresses[2],
			(effectiveAddress)->email_addresses[3],
			(effectiveAddress)->email_addresses[4]
		);
	}
	fclose(address_book->fp);

	return e_success;
}
