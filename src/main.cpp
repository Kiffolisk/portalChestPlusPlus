#include "../include/global.hpp"

void refreshScreen() {
    erase();
    move(0, 0);
    addstr("portalChest++ - Now with USB /proc/ editing!\nPress # to exit program\n\n");
}

bool devicesFound = false;
bool gameFound = false;
std::string procID = "";
std::string packageName = "";
std::string mPackageName = "";

int main() {
    int ch;
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    system("adb devices > devices.out");
    std::ifstream devices;
    devices.open("devices.out");
    if (devices.is_open()) {
        std::string line;
        while (std::getline(devices, line)) {
            /*addstr("\"");
            addstr(line.c_str());
            addstr("\"\n");*/
            if (line.find("\tdevice") != std::string::npos) {
                devicesFound = true;
            }
        }
    }
    refreshScreen();
    if (!devicesFound) {
        refresh();
        endwin();
        printf("No devices found through ADB! Please connect your Android device to the computer.\n");
        return 0;
    }else {
        addstr("Found devices through ADB! /proc/ editing will be allowed\n");
    }
    devices.close();
    remove("devices.out");
    addstr("\nThe Blockheads package name (defaults to com.noodlecake.blockheads): ");
    int y, x;
    getyx(stdscr, y, x);
    Shell::cmd("ps", "ps.out");
    while ((ch = getch()) != '#') {
        switch(ch) {
            case KEY_BACKSPACE:
                if (mPackageName.length() - 1 >= 0) {
                    mPackageName = mPackageName.substr(0,mPackageName.length()-1);
                    move(y, x);
                    clrtoeol();
                    addstr(mPackageName.c_str());
                }
                break;
            case '\n':
                if (packageName == "") {
                    if (mPackageName.length() > 0) {
                        packageName = mPackageName;
                    } else {
                        packageName = "com.noodlecake.blockheads";
                    }
                    std::ifstream ps;
                    ps.open("ps.out");
                    if (ps.is_open()) {
                        std::string line;
                        while (std::getline(ps, line)) {
                            if (line.find(packageName) != std::string::npos) {
                                gameFound = true;
                                int spacesFound = 0;
                                for (int i = 0; i < line.length(); i++) {
                                    if (line.c_str()[i] == ' ') {
                                        if (procID != "") {
                                            break;
                                        }
                                        spacesFound++;
                                    }
                                    if (std::string("0123456789").find(line.c_str()[i]) != std::string::npos && spacesFound >= 1) {
                                        procID += line.c_str()[i];
                                    }
                                }
                                /*std::string x = "[-] LINE ";
                                x += std::to_string(i);
                                x += ": YES\n";
                                printf(x.c_str());*/
                                break;
                            }/*else{
                                std::string x = "[-] LINE ";
                                x += std::to_string(i);
                                x += ": NO\n";
                                printf(x.c_str());
                            }*/
                        }
                    }
                    ps.close();
                    move(y, 0);
                    // clrtoeol();
                    if (!gameFound) {
                        refresh();
                        endwin();
                        printf("Package not running! Please start the game or make sure you typed the right package name\n");
                        return 0;
                    }else{
                        addstr("Found game! You can now mess around\n");
                        addstr("Found process ID! ");
                        addstr(procID.c_str());
                    }
                } else {
                    if (procID != "") {
                        std::string copyMaps = "cat /proc/";
                        copyMaps += procID;
                        copyMaps += "/smaps";
                        Shell::cmd(copyMaps, "maps.out");
                    }
                }
                break;
            default:
                if (packageName == "") {
                    mPackageName += ch;
                    move(y, x);
                    clrtoeol();
                    addstr(mPackageName.c_str());
                }
                break;
        }
    }
    refresh();
    endwin();
    return 0;
}