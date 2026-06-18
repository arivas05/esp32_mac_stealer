#pragma once
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <unistd.h>    
#include <cstdio>   

//#define WIFI_INTERFACE "wlan0" 

std::string identify_os(void);
bool download_package(std::string package);
std::string grab_my_mac(std::string &interfaceName);
void dhclient(std::string &interfaceName);