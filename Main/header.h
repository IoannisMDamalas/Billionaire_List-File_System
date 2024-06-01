#define name "project2-data.csv"
#define L 50


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


typedef struct billList
{

    char *sName;
    char *lName;
    char *pOrigin;
    char *activity;
    char *bPlace;
    char gender;
    date birthdate;
    time birthtime;

    float worth;
    struct bilList *next;
    struct bilList *prev;

}billionaire;

billionaire newBill(billionaire info);
billionaire deleteN();
billionaire deleteO();
