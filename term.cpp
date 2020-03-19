#include <cstdlib>
#include <windows.h>
#include <cstdio>

int main() {
    // Terminate the rollcall clicker in case of emergency.
    // Recommended on the task bar.
    std::printf("Terminating rollcall.exe and jumpstart.exe.\n");
    std::system("taskkill /f /im rollcall.exe > NUL 2> NUL");
    std::system("taskkill /f /im jumpstart.exe > NUL 2> NUL");
    Sleep(500);
}