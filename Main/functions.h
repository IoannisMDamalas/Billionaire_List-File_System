//struct mydate START
typedef struct {

    int year;   //the year of the birth date
    int month;  //the month of the birth date
    int day;    //the day of the birth date

}mydate;
//struct mydate END

//struct mytime START
typedef struct {

    int hour;       //the hour of the birth time
    int minutes;    //the minutes of the birth time

}mytime;
//struct mytime END

//struct billList/billionaire START
typedef struct billList {

    char *name;         //the name of the billionaire
    char *pOrigin;      //the place of origin of the activity of the billionaire
    char *activity;     //the activity of the billionaire
    char *bPlace;       //the birthplace of the billionaire
    char gender;        //the gender of the billionaire
    mydate birthdate;   //the day/month/year of the birth date of the billionaire
    mytime birthtime;   //the hour:minutes of the birth time of the billionaire
    float worth;        //the worth of the billionaire

    char *bankC;        //the bank code of the billionaire

    struct billList *next;      //pointer to the next node
    struct billList *prev;      //pointer to the previous node

}billionaire;
//struct billList/billionaire END

//Variables



//User Created Functions Names

billionaire *newNode(char na[], char plO[], char act[], char bPl[], char gen, mydate biD, mytime biT, float wo, char baC[]);
void *newBill(billionaire **head, char na[], char plO[], char act[], char bPl[], char gen, mydate biD, mytime biT, float wo, char baC[]);
void deleteN(billionaire **head);
void deleteO(billionaire **head);
void printList(billionaire *head);
void printGreater(billionaire *head, char mon[]);
void printLess(billionaire *head, char mon[]);
void printEqual(billionaire *head, char mon[]);
void saveFile(billionaire *head, FILE *f, char fn[]);
void loadFile(billionaire *head, FILE *f, char fn[], int size);
void instructions(void);
void findN(billionaire *head, char needle[]);
void findC(billionaire *head, char needle[]);
void findS(billionaire *head, char needle[]);
int bankCode(void);
int checksum(char baC[]);
float sum(billionaire *head);
