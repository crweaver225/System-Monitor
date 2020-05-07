#include <string>
#include <iostream>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 

    long hours, minutes;
    hours = seconds/3600;
    seconds = seconds%3600;
    minutes = seconds/60;

    string hour_string = std::to_string(hours);
    string minutes_string = std::to_string(minutes);
    string seconds_string = std::to_string(seconds%60);

    try {
        hour_string.insert(0, 2 - hour_string.length(), '0');
        minutes_string.insert(0, 2 - minutes_string.length(), '0');
        seconds_string.insert(0, 2 - seconds_string.length(), '0');

        return hour_string + ":" + minutes_string + ":" + seconds_string;
    } catch (...) {
       // std::cout<<hour_string<<" "<<minutes_string<<" "<<seconds_string<<std::endl;
       return "";
    }
}