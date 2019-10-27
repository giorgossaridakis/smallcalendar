#include <stdio.h>
#include <time.h>
#include <string.h>
#include <iostream>

using namespace std;

int CalcDayNumFromDate(int y, int m, int d);
int isleapyear(int year);
void leavespaces(int nextday);

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

int daysinmonth[]={ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main(int argc, char *argv[])
{
  int i, m, y, d=1, day, spaces, tspace;
  char month[20];
  
  // current year and month
  time_t now = time(0);
  tm *ltm = localtime(&now);
  y=1900 + ltm->tm_year;
  m=ltm->tm_mon;
//   d=ltm->tm_mday;
  
  // if argument parameters are given, disregard current calendar
  if (argc>2) {
   strcpy(month, argv[1]);
   y=atoi(argv[2]);
   if (atoi(month))
    m=atoi(month)-1; 
   else {
    m=-1;
    month[0]=toupper(month[0]);
    for (i=1;i<strlen(month);i++)
     month[i]=tolower(month[i]); 
    for (i=0;i<12;i++)
     if (!strcmp(month, months[i]))
    m=i; }
    if (m>11 || m<0 || y<1) {
     cout << "invalid month/year!" << endl;
   exit(0); } }
   
   // printout calendar
   daysinmonth[1]+=isleapyear(y);
   cout << "                       " << months[m] << " " << y << endl;
   cout << "     Sun     Mon     Tue     Wed     Thu     Fri     Sat" << endl;
   day=CalcDayNumFromDate(y, m+1, d);
   if (day>3)
    spaces=7+((day-4)*8);
   else
    spaces=31+((day)*8);
   leavespaces(spaces);
   for (i=d;i<daysinmonth[m]+1;i++) {
    tspace=(d>9) ? 1 : 0;
    if (d>1) // first day has already enough spaces
     leavespaces(7-tspace);
    cout << d;
    day=CalcDayNumFromDate(y, m+1, d);
    if (day==3) // next line after Saturday
     cout << endl; 
   ++d; }

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
  if( (year%400==0 || year%100!=0) &&(year%4==0)) // is a leap year
   return 1;

 return 0;
}

// leave spaces
void leavespaces(int spaces)
{
  int i;
  
   for (i=0;i<spaces;i++)
    cout << " ";
}
