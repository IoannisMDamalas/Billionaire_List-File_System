/*

Ioannis - Marios Damalas
AM: 2022202300234
dit23234@go.uop.gr

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(void)
{
    char input[20] = {0}, info[200] = {0}, *ptr[7] = {NULL};
    int i;
    //billionaire info[1];


    printf("Welcome!\n");
    printf("$> ");
    scanf("%s",input);
    if ((strcmp(input,"exit") == 0) || (strcmp(input,"EXIT") == 0))
    {
        printf("Exiting program...\n");
        exit(1);
    }
    else if ((strcmp(input,"newbil") == 0))
    {
        fgets(info, sizeof(info), stdin);
        
        ptr[0]=strtok(info,";");
        if(ptr[0]==NULL)
        {
            printf("No info detected.\n");
            exit(0);
        }

        for(i = 1 ; i < 7 ; i++)
        {
            ptr[i] = strtok(NULL,";");
            if(ptr[i] == NULL)
            {
                break;
            }
        }   
    }

    for(i = 0 ; i < 7 ; i++)
    {
        puts(ptr[i]);
        printf("\n");
    }

    return 0;
}