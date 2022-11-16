#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ncurses.h>
#include <iostream>
#include <fstream>

class Shell {
    public:
        static void cmd(std::string comd) {
            std::string finalCmd = "adb shell -n \"su 0 ";
            finalCmd += comd;
            finalCmd += "\"";
            // printf(finalCmd.c_str());
            system(finalCmd.c_str());
        };
        static void cmd(std::string comd, std::string out) {
            std::string finalCmd = "adb shell -n \"su 0 ";
            finalCmd += comd;
            finalCmd += "\" > " + out;
            // printf(finalCmd.c_str());
            system(finalCmd.c_str());
        };
};

struct PortalChestItem {
    uint8_t count;
    int itemIndex;
};