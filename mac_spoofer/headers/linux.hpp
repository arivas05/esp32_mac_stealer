#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <memory>
#include <array>
using namespace std;

string exec(const string& cmd);

bool validAddress(const string& mac);

void resetNIC(const string& interfaceName);

void setMACAddress(const string& interfaceName, const string& macAddress);

void printUsage(const char* programName);

bool parseArguments(int argc, char* argv[], string& action, string& interfaceName, string& macAddress);