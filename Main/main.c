/*

Ioannis - Marios Damalas
AM: 2022202300234
dit23234@go.uop.gr

Dimitrios - Xristos Dafnomilis
AM: 2022202300245
dit23245@go.uop.gr

*/

//Function Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "functions.h" //My header

#define DEBUG 0 //Debug Mode: ON = 1, OFF = 0

int main(void) {
    //Variables-Tables
    char input[20] = {0}, info[200] = {0}, *ptr1[7] = {NULL}, *ptr2[5] = {NULL}, bC[11], n[100] = {0}, pO[100] = {0}, a[100] = {0}, bP[100] = {0}, g, fName[20] = {0}, tmp, ndl[100] = {0}, wo[100] = {0};
    mydate bd;  //mydate variable for birth date
    mytime bt;  //mytime variable for birth time
    float w, sumw;    //float variable for worth, sumw for summary of all billionaire worth
    int i, ch = 1, res, l, s;  //i for counter, ch for choice, res for result of checksum, l for length of string, s for size
    billionaire *h = NULL;  //list head which at first is equal to NULL
    FILE *fp;   //pointer to FILE

    srand(time(NULL));  //Initialization of srand
    
    printf("\nWelcome!\nPlease input one of our available commands from below:\n\n");
    instructions();

    //do-while loop for user buffer/choices
    do {
        printf("$> ");
        scanf("%s",input); //reads the command from the user
        if ((strcmp(input,"exit") == 0)) {   //checks if it is 'exit' or 'EXIT'
            ch = 0; //and makes ch equal to 0, in order to end the do-while loop
        }
        else if ((strcmp(input,"newbil") == 0)) {  //checks if it is 'newbil' or 'NEWBIL'
            fgets(info, sizeof(info), stdin);   //gets the information of the new billionaier from the user

            ptr1[0]=strtok(info,";");   //divides the string with the token ';'
            if(ptr1[0] == NULL) {
                printf("\nNo info detected.\n\n");
                exit(0);
            }

            for(i = 1 ; i < 7 ; i++) {
                ptr1[i] = strtok(NULL,";"); //continues to divide the string with the token ';'
                if(ptr1[i] == NULL){
                    break;
                }
            }

            strcpy(n,ptr1[0]);  //copys the string contained in pointer ptr1[0] and puts it in string n
            strcpy(pO,ptr1[1]); //copys the string contained in pointer ptr1[1] and puts it in string pO
            strcpy(a,ptr1[2]);  //copys the string contained in pointer ptr1[2] and puts it in string a
            strcpy(bP,ptr1[3]); //copys the string contained in pointer ptr1[3] and puts it in string bP
            g = *ptr1[4];       //puts the char contained in pointer ptr1[4] in char g

            #if DEBUG == 1      //For debug purposes
            for(i = 0 ; i < 7 ; i++){
                puts(ptr1[i]);
                printf("\n");
            }
            #endif

            ptr2[0] = strtok(ptr1[5],"/");  //divides the string contained in pointer ptr1[5] (birth date) with the token '/'
            ptr2[1] = strtok(NULL,"/");     //divides the string contained in pointer ptr1[5] (birth date) with the token '/'
            ptr2[2] = strtok(NULL," ");     //divides the string contained in pointer ptr1[5] (birth date) with the token ' '

            bd.day = atoi(ptr2[0]);         //converts the strings into integers and saves them to the struct bd
            bd.month = atoi(ptr2[1]);       //converts the strings into integers and saves them to the struct bd
            bd.year = atoi(ptr2[2]);        //converts the strings into integers and saves them to the struct bd

            ptr2[3] = strtok(NULL,":");     //divides the string contained in pointer ptr1[5] (birth time) with the token ':'
            ptr2[4] = strtok(NULL," ");     //divides the string contained in pointer ptr1[5] (birth time) with the token ' '

            bt.hour = atoi(ptr2[3]);        //converts the strings into integers and saves them to the struct bt
            bt.minutes = atoi(ptr2[4]);     //converts the strings into integers and saves them to the struct bt

            w = atof(ptr1[6]);              //converts the string into float and saves it in w (float)

            #if DEBUG == 1      //For debug purposes
            for(i = 0 ; i < 5 ; i++){
                puts(ptr2[i]);
                printf("\n");
            }
            #endif

            l = strlen(n);

            for (i = 0 ; i < l ; i++) {
                tmp = n[i];
                n[i] = n[i + 1];
                n[i + 1] = tmp;
            }

            for (i = 0 ; i < l ; i++) {
                if (n[i] == ' ') {
                    n[i] == '\0';
                }
            }

            /*
            CHECKSUM:
            sprintf(bC, "%d", bankCode());
            res = checksum(bC);

            if (res >= 0) {
                sprintf(bC + 9, "%d", res);
            }
            else {
                goto CHECKSUM;
            }
            puts(bC);
            */

            newBill(&h, n, pO, a, bP, g, bd, bt, w, bC);     //Calls the function newBill and inserts a new billionaire into the double linked circular list 
            //printList(h);      //Displays the list

        }
        else if ((strcmp(input,"save") == 0)) {
            fgets(fName, sizeof(fName), stdin);

            l = strlen(fName);

            for (i = 0 ; i < l ; i++) {
                if (fName[i] == '\n') {
                    fName[i] = '\0';
                }
            }

            for (i = 0 ; i < l ; i++) {
                tmp = fName[i];
                fName[i] = fName[i + 1];
                fName[i + 1] = tmp; 
            }

            for (i = 0 ; i < l ; i++) {
                if (fName[i] == ' ') {
                    fName[i] == '\0';
                }
            }
            
            fp = fopen(fName,"w");
            if (fp == NULL) {
                printf("\nError! Could not open the file!\n\n");
            }
            else {
                printf("\nSuccess! File opened!\n\n");

                saveFile(h, fp, fName);
            }

        }
        else if ((strcmp(input,"load") == 0)) {
            scanf("%d %s", &s, &fName);

            printf("%d %s\n",s,fName);

            l = strlen(fName);

            for (i = 0 ; i < l ; i++) {
                if (fName[i] == '\n') {
                    fName[i] = '\0';
                }
            }

            printf("%d %s\n",s,fName);
            
            fp = fopen(fName,"r");
            if (fp == NULL) {
                printf("\nError! Could not open the file!\n\n");
            }
            else {
                printf("\nSuccess! File opened!\n\n");

                loadFile(h, fp, fName, s);
            }
        }
        else if (strcmp(input,"deleteN") == 0) {
            deleteN(&h);
            printf("\nThe newest entry has been erased.\n\n");
        }
        else if ((strcmp(input,"deleteO") == 0)) {
            deleteO(&h);
            printf("\nThe oldest entry has been erased.\n\n");
        }
        else if ((strcmp(input,"sum") == 0)) {
            sumw = sum(h);
            printf("\nAll the billionaires that are in the list, have a total of %.2f$.\n\n",sumw);
        }
        else if ((strcmp(input,"findN") == 0)) {
            fgets(ndl, sizeof(ndl), stdin);

            l = strlen(ndl);

            for (i = 0 ; i < l ; i++) {
                if (ndl[i] == '\n') {
                    ndl[i] = '\0';
                }
            }

            for (i = 0 ; i < l ; i++) {
                tmp = ndl[i];
                ndl[i] = ndl[i + 1];
                ndl[i + 1] = tmp; 
            }

            for (i = 0 ; i < l ; i++) {
                if (ndl[i] == ' ') {
                    ndl[i] == '\0';
                }
            }

            findN(h, ndl);
        }
        else if ((strcmp(input,"findC") == 0)) {
            fgets(ndl, sizeof(ndl), stdin);

            l = strlen(ndl);

            for (i = 0 ; i < l ; i++) {
                if (ndl[i] == '\n') {
                    ndl[i] = '\0';
                }
            }

            for (i = 0 ; i < l ; i++) {
                tmp = ndl[i];
                ndl[i] = ndl[i + 1];
                ndl[i + 1] = tmp; 
            }

            for (i = 0 ; i < l ; i++) {
                if (ndl[i] == ' ') {
                    ndl[i] == '\0';
                }
            }

            findC(h, ndl);
        }
        else if ((strcmp(input,"findS") == 0)) {
            fgets(ndl, sizeof(ndl), stdin);

            l = strlen(ndl);

            for (i = 0 ; i < l ; i++) {
                if (ndl[i] == '\n') {
                    ndl[i] = '\0';
                }
            }

            for (i = 0 ; i < l ; i++) {
                tmp = ndl[i];
                ndl[i] = ndl[i + 1];
                ndl[i + 1] = tmp; 
            }

            for (i = 0 ; i < l ; i++) {
                if (ndl[i] == ' ') {
                    ndl[i] == '\0';
                }
            }

            findS(h, ndl);
        }
        else if((strcmp(input,"print+") == 0)) {
            fgets(wo, sizeof(wo), stdin);

            l = strlen(wo);

            for (i = 0 ; i < l ; i++) {
                if (wo[i] == '\n') {
                    wo[i] = '\0';
                }
            }

            for (i = 0 ; i < l ; i++) {
                tmp = wo[i];
                wo[i] = wo[i + 1];
                wo[i + 1] = tmp; 
            }

            for (i = 0 ; i < l ; i++) {
                if (wo[i] == ' ') {
                    wo[i] == '\0';
                }
            }

            printGreater(h, wo);
        }
        else if((strcmp(input,"print-") == 0)) {
            fgets(wo, sizeof(wo), stdin);

            l = strlen(wo);

            for (i = 0 ; i < l ; i++) {
                if (wo[i] == '\n') {
                    wo[i] = '\0';
                }
            }

            for (i = 0 ; i < l ; i++) {
                tmp = wo[i];
                wo[i] = wo[i + 1];
                wo[i + 1] = tmp; 
            }

            for (i = 0 ; i < l ; i++) {
                if (wo[i] == ' ') {
                    wo[i] == '\0';
                }
            }

            printLess(h, wo);
        }
        else if((strcmp(input,"print=") == 0)) {
            fgets(wo, sizeof(wo), stdin);

            l = strlen(wo);

            for (i = 0 ; i < l ; i++) {
                if (wo[i] == '\n') {
                    wo[i] = '\0';
                }
            }

            for (i = 0 ; i < l ; i++) {
                tmp = wo[i];
                wo[i] = wo[i + 1];
                wo[i + 1] = tmp; 
            }

            for (i = 0 ; i < l ; i++) {
                if (wo[i] == ' ') {
                    wo[i] == '\0';
                }
            }

            printEqual(h, wo);
        }
        else if((strcmp(input,"printL") == 0)) {
            printList(h);
        }
        else {
            printf("\nCommand does not exist!\nPlease check our available commands below:\n\n");
            instructions();
        }
    } while(ch != 0);    //do-while condition to check if the user has typed 'exit' 

    printf("\nExiting program...\n\n");     //Prints a message to inform the user that the program is closing

    return 0;       //returns 0
}