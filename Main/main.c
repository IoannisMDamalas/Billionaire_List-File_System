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
#include <ctype.h>
#include "functions.h" // My header

#define DEBUG 0 // Debug Mode: ON = 1, OFF = 0

int main(void) {
    //Variables-Tables
    char input[20] = {0}, info[200] = {0}, *ptr1[7] = {NULL}, *ptr2[5] = {NULL}, bC[12], n[100] = {0}, pO[100] = {0}, a[100] = {0}, bP[100] = {0}, g, fName[20] = {0}, tmp, ndl[100] = {0}, wo[100] = {0}, gend;
    mydate bd;  // mydate variable for birth date
    mytime bt;  // mytime variable for birth time
    float w, sumw;    // float variable for worth, sumw for summary of all billionaire worth
    int i, ch = 1, res, l, s;  // i for counter, ch for choice, res for result of checksum, l for length of string, s for size
    billionaire *h = NULL;  // list head which at first is equal to NULL
    FILE *fp;   // pointer to FILE

    srand(time(NULL));  // Initialization of srand
    
    printf(YELLOW"\nWelcome!\nPlease input one of our available commands from below:\n\n"RESET);   //Welcome Message
    instructions(); // calls the instructions() function which prints the main menu

    // do-while loop for user buffer/choices
    do {
        printf(RED"$> "RESET);   
        printf(MAGENTA); 
        scanf("%s",input); // reads the command from the user
        printf(RESET);
        if ((strcmp(input,"exit") == 0)) {   // checks if it is 'exit'
            ch = 0; // and makes ch equal to 0, in order to end the do-while loop
        }
        else if ((strcmp(input,"newbil") == 0)) {  // checks if it is 'newbil'
            fgets(info, sizeof(info), stdin);   // gets the information of the new billionaier from the user

            ptr1[0]=strtok(info,";");   // divides the string with the token ';'
            if(ptr1[0] == NULL) {
                printf(BRIGHT_RED"\nNo info detected.\n\n"RESET);
            }

            for(i = 1 ; i < 7 ; i++) {
                ptr1[i] = strtok(NULL,";"); // continues to divide the string with the token ';'
                if(ptr1[i] == NULL){
                    break;
                }
            }
            
            strcpy(n,ptr1[0]);      // copies the string contained in pointer ptr1[0] and puts it in string n
            normalizeBilName(n);    // normalizes the billionaire's name
            strcpy(pO,ptr1[1]);     // copies the string contained in pointer ptr1[1] and puts it in string pO
            replaceUnknown(pO);     // replaces ? with unknown
            strcpy(a,ptr1[2]);      // copies the string contained in pointer ptr1[2] and puts it in string a
            strcpy(bP,ptr1[3]);     // copies the string contained in pointer ptr1[3] and puts it in string bP
            g = *ptr1[4];           // puts the char contained in pointer ptr1[4] in char g

            #if DEBUG == 1      //For debug purposes
            for(i = 0 ; i < 7 ; i++){
                puts(ptr1[i]);
                printf("\n");
            }
            #endif

            ptr2[0] = strtok(ptr1[5],"/");  // divides the string contained in pointer ptr1[5] (birth date) with the token '/'
            ptr2[1] = strtok(NULL,"/");     // divides the string contained in pointer ptr1[5] (birth date) with the token '/'
            ptr2[2] = strtok(NULL," ");     // divides the string contained in pointer ptr1[5] (birth date) with the token ' '

            bd.day = atoi(ptr2[0]);         // converts the strings into integers and saves them to the struct bd
            bd.month = atoi(ptr2[1]);       // converts the strings into integers and saves them to the struct bd
            bd.year = atoi(ptr2[2]);        // converts the strings into integers and saves them to the struct bd

            ptr2[3] = strtok(NULL,":");     // divides the string contained in pointer ptr1[5] (birth time) with the token ':'
            ptr2[4] = strtok(NULL," ");     // divides the string contained in pointer ptr1[5] (birth time) with the token ' '

            bt.hour = atoi(ptr2[3]);        // converts the strings into integers and saves them to the struct bt
            bt.minutes = atoi(ptr2[4]);     // converts the strings into integers and saves them to the struct bt

            w = atof(ptr1[6]);              // converts the string into float and saves it in w (float)

            #if DEBUG == 1      // For debug purposes
            for(i = 0 ; i < 5 ; i++){
                puts(ptr2[i]);
                printf("\n");
            }
            #endif

            l = strlen(n);      // gets the length of string n

            // finds and removes the space at the start of the string name
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
            // finds and removes the space at the start of the string name
            
            generateAccountNumber(bC);
            //printf("\n%s\n\n",bC);
            
            newBill(&h, n, pO, a, bP, g, bd, bt, w, bC);     // Calls the function newBill and inserts a new billionaire into the double linked circular list 
            //printList(h);      // Displays the list

        }
        else if ((strcmp(input,"save") == 0)) {     // checks if it is 'save'
            fgets(fName, sizeof(fName), stdin);     // gets the name of the file from the user

            l = strlen(fName);      // gets the length of string fName 

            // finds and removes the space at the start of the string fName and the enter at the end
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
            // finds and removes the space at the start of the string fName and the enter at the end
            
            fp = fopen(fName,"w");                                  // opens the file 'fName' with write permissions
            if (fp == NULL) {                                       // checks if the file has opened
                printf(BRIGHT_RED"\nError! Could not open the file!\n\n"RESET);    // if it has not then it informs the user that it could not open the file
            }
            else { //if it has opened
                printf(BRIGHT_BLUE"\nSuccess! File opened!\n\n"RESET);              // it informs the user that the files has been opened

                saveFile(h, fp, fName);                             // it calls the saveFile() function which saves the list data into the file
            }

            fclose(fp);

        }
        else if ((strcmp(input,"load") == 0)) {                     // checks if it is 'load'
            scanf("%d %s", &s, &fName);                             // scanfs the size and the file name from the user

            //printf("%d %s\n",s,fName);                              

            l = strlen(fName);                  // gets the length of the string fName

            //finds and removes the enter from the file name
            for (i = 0 ; i < l ; i++) {         
                if (fName[i] == '\n') {
                    fName[i] = '\0';
                }
            }
            // finds and removes the enter from the file name

            //printf("%d %s\n",s,fName);
            
            fp = fopen(fName,"r");                       // fopens the file with read permissions
            if (fp == NULL) {                           // checks if the file has been opened
                printf(BRIGHT_RED"\nError! Could not open the file!\n\n"RESET);    // if it has not then it informs the user that it could not open the file
            }
            else { //if it has
                printf(BRIGHT_CYAN"\nSuccess! File opened!\n\n"RESET);     // it informs the user that the files has been opened

                loadFile(h, fp, fName, s);                          // it calls the loadFile() function which saves the list data into the file
            }
            fclose(fp);
        }
        else if (strcmp(input,"deleteN") == 0) {                    // checks if it is 'deleteN'         
            deleteN(&h);                 // eletes the newest entry from the list and frees the allocated memory
            printf(BRIGHT_CYAN"\nThe newest entry has been erased from the list.\n\n"RESET);
        }
        else if ((strcmp(input,"deleteO") == 0)) {                  // checks if it is 'deleteO'
            deleteO(&h);                 // deletes the oldest entry from the list and frees the allocated memory
            printf(BRIGHT_CYAN"\nThe oldest entry has been erased from the list.\n\n"RESET);
        }
        else if ((strcmp(input,"deleteA") == 0)) {                  // checks if it is 'deleteA'
            deleteA(&h);                // deletes the entire list and frees the allocated memory 
        }
        else if ((strcmp(input,"sum") == 0)) {                      // checks if it is 'sum'
            sumw = sum(h);              // sums up all the billionaire's worth from the list
            printf(BRIGHT_BLUE"\nAll the billionaires that are in the list, have a total of %.2f"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK".\n\n"RESET,sumw);
        }
        else if ((strcmp(input,"findN") == 0)) {                    // checks if it is 'findN'
            fgets(ndl, sizeof(ndl), stdin);                         // fgets the 'needle' string from user         

            l = strlen(ndl);                                        // gets the length of string ndl

            // finds and removes the space at the start of the string ndl and the enter at the end
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
            // finds and removes the space at the start of the string ndl and the enter at the end


            findN(h, ndl);                                          // calls the findN() functions which finds any billionaire with the string ndl in their name
        }
        else if ((strcmp(input,"findC") == 0)) {                    // checks if it is 'findC'
            fgets(ndl, sizeof(ndl), stdin);                         // fgets the 'needle' string from user

            l = strlen(ndl);                                        // gets the length of ndl

            // finds and removes the space at the start of the string ndl and the enter at the end
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
            // finds and removes the space at the start of the string ndl and the enter at the end

            findC(h, ndl);                  // calls the findC() functions which finds any billionaire with the string ndl in their City/Country/Birthplace
        }
        else if ((strcmp(input,"findS") == 0)) {     // checks if it is 'findS'
            fgets(ndl, sizeof(ndl), stdin);          // fgets the needle from the user

            l = strlen(ndl);                         // gets the length of the string ndl

            // finds and removes the space at the start of the string ndl and the enter at the end
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
            // finds and removes the space at the start of the string ndl and the enter at the end

            findS(h, ndl);    // calls the findS() function which finds any billionaire with the string ndl in their Activity
        }
        else if((strcmp(input,"print+") == 0)) {    // checks if it is 'print+'
            fgets(wo, sizeof(wo), stdin);           // fgets the wo from the user

            l = strlen(wo);                         // gets the length of the string wo

            // finds and removes the space at the start of the string ndl and the enter at the end
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
            // finds and removes the space at the start of the string ndl and the enter at the end

            printGreater(h, wo);                // calls the printGreater() functions which finds any billionaire with worth greater than wo
        }
        else if((strcmp(input,"print-") == 0)) {    // checks if it is 'print-'
            fgets(wo, sizeof(wo), stdin);           // fgets the wo from the user

            l = strlen(wo);                         // gets the length of the string wo

            // finds and removes the space at the start of the string ndl and the enter at the end
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
            // finds and removes the space at the start of the string ndl and the enter at the end

            printLess(h, wo);           // calls the printLess() functions which finds any billionaire with worth less than wo
        }
        else if((strcmp(input,"print=") == 0)) {   // checks if it is 'print='
            fgets(wo, sizeof(wo), stdin);           // fgets the wo from the user

            l = strlen(wo);                         // gets the length of the string wo

            // finds and removes the space at the start of the string ndl and the enter at the end
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
            // finds and removes the space at the start of the string ndl and the enter at the end

            printEqual(h, wo);      // calls the printEqual() functions which finds any billionaire with worth equal to wo
        }
        else if((strcmp(input,"printA") == 0)) {    // checks if it is 'printA'
            printA(h);              // calls the printA() functions which prints the entire list
        }
        else if((strcmp(input,"help") == 0)) {
            instructions();
        }
        else {      // in any other circumstance
            printf(BRIGHT_YELLOW"\nCommand does not exist!\nPlease check our available commands using \'help\':\n\n"RESET); //informs the user that the command they gave is non-existent
        }
    } while(ch != 0);    // do-while condition to check if the user has typed 'exit' 

    deleteA(&h);        // deletes the entire list and frees the allocated memory
    printf(YELLOW"\nGoodbye, thank you for using our program! :)\nExiting program...\n\n"RESET);     // Prints a message to inform the user that the program is closing

    return 0;       // returns 0
}