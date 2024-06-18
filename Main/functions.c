// Function Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

// User Created Functions Bodies

// newNode START
billionaire *newNode(char na[], char plO[], char act[], char bPl[], char gen, mydate biD, mytime biT, float wo, char baC[]) {

    billionaire *node;  // Pointer to billionaire struct
    
    node = (billionaire*)malloc(sizeof(billionaire));     // Allocates memory with the use of malloc()

    if (node == NULL) {
        printf(BRIGHT_RED"Error! Could not allocate memory!\n"RESET);
        exit(0);
    }

    // Puts the new billionaire data into the corresponding variables on the billionaire node
    node->name = strdup(na);
    node->pOrigin = strdup(plO);
    node->activity = strdup(act);
    node->bPlace = strdup(bPl);
    node->gender = gen;

    node->birthdate.day = biD.day;
    node->birthdate.month = biD.month;
    node->birthdate.year = biD.year;

    node->birthtime.hour = biT.hour;
    node->birthtime.minutes = biT.minutes;

    node->worth = wo;

    node->bankC = strdup(baC);

    // keeps the list circular and double linked
    node->next = node;
    node->prev = node;

    return node;    // returns the new node
}
// newNode END

// newBill START
void *newBill(billionaire **head, char na[], char plO[], char act[], char bPl[], char gen, mydate biD, mytime biT, float wo, char baC[]) {

    billionaire *newBillionaire, *last;     // 2 pointers to the billionaire struct
    
    newBillionaire = newNode(na, plO, act, bPl, gen, biD, biT, wo, baC);    // calls the function newNode and returns the new node to newBillionaire

    if (*head == NULL) {        // checks if the list head is equal to NULL
        *head = newBillionaire; // if it is, it means that the new node is the first node of the list and makes it the head
    }
    else {                              // if not, it inserts the new node to the end of the list
        last = (*head)->prev;           // last is equal to the previous node of the head of the list
        last->next = newBillionaire;    // the next node of last is equal to newBillionaire
        newBillionaire->prev = last;    // the previous node of newBillionaire is equal to last
        newBillionaire->next = *head;   // the next node of newBillionaire is equal to the head of the list
        (*head)->prev = newBillionaire; // the previous node of the head of the list is equal to newBillionaire
    }

    printf(BRIGHT_CYAN"\nNew billionaire succesfully inserted to the list.\n\n"RESET);

    // returns nothing because the function is void
}
// newBill END

// deleteN START
void deleteN(billionaire **head) {
    billionaire *lst, *slst; // pointers to the last node of the list and second last of the list accordingly

    if ((*head) == NULL) {                  // checks if the head of the list is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);     // if it is, then it informs the user that the list is empty

        return;     // returns nothing because the function is void
    }

    // if not, then:

    lst = (*head)->prev;    // makes the last nod same as the previous node of the head of the list

    if (lst == (*head)) {   // checks if the last node is equal to the head of the list
        free(lst);          // if it is, it means that the list has only one node and it frees the allocated memory
        (*head) = NULL;     // now the head of the list is equal to NULL
    }
    else {                     // else, the list has more than 1 nodes
        slst = lst->prev;      // it makes the second last node equal to the previous node of the last node 
        slst->next = (*head);  // it makes the next node of the second last node equal to the head of the list
        (*head)->prev = slst;  // it makes the previous node of the head of the list equal to the second last node
        free(lst->name);
        free(lst->pOrigin);
        free(lst->activity);
        free(lst->bPlace);
        free(lst);             // it frees the allocated memory for the last node of the list
    }

    return;   // returns nothing because the function is void

}
// deleteN END

// deleteO START
void deleteO(billionaire **head) {
    billionaire *fst, *snd, *lst;   // pointers to the first, second and last node of the list accordingly

    if ((*head) == NULL) {                    // checks if the head of the list is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);   // if it is, the user is informed that the list is empty

        return;                         // returns nothing because the function is void
    }

    fst = (*head);                      // makes the first node the same as the head of the list
    lst = fst->prev;                    // makes the last node the same as the previous of the first node

    if (fst == lst) {                   // checks if the first node is equal to the last node
        free(fst);                      // if it is, it means that the list has only one node and it frees the allocated memory
        (*head) = NULL;                 // makes the head of the list equal to NULL
    }
    else {                              // else, the list has more than 1 node
        snd = fst->next;                // makes the second node the same as the next of the first node
        lst->next = snd;                // makes the next of the last node the same as the second node
        snd->prev = lst;                // makes the previous of the second node the same as the last node
        free(fst->name);
        free(fst->pOrigin);
        free(fst->activity);
        free(fst->bPlace);
        free(fst);                      // it frees the allocated memory for the first node of the list
        (*head) = snd;                  // makes the head of the list equal to the second node
    }

    return;                             //  returns nothing because the function is void
}
//deleteO END

//deleteA START
void deleteA(billionaire **head) {
    billionaire *tmp, *tmp2;        // pointers tmp and tmp2

    if ((*head) == NULL) {                          // checks if the head of the list is equal to NULL
        return;                                     // returns nothing because the function is void
    }
    else {
        tmp = (*head);                              
        
        do {
            tmp2 = tmp->next;   // makes the second tmp(node) the same as the next of the first tmp(node)
            free(tmp->name);    
            free(tmp->pOrigin);
            free(tmp->activity);
            free(tmp->bPlace);
            free(tmp);          // it frees the allocated memory for the first tmp(node) of the list
            tmp = tmp2;
        } while (tmp != (*head));

        (*head) = NULL;          // makes the head of the list equal to the NULL

        printf(BRIGHT_CYAN"\nAll entries have been erased from the list.\n\n"RESET);
    }
    
    return;     // returns nothing because the function is void
}
// deleteA END

// printList START
void printA(billionaire *head) {
    billionaire *tmp;  // a temporary pointer to the struct billionaire

    if (head == NULL) { // checks if the head is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);     // if it is, then it informs the user that the list is empty

        return;
    }

    //if not
    tmp = head;  // temp is equal to the head of the list  

    // do-while loop to print all the nodes of the list
    do {
        printf(BRIGHT_BLACK"\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\n"RESET BRIGHT_GREEN"Worth: %.2fB"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK"\nBank Code: %s\n\n"RESET, tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
        tmp = tmp->next;  // moves to the next node of the list
    } while (tmp != head); // do-while condition to keep printing the next node as long as temp is not equal to the head of the list

    return;     // returns nothing because the function is void
}
// printList END

// printGreater START
void printGreater(billionaire *head, char mon[]) {
    billionaire *tmp;  // a temporary pointer to the struct billionaire
    float worth;
    int flag = -1;

    if (head == NULL) { // checks if the head is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);     // if it is, then it informs the user that the list is empty

        return;
    }

    // if not
    tmp = head;  // temp is equal to the head of the list  

    worth = atof(mon);

    // do-while loop to print all the nodes of the list
    do {
        if (worth < tmp->worth) {
            printf(BRIGHT_BLACK"\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\n"RESET BRIGHT_GREEN"Worth: %.2fB"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK"\nBank Code: %s\n\n"RESET, tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
            flag = 1;
        }
        tmp = tmp->next;  // moves to the next node of the list
    } while (tmp != head); // do-while condition to keep printing the next node as long as temp is not equal to the head of the list

    if (flag != 1) {
        printf(BRIGHT_CYAN"\nThere is not a billionaire on the list whose worth is greater than %.2f"RESET BRIGHT_GREEN"$\n\n"RESET, worth);
    }

    return;     // returns nothing because the function is void
}
//printGreater END

//printLess START
void printLess(billionaire *head, char mon[]) {
    billionaire *tmp;  // a temporary pointer to the struct billionaire
    float worth;
    int flag = -1;

    if (head == NULL) { // checks if the head is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);     // if it is, then it informs the user that the list is empty

        return;
    }

    // if not
    tmp = head;  // temp is equal to the head of the list  

    worth = atof(mon);

    // do-while loop to print all the nodes of the list
    do {
        if (worth > tmp->worth) {
            printf(BRIGHT_BLACK"\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\n"RESET BRIGHT_GREEN "Worth: %.2fB"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK"\nBank Code: %s\n\n"RESET, tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
            flag = 1;
        }
        tmp = tmp->next;  // moves to the next node of the list
    } while (tmp != head); // do-while condition to keep printing the next node as long as temp is not equal to the head of the list

    if (flag != 1) {
        printf(BRIGHT_CYAN"\nThere is not a billionaire on the list whose worth is less than %.2f"RESET BRIGHT_GREEN"$"RESET BRIGHT_CYAN"\n\n"RESET, worth);
    }

    return;     // returns nothing because the function is void
}
// printLess END

// printEqual START
void printEqual(billionaire *head, char mon[]) {
    billionaire *tmp;  // a temporary pointer to the struct billionaire
    float worth;
    int flag = -1;

    if (head == NULL) { // checks if the head is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);     // if it is, then it informs the user that the list is empty

        return;
    }

    // if not
    tmp = head;  // temp is equal to the head of the list  

    worth = atof(mon);

    // do-while loop to print all the nodes of the list
    do {
        if (worth == tmp->worth) {
            printf(BRIGHT_BLACK"\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\n"RESET BRIGHT_GREEN"Worth: %.2fB"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK"\nBank Code: %s\n\n"RESET, tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
            flag = 1;
        }
        tmp = tmp->next;  // moves to the next node of the list
    } while (tmp != head); // do-while condition to keep printing the next node as long as temp is not equal to the head of the list

    if (flag != 1) {
        printf(BRIGHT_CYAN"\nThere is not a billionaire on the list whose worth is equal to %.2f"RESET BRIGHT_GREEN"$\n\n"RESET, worth);
    }

    return;     // returns nothing because the function is void
}
// printEqual END

// saveFile START
void saveFile(billionaire *head, FILE *f, char fn[]) {
    billionaire *tmp;

    tmp = head;

    if (tmp == NULL) {
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);
    }
    else {
        do {
            fprintf(f, "%s;%s;%s;%s;%c;%d/%d/%d %02d:%02d;%.2fB$;%s;\n", tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
            tmp = tmp->next;
        } while (tmp != head);
        printf(BRIGHT_MAGENTA"\nSuccess! Data saved in \'%s\'!\n\n"BRIGHT_MAGENTA,fn);
    }

    return;
}
// saveFile END

// loadFile START
void loadFile(billionaire *head, FILE *f, char fn[], int size) {
    billionaire *tmp;
    int i;
    char info[200], *ptr1[7] = {NULL}, *ptr2[5] = {NULL}, n[100] = {0}, pO[100] = {0}, a[100] = {0}, bP[100] = {0}, g, bC[12] = "Hello";
    mydate bd;  // mydate variable for birth date
    mytime bt;  // mytime variable for birth time
    float w;

    tmp = head;
    
    for (i = 0 ; i < size ; i++) {
        if (feof(f)) {
            printf(BRIGHT_RED"\nThe file is empty.\n\n"RESET);

            return;
        }
        else {
            
            fgets(info, sizeof(info), f);
            //puts(info);

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

            strcpy(n,ptr1[0]);  // copies the string contained in pointer ptr1[0] and puts it in string n
            strcpy(pO,ptr1[1]); // copies the string contained in pointer ptr1[1] and puts it in string pO
            strcpy(a,ptr1[2]);  // copies the string contained in pointer ptr1[2] and puts it in string a
            strcpy(bP,ptr1[3]); // copies the string contained in pointer ptr1[3] and puts it in string bP
            g = *ptr1[4];       // puts the char contained in pointer ptr1[4] in char g

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

            newBill(&tmp, n, pO, a, bP, g, bd, bt, w, bC);     // Calls the function newBill and inserts a new billionaire into the double linked circular list 

            tmp = tmp->next;
        }
    }
    
    printf(BRIGHT_CYAN"\nSuccess! Data Loaded in list!\n\n"RESET);

    return;
}
// loadFile END

// instructions START
void instructions(void) {
    printf(MAGENTA"Available Commands:\n"RESET);
    printf(RED"    1. $> "RESET MAGENTA"newbil Name;OriginOfActivity;Activity;BirthPlace;Gender;Day/Month/Year Hour:Minutes;Worth$;\n"RESET);
    printf(RED"    2. $> "RESET MAGENTA"sum \'worth\' (The total sum of the networth of every billionaire in the list)\n"RESET);
    printf(RED"    3. $> "RESET MAGENTA"findN/findC/findS \'string\' (Searches if there is the inserted string in any of the billionaire's Name/City-Country/Activity info in the list)\n"RESET);
    printf(RED"    4. $> "RESET MAGENTA"print+/print-/print=/printA \'worth\' (Searches billionaires with greater/less/equal networths than/to the user's input) (printA prints the whole list)\n"RESET);
    printf(RED"    5. $> "RESET MAGENTA"deleteN/deleteO/deleteA (deletes the newest/oldest/all entry/entries from the list)\n"RESET);
    printf(RED"    6. $> "RESET MAGENTA"save \'file_name\'.txt (saves list data locally)\n"RESET);
    printf(RED"    7. $> "RESET MAGENTA"load \'size\' \'file_name\'.txt (loads data from file onto the list)\n"RESET);
    printf(RED"    8. $> "RESET MAGENTA"help (shows available commands)\n"RESET);
    printf(RED"    9. $> "RESET MAGENTA"exit (exits the program)\n\n"RESET);

    return;
}
// instructions END

// findN START
void findN(billionaire *head, char needle[]) {     
    billionaire *tmp;                           // pointer tmp
    char *res1, *res2, *fUpper, *fLower;        // char pointers for strings
    int flag = -1;                              // flag equal to -1, in order to see if there is a need to print the absence of the string in the bil's name

    tmp = head;               // makes tmp equal to head

    if (tmp == NULL) {                           // checks if tmp is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);     // if it is,then it informs the user that the list is empty
    }
    else {        //else
        fUpper = strdup(needle);            // it duplicates the needle string and puts it in fUpper
        fUpper[0] = toupper(needle[0]);     // it makes the first character uppercase

        fLower = strdup(needle);            // it duplicates the needle string and puts it in fLower
        fLower[0] = tolower(needle[0]);     // it makes the first character lowercase
        do { //do-while loop to traverse the whole list
            res1 = strstr(tmp->name, fUpper);   // checks if fUpper is in tmp->name
            res2 = strstr(tmp->name, fLower);   // checks if fLower is in  tmp->name

            if ((res1 != NULL) || (res2 != NULL)) {     // if any of them are in tmp->name, it prints the data
                printf(BRIGHT_BLACK"\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\n"RESET BRIGHT_GREEN "Worth: %.2fB"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK"\nBank Code: %s\n\n"RESET, tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
                flag = 1;       // makes flag equal to 1
            }

            tmp = tmp->next;        // traverses to the next node of the list
        } while (tmp != head);      // while tmp node not equal to head node
        
    }

    if (flag != 1) {                // if flag is equal to 1
        printf(BRIGHT_RED"\nThere is not a billionaire on the list with the string \'%s\' in their name.\n\n"RESET, needle);
    } // then it informs the user that there is not a billionaire

    return;     // returns nothing because the function is void
}
// findN END

// findC START
void findC(billionaire *head, char needle[]) {
    billionaire *tmp;                                    // pointer tmp
    char *res1, *res2, *res3, *res4, *fUpper, *fLower;   // char pointers for strings
    int flag = -1;                                       // flag equal to -1, in order to see if there is a need to print the absence of the string in the bil's geographical details

    tmp = head;             // makes tmp equal to head

    if (tmp == NULL) {                                    // checks if tmp is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);               // if it is,then it informs the user that the list is empty
    }
    else {  //else
        fUpper = strdup(needle);                          // it duplicates the needle string and puts it in fUpper
        fUpper[0] = toupper(needle[0]);                   // it makes the first character uppercase

        fLower = strdup(needle);                          // it duplicates the needle string and puts it in fLower  
        fLower[0] = tolower(needle[0]);                   // it makes the first character lowercase
        do {    //do-while loop to traverse the whole list
            res1 = strstr(tmp->pOrigin, fUpper);           // checks if fUpper is in tmp->pOrigin
            res2 = strstr(tmp->pOrigin, fLower);           // checks if fLower is in tmp->pOrigin
            res3 = strstr(tmp->bPlace, fUpper);            // checks if fUpper is in tmp->bPlace
            res4 = strstr(tmp->bPlace, fLower);            // checks if fLower is in tmp->bPlace

            if ((res1 != NULL) || (res2 != NULL) || (res3 != NULL) || (res4 != NULL)) {  // if any of them are in tmp->pOrigin or tmp->bPlace , it prints the data
                printf(BRIGHT_BLACK"\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\n"RESET BRIGHT_GREEN"Worth: %.2fB"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK"\nBank Code: %s\n\n"RESET, tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
                flag = 1;       // makes flag equal to 1
            }

            tmp = tmp->next;    // traverses to the next node of the list
        } while (tmp != head);  // while tmp node not equal to head node
        
    }

    if (flag != 1) {    // if flag is equal to 1
        printf(BRIGHT_RED"\nThere is not a billionaire on the list with the string \'%s\' in their City/Country - Birthplace.\n\n"RESET, needle);
    }   // then it informs the user that there is not a billionaire

    return;     //returns nothing because the function is void
}
// findC END

// findS START
void findS(billionaire *head, char needle[]) {
    billionaire *tmp;                             // pointer tmp
    char *res1, *res2, *fUpper, *fLower;          // char pointers for strings
    int flag = -1;                                // flag equal to -1, in order to see if there is a need to print the absence of the string in the bil's activity details                                

    tmp = head;             // makes tmp equal to head

    if (tmp == NULL) {                              // checks if tmp is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);         // if it is,then it informs the user that the list is empty
    }
    else {  //else
        fUpper = strdup(needle);                    // it duplicates the needle string and puts it in fUpper
        fUpper[0] = toupper(needle[0]);             // it makes the first character uppercase

        fLower = strdup(needle);                    // it duplicates the needle string and puts it in fLower  
        fLower[0] = tolower(needle[0]);             // it makes the first character lowercase
        do {    // do-while loop to traverse the whole list
            res1 = strstr(tmp->activity, fUpper);   // checks if fUpper is in tmp->activity
            res2 = strstr(tmp->activity, fLower);   // checks if fLower is in tmp->activity

            if ((res1 != NULL) || (res2 != NULL)) {     // if any of them are in tmp->activity, it prints the data
                printf(BRIGHT_BLACK"\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\n"RESET BRIGHT_GREEN"Worth: %.2fB"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK"\nBank Code: %s\n\n"RESET, tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
                flag = 1;       // makes flag equal to 1
            }

            tmp = tmp->next;    // traverses to the next node of the list
        } while (tmp != head);  // while tmp node not equal to head node
        
    }

    if (flag != 1) {        // if flag is equal to 1
        printf(BRIGHT_RED"\nThere is not a billionaire on the list with the string \'%s\' in their Activity.\n\n"RESET, needle);
    }   // then it informs the user that there is not a billionaire

    return;     //returns nothing because the function is void
}
// findS END

/* findG START
void findG(billionaire *head, char gnd) {
    billionaire *tmp;  // pointer tmp
    char fUpper;       // char variable
    int flag = -1;     // flag equal to -1, in order to see if there is a need to print the absence of the gender

    tmp = head;               // makes tmp equal to head

    if (tmp == NULL) {                                          // checks if tmp is equal to NULL
        printf(BRIGHT_RED"\nThe list is empty.\n\n"RESET);     // if it is,then it informs the user that the list is empty
    }
    else {        //else
        fUpper = toupper(gnd);           // it makes the char gnd Uppercase

        do { //do-while loop to traverse the whole list

            if (fUpper == tmp->gender) {     // if it is equal to tmp->gender, it prints the data
                printf(BRIGHT_BLACK"\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\n"RESET BRIGHT_GREEN "Worth: %.2fB"RESET BRIGHT_GREEN"$"RESET BRIGHT_BLACK"\nBank Code: %s\n\n"RESET, tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
                flag = 1;       // makes flag equal to 1
            }

            tmp = tmp->next;        // traverses to the next node of the list
        } while (tmp != head);      // while tmp node not equal to head node
        
    }

    if (flag != 1) {                // if flag is equal to 1
        printf(BRIGHT_RED"\nThere is not a billionaire on the list with the gender \'%c\'.\n\n"RESET, gnd);
    } // then it informs the user that there is not a billionaire with that gender

    return;     // returns nothing because the function is void
}
 findG END */

// generateRandomDigits
void generateRandomDigits(char *accountNumber, int length) {
    int i, r;

    for (i = 0 ; i < length ; i++) {
        r = 1 + rand() % 9; // Generate a random digitt between 1 and 9
        accountNumber[i] = '0' + r; // Convert the digit to a character and assign it to the account's number
    }
}
// generateRandomDigits END

// calculateCheckDigit START
int calculateCheckDigit(const char *accountNumber) {
    int sum = 0, i, digit;

    for (i = 9 ; i > 0 ; i-=2) { // Repeat for every second digit starting from the end
        digit = accountNumber[i] - '0'; // Convert character to integer
        
        digit *= 2;
        if (digit > 9) { // If the result is greater than 9, sum the digits of the result
            digit = digit / 10 + digit % 10;
        }
        
        sum += digit;
    }
    sum *= 9;

    return sum % 10; // Return the last digit of the sum
}
// calculateCheckDigit END

// generateAccountNumber START
void generateAccountNumber(char *accountNumber) {
    generateRandomDigits(accountNumber, 10);              // Generate 10 random digits for the account number
    int checkDigit = calculateCheckDigit(accountNumber); // Calculates the check digit
    accountNumber[10] = '0' + checkDigit; // Annex/Add the check digit to the account number
    accountNumber[11] = '\0'; // Null-terminate the string
}
// generateAccountNumber END

// normalizeBilName START

void normalizeBilName(char *name) {
    int len = strlen  (name);
    int i;

    name[0] = toupper(name[0]);
    for (i=1; i < len; i++) {
        if (name[i - 1] == ' ') {
            name[i] = toupper(name[i]);
        }
        else {
            name[i] = tolower(name[i]);
        }
    }
}

// normalizeBilName END

// replaceUnknown START

void replaceUnknown(char *str) {
    if (strcmp(str,"?") == 0) {
        strcpy(str,"Unknown");
    }
    else if (strcmp(str,"?/?") == 0) {
        strcpy(str,"Unknown/Unknown");
    }
}

// replaceUnknown END

// sum START
float sum(billionaire *head) {
    billionaire *tmp;
    float sum = 0;

    tmp = head;

    if (tmp == NULL) {
        printf(BRIGHT_RED"\nThe list is empty!\n\n"RESET);
    }
    else {
        do {
            sum += tmp->worth; // Add the net worth of the current tmp(node)
            tmp = tmp->next;  // Move to the next tmp(node)
        } while (tmp != head); // Continue until we return to the head
    }

    return sum; // Returns the sum
}
// sum END