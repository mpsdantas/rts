#include <iostream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(){
  time_t currentTime;
  struct tm timeOfBith;
  int year, month ,day;
  double seconds;
  
  cout << "year?";
  cin >> year;
  cout << "month?";
  cin >> month;
  cout << "day?";
  cin >> day;

  time(&currentTime);

  timeOfBith.tm_hour = 0;   
  timeOfBith.tm_min = 0; 
  timeOfBith.tm_sec = 0;
  timeOfBith.tm_year = year - 1900; 
  timeOfBith.tm_mon = month - 1; 
  timeOfBith.tm_mday = day;

  seconds = difftime(currentTime, mktime(&timeOfBith));

  cout << "Seconds lived: " << seconds << endl;
  


}