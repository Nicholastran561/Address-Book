#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

//gcc -o run address_book_fops.c address_book_menu.c main.c -I.
int main()
{
    AddressBook book;
    Status action = load_file(&book);
    if (action == e_success)
    {
        action = menu(&book);
        if (action == e_success)
        {
            save_prompt(&book);
        }
    }
    return 0;
}