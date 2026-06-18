#include <stdio.h> 
#include "get_mac.hpp"
#include "linux.hpp"

int main(int argc, char* argv[]) { 
    const char* macfilename = "output.txt"; 
    bool check = false;
    std::fstream fptr(macfilename);

    if (geteuid() != 0) {
        std::cerr << "Please run as root (use sudo)" << std::endl;
        return 1;
    }



    std::string action,interfaceName,macAddress,my_mac_address;

    while (std::getline(fptr, macAddress)) {
        if (!parseArguments(argc, argv, action, interfaceName)) {
            printUsage(argv[0]);
            return 1;
        }

        if (action == "-r") {
            resetNIC(interfaceName);
            return 0;
        } else if (action == "-s") {
            if(!check){
                my_mac_address = grab_my_mac(interfaceName);
                while(!check){
                    if (!validAddress(my_mac_address)) {
                        std::cerr << "[-] Invalid MAC address format." << std::endl;
                        std::cout << "input a valid MAC address" << std::endl;
                        std::cin >> my_mac_address;
                    } else {
                        std::cout << "valid MAC address" << std::endl; break;
                    }
                }
                check = true;
            }

            std::string mac = "00:00:00:00:00:00";
            for(int i = 0; i<=17; i+=1){
                mac[i] = macAddress[i];
            }


            if (!validAddress(mac)) {
                std::cerr << "[-] Invalid MAC address format." << std::endl;
                printUsage(argv[0]);
                return 1;
            }
            cout << macAddress << " is being used" << endl;
            setMACAddress(interfaceName, mac);
        }

        std::cout << "Press Enter to change to the next MAC address...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    fptr.close();
    setMACAddress(interfaceName, my_mac_address);
    std::string cmd = "sudo dhclient" + interfaceName;
    system(cmd.c_str());
    return 0;
}