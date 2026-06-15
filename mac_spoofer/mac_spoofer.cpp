#include <stdio.h> 
#include "get_mac.hpp"
#include "linux.hpp"

int main(int argc, char* argv[]) { 
    const char* macfilename = "output.txt"; 

    std::fstream fptr(macfilename);

    if (geteuid() != 0) {
        std::cerr << "Please run as root (use sudo)" << std::endl;
        return 1;
    }

    std::string my_mac_address = grab_my_mac();
    while(true){
        if (!validAddress(my_mac_address)) {
        std::cerr << "[-] Invalid MAC address format." << std::endl;
        std::cout << "input a valid MAC address" << std::endl;
        std::cin >> my_mac_address;
        } else {
            std::cout << "valid MAC address" << std::endl; break;
        }
    }


    std::string macAddress;
    std::string action, interfaceName;

    while (std::getline(fptr, macAddress)) {
        if (!parseArguments(argc, argv, action, interfaceName, macAddress)) {
            printUsage(argv[0]);
            return 1;
        }

        if (action == "-r") {
            resetNIC(interfaceName);
        } else if (action == "-s") {
            if (!validAddress(macAddress)) {
                std::cerr << "[-] Invalid MAC address format." << std::endl;
                printUsage(argv[0]);
                return 1;
            }
            setMACAddress(interfaceName, macAddress);
        }

        std::cout << "Press Enter to change to the next MAC address...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    fptr.close();
    setMACAddress(interfaceName, my_mac_address);
    return 0;
}