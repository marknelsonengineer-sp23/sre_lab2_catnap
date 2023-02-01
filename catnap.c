///////////////////////////////////////////////////////////////////////////////
//          University of Hawaii, College of Engineering
//          Lab 2 - Catnap - SRE - Spring 2023
//
/// The intent of this program is to:
///    - Remember everything you've forgotten about programming
///    - Write a simple algorithm in C
///    - Work with structs
///    - Research API calls
///
/// Compile: $ clear && make test
///
/// Makefile Targets
///    | Command        | Result                                     |
///    |----------------|--------------------------------------------|
///    | `$ make`       | will compile your program                  |
///    | `$ make test`  | will compile your program and then run it. |
///    | `$ make debug` | will compile with debug mode               |
///    | `$ make clean` | will remove any unnecessary files          |
///
/// Example:
///   $ ./catnap
///   Reference time: Thu May  4 22:41:00 2000
///   
///   Years: 22  Days: 277  Hours:  9  Minutes: 59  Seconds: 57 
///   Years: 22  Days: 277  Hours:  9  Minutes: 59  Seconds: 58 
///   Years: 22  Days: 277  Hours:  9  Minutes: 59  Seconds: 59 
///   Years: 22  Days: 277  Hours: 10  Minutes:  0  Seconds:  0 
///   Years: 22  Days: 277  Hours: 10  Minutes:  0  Seconds:  1 
///   Years: 22  Days: 277  Hours: 10  Minutes:  0  Seconds:  2 
///   Years: 22  Days: 277  Hours: 10  Minutes:  0  Seconds:  3 
///
/// @file    catnap.c
/// @author  Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>    // For printf()
#include <unistd.h>   // For sleep()
#include <time.h>     // For time(), mktime(), asctime(), difftime()
#include <stdlib.h>   // For exit(), labs(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h>   // For memset()

const int REFERENCE_YEAR   = 2000;
const int REFERENCE_MONTH  =   05;    // Jan = 01, Feb = 02, ... Dec = 12
const int REFERENCE_DAY    =   04;    // Day of the month
//const int REFERENCE_HOUR   =   02;    // On a 24-hour clock
//const int REFERENCE_MINUTE =   12;
const int REFERENCE_HOUR   =   22;    // On a 24-hour clock
const int REFERENCE_MINUTE =   41;

const int secondsInMinute  = 60;
const int secondsInHour    = secondsInMinute *  60;
const int secondsInDay     = secondsInHour   *  24;
const int secondsInYear    = secondsInDay    * 365;


/// Start with the input parameter differenceInSeconds
///
/// Figure out how many whole years are in the seconds (put in differenceInYears)
///
/// Then, subtract that many years from the differenceInSeconds
///
/// Repeat for Days, Hours and Minutes
///
/// labs :: long absolute value (from stdlib.h)
void printDifference( double differenceInSeconds ) {
   // printf ("%lf\n", differenceInSeconds);

   /// How many whole years are in differenceInSeconds?
   long differenceInYears    = (long) differenceInSeconds / secondsInYear;
        differenceInSeconds -=        differenceInYears   * secondsInYear;  // Remove whole number of years

   /// How many whole days are left in differenceInSeconds?
   long differenceInDays     = (long) differenceInSeconds / secondsInDay;
        differenceInSeconds -=        differenceInDays    * secondsInDay;   // Remove whole number of days

   /// How many whole hours are left in differenceInSeconds?
   long differenceInHours    = (long) differenceInSeconds / secondsInHour;
        differenceInSeconds -=        differenceInHours   * secondsInHour;  // Remove whole number of hours

   /// How many whole minutes are left in differenceInSeconds?
   long differenceInMinutes  = (long) differenceInSeconds / secondsInMinute;
        differenceInSeconds -=        differenceInMinutes * secondsInMinute;// Remove whole number of minutes

   printf ("Years: %2ld  Days: %2ld  Hours: %2ld  Minutes: %2ld  Seconds: %2ld \n"
      ,labs( differenceInYears )
      ,labs( differenceInDays )
      ,labs( differenceInHours )
      ,labs( differenceInMinutes )
      ,labs( (long) differenceInSeconds ));
}


int main() {

   time_t referenceTime = -1;

   struct tm reference;

   memset( &reference, 0, sizeof( reference ));

   reference.tm_year = REFERENCE_YEAR - 1900;  ///< Per the spec:  "Year - 1900"
   reference.tm_mon  = REFERENCE_MONTH - 1;    ///< Jan=0 ... May=4
   reference.tm_mday = REFERENCE_DAY;
   reference.tm_hour = REFERENCE_HOUR;
   reference.tm_min  = REFERENCE_MINUTE;

   // Convert the tm structure into epoch time
   referenceTime = mktime( &reference );

   if( referenceTime == -1 ) {
      printf ("Can't make a reference time.  Exiting.\n" );
      exit(EXIT_FAILURE);
   }

   printf("Reference time: %s\n", asctime(&reference));

   time_t currentTime;
   double differenceInSeconds;

   while (1) {
      currentTime = time(NULL);

      differenceInSeconds = difftime( referenceTime, currentTime );

      printDifference( differenceInSeconds );

      // Wait for 1 second
      sleep(1);
   }

   return EXIT_SUCCESS;
}
