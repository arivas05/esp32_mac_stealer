#include "get_mac.hpp"
   

const char* ios_filename = "identifyos.txt";
const char* ico_filename = "ipconfigoutput.txt";

std::string identify_os(void) {
    bool os_identified = false;   
    std::fstream ios_file(ios_filename); 


    system("cat /etc/os-release > identifyos.txt");

    std::string os;
    while (std::getline(ios_file, os)) { 
        if (os.find("arch") != std::string::npos)       { os_identified = true; os = "arch"; break; }
        else if (os.find("debian") != std::string::npos) { os_identified = true; os = "debian"; break; }
        else if (os.find("ubuntu") != std::string::npos) { os_identified = true; os = "ubuntu"; break; }
        else if (os.find("Red Hat") != std::string::npos){ os_identified = true; os = "red hat"; break; }
        else if (os.find("fedora") != std::string::npos) { os_identified = true; os = "fedora"; break; }
        else if (os.find("centos") != std::string::npos) { os_identified = true; os = "centos"; break; }
    }

    if (!os_identified) os = "unidentified";
    ios_file.close();
    std::cout<<os<<std::endl;
    return os;
}

bool download_net_tools(void) {
    std::string os = identify_os();
    if (os == "arch") {
        system("sudo pacman -Syu");
        system("sudo pacman -S net-tools");
    } else if (os == "debian" || os == "ubuntu") {
        system("sudo apt update && sudo apt upgrade -y");
        system("sudo apt install -y net-tools");
    } else if (os == "red hat" || os == "fedora" || os == "centos") {
        system("sudo dnf check-update && sudo dnf upgrade -y");
        system("sudo dnf install -y net-tools");
    } else {
        std::cout << "os unidentifiable"<<std::endl;
        return false;
    }
    return true;
}

std::string grab_my_mac(std::string &interfaceName) {
    bool ret = false;
    if (system("which ifconfig > /dev/null 2>&1") != 0) { 
        ret = download_net_tools();
    } else {
        ret = true;
    }

    if (!ret) { return ""; } 
    std::string cmd = "ifconfig " + interfaceName + " > " + ico_filename;
    system(cmd.c_str());
    


    std::fstream ico(ico_filename);
    std::string mac;
    while (std::getline(ico, mac)) {  
        if (mac.find("ether") != std::string::npos) {
            
            size_t pos = mac.find("ether");
            mac = mac.substr(pos + 6);
            size_t end = mac.find(' ');
            if (end != std::string::npos) mac = mac.substr(0, end);
            break;
        }
    }
    ico.close();
    return mac;
}