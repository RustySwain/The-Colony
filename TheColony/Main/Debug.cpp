#include "Debug.h"
#include <iomanip>
#include <sstream>
#include "Windows.h"

void Debug::Log(string _message, unsigned int _severity)
{
	// create empty string
	string output = "";
	// add severity level
	if (_severity == 0)
		output += "INFO";
	if (_severity == 1)
		output += "WARNING";
	if (_severity == 2)
		output += "ERROR";
	// add system time in hours:minutes:seconds
	output += " [";
	auto t = time(nullptr);
	tm tm;
	localtime_s(&tm, &t);
	ostringstream oss;
	oss << put_time(&tm, "%H:%M:%S");
	output += oss.str();
	output += "] ";
	// add actual message
	output += _message;
	output += "\n";
	// print string to output window
	OutputDebugString(output.c_str());
}