// small calendar
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define SPACES 7 // spaces between printed days, from 3 to 10

int CalcDayNumFromDate(int y, int m, int d);
int isleapyear(int year);
void leavespaces(int nextday);
char *firstthreeletters(const char *source);

const char *daysofweek[] = { 
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday",
    "Monday",
    "Tuesday"
};

const char *months[]= {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

int main(int argc, char *argv[])
{
  int i, m=-1, y, d=1, day, spaces, daysinmonth;
  char month[20];
  time_t now = time(0);
  struct tm *ltm = localtime(&now);
  int thismonth=ltm->tm_mon, thisyear=1900+ltm->tm_year, today=ltm->tm_mday;
  
  // if argument parameters are given, disregard current calendar
  if (argc==3) {
   strcpy(month, argv[1]);
   y=atoi(argv[2]);
   if (atoi(month))
    m=atoi(month)-1; 
   else {
    month[0]=toupper(month[0]);
    for (i=1;i<3;i++)
     month[i]=tolower(month[i]); 
    month[i]='\0';
    for (i=0;i<12;i++)
     if (!strcmp(month, firstthreeletters(months[i])))
    m=i; } }
    // if something is wrong with parameters, use current calendar
    if (m>11 || m<0 || y<1) {
     y=thisyear;
    m=thismonth; }   
   // printout calendar
   leavespaces((SPACES*3)-2);
   printf("%s %d\n", months[m], y);
   for (i=4;i<7;i++) {
    leavespaces(SPACES-3);
   printf("%s", firstthreeletters(daysofweek[i])); }
   for (i=0;i<4;i++) {
    leavespaces(SPACES-3);
   printf("%s", firstthreeletters(daysofweek[i])); }
   printf("\n");
   day=CalcDayNumFromDate(y, m+1, d);
   if (day>3)
    spaces=(day-4)*SPACES;
   else
    spaces=(SPACES*3)+((day)*SPACES);
   leavespaces(spaces);
   daysinmonth=(m==1) ? (28 + isleapyear(y)) : 31 - m % 7 % 2;
   for (i=d;i<daysinmonth+1;i++) {
    spaces=(d>9) ? 1 : 0;
    leavespaces((SPACES-1)-spaces);
    if (d==today && m==thismonth && y==thisyear)
     printf("\e[47m\e[30m%d\e[0m", d);
    else
     printf("%d", d);
    day=CalcDayNumFromDate(y, m+1, d);
    if (day==3) // next line after Saturday
     printf("\n");
   ++d; }
   printf("\n");

 return 0;
}

// ----------------------------------------------------------------------
// Given the year, month and day, return the day number.
// (see: https://alcor.concordia.ca/~gpkatch/gdate-method.html)
// ----------------------------------------------------------------------
int CalcDayNumFromDate(int y, int m, int d)
{
  m = (m + 9) % 12;
  y -= m / 10;
  int dn = 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1);

  return dn % 7;
}

// return 1 if year is leap
int isleapyear(int year)
{ 
  if ((year%400==0 || year%100!=0) && (year%4==0)) // is a leap year
   return 1;

 return 0;
}

// leave spaces
void leavespaces(int spaces)
{
  int i;
  
   for (i=0;i<spaces;i++)
    putchar(' ');
}

// first 3 letters
char *firstthreeletters(const char *source)
{
  int i;
  static char dest[3];
  
   for (i=0;i<3;i++)
    dest[i]=source[i];
   dest[i]='\0';
   
  return &dest[0];
}
