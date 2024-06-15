//Function Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "functions.h"

//User Created Functions Bodies

//newNode START
billionaire *newNode(char na[], char plO[], char act[], char bPl[], char gen, mydate biD, mytime biT, float wo, char baC[]) {

    billionaire *node;  //Pointer to billionaire struct
    
    node = (billionaire*)malloc(sizeof(billionaire));     //Allocates memory with the use of malloc()

    if (node == NULL) {
        printf("Error! Could not allocate memory!\n");
    }

    //Puts the new billionaire data into the corresponding variables on the billionaire node
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

    //keeps the list circular and double linked
    node->next = node;
    node->prev = node;

    return node;    //returns the new node
}
//newNode END

//newBill START
void *newBill(billionaire **head, char na[], char plO[], char act[], char bPl[], char gen, mydate biD, mytime biT, float wo, char baC[]) {

    billionaire *newBillionaire, *last;     //2 pointers to the billionaire struct
    
    newBillionaire = newNode(na, plO, act, bPl, gen, biD, biT, wo, baC);    //calls the function newNode and returns the new node to newBillionaire

    if (*head == NULL) {        //checks if the list head is equal to NULL
        *head = newBillionaire; //if it is, it means that the new node is the first node of the list and makes it the head
    }
    else {                              //if not, it inserts the new node to the end of the list
        last = (*head)->prev;           //last is equal to the previous node of the head of the list
        last->next = newBillionaire;    //the next node of last is equal to newBillionaire
        newBillionaire->prev = last;    //the previous node of newBillionaire is equal to last
        newBillionaire->next = *head;   //the next node of newBillionaire is equal to the head of the list
        (*head)->prev = newBillionaire; //the previous node of the head of the list is equal to newBillionaire
    }

    printf("\nNew billionaire succesfully inserted to the list.\n\n");

    //returns nothing because the function is void
}
//newBill END

//deleteN START
void deleteN(billionaire **head) {
    billionaire *lst, *slst; //pointers to the last node of the list and second last of the list accordingly

    if ((*head) == NULL) {                  //checks if the head of the list is equal to NULL
        printf("\nThe list is empty.\n\n");     //if it is, then it informs the user that the list is empty

        return;     //returns nothing because the function is void
    }

    //if not, then:

    lst = (*head)->prev;    //makes the last nod same as the previous node of the head of the list

    if (lst == (*head)) {   //checks if the last node is equal to the head of the list
        free(lst);          //if it is, it means that the list has only one node and it frees the allocated memory
        (*head) = NULL;     //now the head of the list is equal to NULL
    }
    else {                     //else, the list has more than 1 nodes
        slst = lst->prev;      //it makes the second last node equal to the previous node of the last node 
        slst->next = (*head);  //it makes the next node of the second last node equal to the head of the list
        (*head)->prev = slst;  //it makes the previous node of the head of the list equal to the second last node
        free(lst);             //it frees the allocated memory for the last node of the list
    }

    return;   //returns nothing because the function is void

}
//deleteN END

//deleteO START
void deleteO(billionaire **head) {
    billionaire *fst, *snd, *lst;   //pointers to the first, second and last node of the list accordingly

    if ((*head) == NULL) {                    //checks if the head of the list is equal to NULL
        printf("\nThe list is empty.\n\n");   //if it is, the user is informed that the list is empty

        return;                         //returns nothing because the function is void
    }

    fst = (*head);                      //makes the first node the same as the head of the list
    lst = fst->prev;                    //makes the last node the same as the previous of the first node

    if (fst == lst) {                   //checks if the first node is equal to the last node
        free(fst);                      //if it is, it means that the list has only one node and it frees the allocated memory
        (*head) = NULL;                 //makes the head of the list equal to NULL
    }
    else {                              //else, the list has more than 1 node
        snd = fst->next;                //makes the second node the same as the next of the first node
        lst->next = snd;                //makes the next of the last node the same as the second node
        snd->prev = lst;                //makes the previous of the second node the same as the last node
        free(fst);                      //it frees the allocated memory for the first node of the list
        (*head) = snd;                  //makes the head of the list equal to the second node
    }

    return;                             //returns nothing because the function is void
}
//deleteO END

//printList START
void printList(billionaire *head) {
    billionaire *tmp;  //a temporary pointer to the struct billionaire

    if (head == NULL) { //checks if the head is equal to NULL
        printf("\nThe list is empty.\n\n");     //if it is, then it informs the user that the list is empty

        return;
    }

    //if not
    tmp = head;  //temp is equal to the head of the list  

    //do-while loop to print all the nodes of the list
    do {
        printf("\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\nWorth: %.2f$\nBank Code: %s\n\n", tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
        tmp = tmp->next;  //moves to the next node of the list
    } while (tmp != head); //do-while condition to keep printing the next node as long as temp is not equal to the head of the list

    return;     //returns nothing because the function is void
}
//printList END

//printGreater START
void printGreater(billionaire *head, char mon[]) {
    billionaire *tmp;  //a temporary pointer to the struct billionaire
    float worth;
    int flag = -1;

    if (head == NULL) { //checks if the head is equal to NULL
        printf("\nThe list is empty.\n\n");     //if it is, then it informs the user that the list is empty

        return;
    }

    //if not
    tmp = head;  //temp is equal to the head of the list  

    worth = atof(mon);

    //do-while loop to print all the nodes of the list
    do {
        if (worth < tmp->worth) {
            printf("\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\nWorth: %.2f$\nBank Code: %s\n\n", tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
            flag = 1;
        }
        tmp = tmp->next;  //moves to the next node of the list
    } while (tmp != head); //do-while condition to keep printing the next node as long as temp is not equal to the head of the list

    if (flag != 1) {
        printf("\nThere is not a billionaire on the list whose worth is greater than %.2f$\n\n", worth);
    }

    return;     //returns nothing because the function is void
}
//printGreater END

//printLess START
void printLess(billionaire *head, char mon[]) {
    billionaire *tmp;  //a temporary pointer to the struct billionaire
    float worth;
    int flag = -1;

    if (head == NULL) { //checks if the head is equal to NULL
        printf("\nThe list is empty.\n\n");     //if it is, then it informs the user that the list is empty

        return;
    }

    //if not
    tmp = head;  //temp is equal to the head of the list  

    worth = atof(mon);

    //do-while loop to print all the nodes of the list
    do {
        if (worth > tmp->worth) {
            printf("\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\nWorth: %.2f$\nBank Code: %s\n\n", tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
            flag = 1;
        }
        tmp = tmp->next;  //moves to the next node of the list
    } while (tmp != head); //do-while condition to keep printing the next node as long as temp is not equal to the head of the list

    if (flag != 1) {
        printf("\nThere is not a billionaire on the list whose worth is less than %.2f$\n\n", worth);
    }

    return;     //returns nothing because the function is void
}
//printLess END

//printEqual START
void printEqual(billionaire *head, char mon[]) {
    billionaire *tmp;  //a temporary pointer to the struct billionaire
    float worth;
    int flag = -1;

    if (head == NULL) { //checks if the head is equal to NULL
        printf("\nThe list is empty.\n\n");     //if it is, then it informs the user that the list is empty

        return;
    }

    //if not
    tmp = head;  //temp is equal to the head of the list  

    worth = atof(mon);

    //do-while loop to print all the nodes of the list
    do {
        if (worth == tmp->worth) {
            printf("\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\nWorth: %.2f$\nBank Code: %s\n\n", tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
            flag = 1;
        }
        tmp = tmp->next;  //moves to the next node of the list
    } while (tmp != head); //do-while condition to keep printing the next node as long as temp is not equal to the head of the list

    if (flag != 1) {
        printf("\nThere is not a billionaire on the list whose worth is equal to %.2f$\n\n", worth);
    }

    return;     //returns nothing because the function is void
}
//printEqual END

//saveFile START
void saveFile(billionaire *head, FILE *f, char fn[]) {
    billionaire *tmp;

    tmp = head;

    if (tmp == NULL) {
        printf("\nThe list is empty.\n\n");
    }
    else {
        do {
            fprintf(f, "%s;%s;%s;%s;%c;%d/%d/%d %02d:%02d;%.2f$;%s;\n", &tmp->name, &tmp->pOrigin, &tmp->activity, &tmp->bPlace, &tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
            tmp = tmp->next;
        } while (tmp != head);
        printf("\nSuccess! Data saved in \'%s\'!\n\n",fn);
    }

    return;
}
//saveFile END

//loadFile START
void loadFile(billionaire *head, FILE *f, char fn[], int size) {
    billionaire *tmp;
    int i;
    char info[200], *ptr1[7] = {NULL}, *ptr2[5] = {NULL}, n[100] = {0}, pO[100] = {0}, a[100] = {0}, bP[100] = {0}, g, bC[12] = "Hello";
    mydate bd;  //mydate variable for birth date
    mytime bt;  //mytime variable for birth time
    float w;

    tmp = head;
    
    for (i = 0 ; i < size ; i++) {
        if (feof(f)) {
            printf("\nThe file is empty.\n\n");

            return;
        }
        else {
            
            fgets(info, sizeof(info), f);
            puts(info);

            ptr1[0]=strtok(info,";");   //divides the string with the token ';'

            if(ptr1[0] == NULL) {
                printf("\nNo info detected.\n\n");
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

            newBill(&tmp, n, pO, a, bP, g, bd, bt, w, bC);     //Calls the function newBill and inserts a new billionaire into the double linked circular list 

            tmp = tmp->next;
        }
    }
    
    printf("\nSuccess! Data Loaded in list!\n\n");

    return;
}
//loadFile END

//instructions START
void instructions(void) {
    printf("Available Commands:\n");
    printf("    1. $> newbil Name;OriginOfActivity;Activity;BirthPlace;Gender;Day/Month/Year Hour:Minutes;Worth$;\n");
    printf("    2. $> sum\n");
    printf("    3. $> findN/findC/findS\n");
    printf("    4. $> print+/print-/print=/printL\n");
    printf("    5. $> deleteN/deleteO\n");
    printf("    6. $> save \'file_name\'.txt\n");
    printf("    7. $> load \'size\' \'file_name\'.txt   \'Not Functional\'\n");
    printf("    8. $> exit\n\n");

    return;
}
//instructions END

//findN START
void findN(billionaire *head, char needle[]) {
    billionaire *tmp;
    char *res1, *res2, *fUpper, *fLower;
    int flag = -1;

    tmp = head;

    if (tmp == NULL) {
        printf("\nThe list is empty.\n\n");
    }
    else {
        fUpper = strdup(needle);
        fUpper[0] = toupper(needle[0]);

        fLower = strdup(needle);
        fLower[0] = tolower(needle[0]);
        do {
            res1 = strstr(tmp->name, fUpper);
            res2 = strstr(tmp->name, fLower);

            if ((res1 != NULL) || (res2 != NULL)) {
                printf("\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\nWorth: %.2f$\nBank Code: %s\n\n", tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
                flag = 1;
            }

            tmp = tmp->next;
        } while (tmp != head);
        
    }

    if (flag != 1) {
        printf("\nThere is not a billionaire on the list with the string \'%s\' in their name.\n\n", needle);
    }

    return;
}
//findN END

//findC START
void findC(billionaire *head, char needle[]) {
    billionaire *tmp;
    char *res1, *res2, *res3, *res4, *fUpper, *fLower;
    int flag = -1;

    tmp = head;

    if (tmp == NULL) {
        printf("\nThe list is empty.\n\n");
    }
    else {
        fUpper = strdup(needle);
        fUpper[0] = toupper(needle[0]);

        fLower = strdup(needle);
        fLower[0] = tolower(needle[0]);
        do {
            res1 = strstr(tmp->pOrigin, fUpper);
            res2 = strstr(tmp->pOrigin, fLower);
            res3 = strstr(tmp->bPlace, fUpper);
            res4 = strstr(tmp->bPlace, fLower);

            if ((res1 != NULL) || (res2 != NULL) || (res3 != NULL) || (res4 != NULL)) {
                printf("\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\nWorth: %.2f$\nBank Code: %s\n\n", tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
                flag = 1;
            }

            tmp = tmp->next;
        } while (tmp != head);
        
    }

    if (flag != 1) {
        printf("\nThere is not a billionaire on the list with the string \'%s\' in their City/Country - Birthplace.\n\n", needle);
    }

    return;
}
//findC END

//findS START
void findS(billionaire *head, char needle[]) {
    billionaire *tmp;
    char *res1, *res2, *fUpper, *fLower;
    int flag = -1;

    tmp = head;

    if (tmp == NULL) {
        printf("\nThe list is empty.\n\n");
    }
    else {
        fUpper = strdup(needle);
        fUpper[0] = toupper(needle[0]);

        fLower = strdup(needle);
        fLower[0] = tolower(needle[0]);
        do {
            res1 = strstr(tmp->activity, fUpper);
            res2 = strstr(tmp->activity, fLower);

            if ((res1 != NULL) || (res2 != NULL)) {
                printf("\nName:%s\nOrigin: %s\nActivity: %s\nBirth Place: %s\nGender: %c\nBirthday: %d/%d/%d %02d:%02d\nWorth: %.2f$\nBank Code: %s\n\n", tmp->name, tmp->pOrigin, tmp->activity, tmp->bPlace, tmp->gender, tmp->birthdate.day, tmp->birthdate.month, tmp->birthdate.year, tmp->birthtime.hour, tmp->birthtime.minutes, tmp->worth, tmp->bankC);
                flag = 1;
            }

            tmp = tmp->next;
        } while (tmp != head);
        
    }

    if (flag != 1) {
        printf("\nThere is not a billionaire on the list with the string \'%s\' in their Activity.\n\n", needle);
    }

    return;
}
//findS END


//bankCode START
int bankCode(void) {
    int random;

    random = abs(1000000000 + rand() % 9999999999);
    
    printf("A1. %d\n",random);

    return random;
}
//bankCode END

//checksum START
int checksum(char baC[]) {
    int r, l, i, num, n1, n2, sum = 0, mul;
    char n[2], m[3];

    l = strlen(baC);

    for (i = l - 1 ; i > 0 ; i -= 2) {
        num = atoi(baC + i) * 2;

        printf("B%d. %d\n", i, num); //debug

        if (num > 9) {
            sprintf(n, "%d", num);

            printf("C1. %s\n",n); //debug

            n1 = atoi(n + 0);
            n2 = atoi(n + 1);
            num = n1 + n2;

            printf("C2. %d + %d = %d\n",n1,n2,num); //debug
        }

        sprintf(baC + i, "%d", num);

        printf("D%d. %c",baC[i]); //debug
    }

    for (i = 0 ; i < l ; i++) {
        num = atoi(baC + i);

        printf("E%d. %d + %d = ",i,sum,num); //debug

        sum += num;

        printf("%d\n",sum); //debug
    }

    mul = sum * 9;

    printf("F1. %d * 9 = %d\n",sum,mul); //debug

    sprintf(m, "%d", mul);
    sum += atoi(m + 2);

    printf("sum = %d\n",sum); //debug

    if (sum % 10 == 0) {

        printf("Good!\n"); //debug

        return atoi(m + 2);
    }
    else {

        printf("Bad!\n");   //debug

        return -1;
    }
}
//checksum END

//sum START
float sum(billionaire *head) {
    billionaire *tmp;
    float sum = 0;

    tmp = head;

    if (tmp == NULL) {
        printf("\nThe list is empty!\n\n");
    }
    else {
        do {
            sum += tmp->worth;
            tmp = tmp->next;
        } while (tmp != head);
    }

    return sum;
}
//sum END

