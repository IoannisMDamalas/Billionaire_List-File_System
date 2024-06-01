#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define name "project2-data.csv"



typedef struct
{
    int year;
    int month;
    int day;
}date;

typedef struct
{
    int hour;
    int minutes;
}time;

typedef struct
{
    char sName[20];
    char lName[20];
    char pOrigin[20];
    char activity[20];
    char bPlace[20];
    char gender;
    date birthdate; 
    time birthtime;
    float worth;
}info;


typedef struct billList
{
    info bilinfo;
    struct bilList *next; 
    struct bilList *prev;
    
}billionaire;

billionaire newBill();
billionaire deleteN();
billionaire deleteO();



int main(void)
{
    int d;
    char input[100];

    printf("Welcome!\n");
    printf("$> ");
    scanf("%s",input);
    if ((strcmp(input,"exit") == 0) || (strcmp(input,"EXIT") == 0))
    {
        printf("Exiting program...\n");
        exit(1);
    }

    return 0;
}

void putEnd(struct billList )