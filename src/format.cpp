#include <string>

#include "format.h"

using std::string;
using std::to_string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS or if it applies "DD days HH:MM:SS"
string Format::ElapsedTime(long seconds) { 
	int dd, hh, remaining_s, mm, ss;

	// Get days
	dd = seconds / 86400;
	remaining_s = seconds % 86400;
	// Get hours
	hh = remaining_s / 3600;
	remaining_s = remaining_s % 3600;
	// Get minutes
	mm = remaining_s / 60;
	// Get total remaining seconds
	ss = remaining_s % 60;

	if (dd == 0) {
		return to_string(hh) + ":" + to_string(mm) + ":" + to_string(ss);
	}
	else{
		return to_string(dd) + " days " + to_string(hh) + ":" + to_string(mm) + ":" + to_string(ss);
	}
	
}