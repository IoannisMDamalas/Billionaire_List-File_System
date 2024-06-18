// struct mydate START
typedef struct {

    int year;   // the year of the birth date
    int month;  // the month of the birth date
    int day;    // the day of the birth date

}mydate;
// struct mydate END

// struct mytime START
typedef struct {

    int hour;       // the hour of the birth time
    int minutes;    // the minutes of the birth time

}mytime;
// struct mytime END

// struct billList/billionaire START
typedef struct billList {

    char *name;         // the name of the billionaire
    char *pOrigin;      // the place of origin of the activity of the billionaire
    char *activity;     // the activity of the billionaire
    char *bPlace;       // the birthplace of the billionaire
    char gender;        // the gender of the billionaire
    mydate birthdate;   // the day/month/year of the birth date of the billionaire
    mytime birthtime;   // the hour:minutes of the birth time of the billionaire
    float worth;        // the worth of the billionaire

    char *bankC;        // the bank code of the billionaire

    struct billList *next;      // pointer to the next node
    struct billList *prev;      // pointer to the previous node

}billionaire;
// struct billList/billionaire END

// Defines
#define RESET           "\x1b[0m"
#define BLACK           "\x1b[30m"
#define RED             "\x1b[31m"
#define GREEN           "\x1b[32m"
#define YELLOW          "\x1b[33m"
#define BLUE            "\x1b[34m"
#define MAGENTA         "\x1b[35m"
#define CYAN            "\x1b[36m"
#define WHITE           "\x1b[37m"
#define BRIGHT_BLACK    "\x1b[90m"
#define BRIGHT_RED      "\x1b[91m"
#define BRIGHT_GREEN    "\x1b[92m"
#define BRIGHT_YELLOW   "\x1b[93m"
#define BRIGHT_BLUE     "\x1b[94m"
#define BRIGHT_MAGENTA  "\x1b[95m"
#define BRIGHT_CYAN     "\x1b[96m"
#define BRIGHT_WHITE    "\x1b[97m"


// User Created Functions Names

billionaire *newNode(char na[], char plO[], char act[], char bPl[], char gen, mydate biD, mytime biT, float wo, char baC[]);
void *newBill(billionaire **head, char na[], char plO[], char act[], char bPl[], char gen, mydate biD, mytime biT, float wo, char baC[]);
void deleteN(billionaire **head);
void deleteO(billionaire **head);
void deleteA(billionaire **head);
void printA(billionaire *head);
void printGreater(billionaire *head, char mon[]);
void printLess(billionaire *head, char mon[]);
void printEqual(billionaire *head, char mon[]);
void saveFile(billionaire *head, FILE *f, char fn[]);
void loadFile(billionaire *head, FILE *f, char fn[], int size);
void instructions(void);
void findN(billionaire *head, char needle[]);
void findC(billionaire *head, char needle[]);
void findS(billionaire *head, char needle[]);
void findG(billionaire *head, char gnd);
void generateRandomDigits(char *accountNumber, int length);
void generateAccountNumber(char *accountNumber);
void normalizeBilName(char *name);
void replaceUnknown(char *str);
int calculateCheckDigit(const char *accountNumber);
float sum(billionaire *head);