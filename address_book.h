#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#define DEFAULT_FILE				"address_book.csv"

/* Length of a contact name  */
#define NAME_LEN					32
/* Max number of phone numbers*/
#define MAX_PHONE_NUMBERS			5
/* Length of a phone number */
#define NUMBER_LEN					32
/* Max number of email addresses */
#define MAX_EMAILS					5
/* Length of an email address */
#define EMAIL_ID_LEN				32

#define MAX_ROW_CHAR 				1 + NAME_LEN + (MAX_PHONE_NUMBERS * NUMBER_LEN) + (MAX_EMAILS * EMAIL_ID_LEN)
#define MAX_INPUT_LENGTH			255

#define FIELD_DELIMITER				","
#define NEXT_ENTRY					"\n"

typedef int bool_t;

typedef enum 
{
	e_add,
	e_search,
	e_edit,
	e_delete,
	e_list,
} Modes;

typedef enum 
{
	e_first_opt,
	e_second_opt,
	e_third_opt,
	e_fourth_opt,
	e_fifth_opt,
	e_sixth_opt,
	e_no_opt = '\n' -'0',
} MenuOptions;

typedef enum
{
	e_fail = -10,
	e_back,
	e_success,
	e_no_match,
	e_new_line,
} Status;

typedef enum 
{
	e_exit,
	e_add_contact,
	e_search_contact,
	e_edit_contact,
	e_delete_contact,
	e_list_contacts,
	e_save
} MenuFeatures;

typedef struct
{
	char name[NAME_LEN];
	char phone_numbers[MAX_PHONE_NUMBERS][NUMBER_LEN];
	char email_addresses[MAX_EMAILS][EMAIL_ID_LEN];
	int si_no;
} ContactInfo;

typedef struct
{
	FILE *fp;
	ContactInfo *list;
	int count;	
} AddressBook;

#endif
