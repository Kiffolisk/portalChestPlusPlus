# portalChest++
Edit Blockheads instances from rooted Android devices through ADB and /proc/

# How to:
Run "adb devices" and check if you have only 1 device connected. The program gets the first device found from "adb devices".

Make sure the device also has root and it accepts ADB shell by running adb shell -n "su 0 echo hi" and accepting the superuser prompt

# TODO:
- [ ] Figure out /proc/ editing on Android
- [ ] Optimize code, find better way to execute superuser command through ADB
- [ ] Item swap menu with a good item selector
