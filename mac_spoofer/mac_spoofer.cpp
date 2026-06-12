#include <stdio.h>
#include <linux.hpp>
#define size 17

int main (void){
    const char macfilename = "output.txt";
    FILE *mfn_fp = fopen(macfilename, "r");

    if(!mfn_fp){
        perror("File not found...\n");
        return 1;
    }

    char mac_address[size];
    while (fscanf(mfn_fp, "%17s", mac_address) == 1){
        std :: string action, interfaceName;
        std :: string macAddress(mac_address);
    if (!parseArguments(argc, argv, action, interfaceName, macAddress)) {
        printUsage(argv[0]);
        return 1;
    }
    if (action == "-r") resetNIC(interfaceName);
    else if (action == "-s") {
        if (!validAddress(macAddress)) {
            cerr << "[-] Invalid MAC address format." << endl;
            printUsage(argv[0]);
            return 1;
        }
        setMACAddress(interfaceName, macAddress);
    }
    // I hope this works and is good enough
    std::cout << "Press Enter to change to the next MAC address...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    }
    fclose(mfn_fp);
    return 0;
}