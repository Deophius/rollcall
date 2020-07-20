#include <windows.h>
#include <thread>
#include <cstdio>
#include "click.h"

int main() {
    printf("Starting rollcall manager...\n");
    printf("Your mouse will be controlled."
    " Please give appropriate permissions.\n");
    #ifndef JUMP_START
    // Define jump start to skip this extra checking and confirmation.
    printf("Please make sure you have term.exe sticked to the task bar.\n");
    printf("Do you have it? Can you open it at any time?\n\n");
    {
        int has_term = std::system("choice /C yn /T 10 /D y");
        if (has_term != 1) {
            printf("Error: no term.exe. Cannot proceed.\n");
            return -1;
        }
    }
    #endif
    int interval = Rollcall::step_interval();
    printf("Step interval is %d\n", interval);
    if (interval == -1) {
        return 1;
    }
    bool do_loop = true;
    {
        int is_dev_run = std::system("choice /C yn /T 3 /D n"
            " /M \"Is this a development run?\"");
        if (is_dev_run == 1)
            do_loop = false;
    }
    printf("You have 5 seconds to shut this app down.\n");
    Sleep(5000);
    // Action! First, get home
    POINT home;
    GetCursorPos(&home);
    std::thread worker([do_loop, interval, home]{
        do Rollcall::do_clicking(interval, home.x, home.y);
        while (do_loop);
    });
    worker.join();
    return 0;
}
