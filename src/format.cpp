#include <string>

#include "format.h"

using std::string;
using std::to_string;

// Done: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
	int hh, remaining_s, mm, ss;

	hh = seconds / 3600;
	remaining_s = seconds % 3600;
	mm = remaining_s / 60;
	ss = remaining_s % 60;

	return to_string(hh) + ":" + to_string(mm) + ":" + to_string(ss);
}