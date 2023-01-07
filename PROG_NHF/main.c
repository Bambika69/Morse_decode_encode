#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "debugmalloc.h"

int main(void){

    make_tree();
    int choice;
    char *input;

    while(choice != 3){

            printf("Please choose a service \nDecrypt morse code -> (1) \nEncrypt morse code -> (2) \nExit               -> (3) \n");
            scanf("%d",&choice);

    switch(choice){

    case 1:

        system("cls");
        printf("Please insert the input\n");

        while( strcmp((input=scan(input)),"end") )
            decode_out(input);

        choice = 0;
        system("cls");
        free(input);
        break;

    case 2:

        system("cls");
        printf("Please insert the input\n");

        while( strcmp((input=scan(input)),"end") )
            encode_out(input);

        choice = 0;
        system("cls");
        free(input);
        break;

    default:

        system("cls");
        printf("Not a valid input\n");
        break;

      }

    }

    system("cls");
    drop_tree();
    free(input);
    return 0;

}
