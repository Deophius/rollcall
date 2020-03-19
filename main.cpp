#include <windows.h>
#include <cstdio>

// Configure these variables for your use.
// Default config is for screen with 1366 * 678.
// Start of the region for madness clicking.
const int screen_start_x = 110;
const int screen_start_y = 140;
// End of madness clicking.
const int screen_end_x = 1070;
const int screen_end_y = 720;
// The size of the Confirm button, a little smaller to increase aim.
const int x_step = 200;
const int y_step = 20;

int step_interval() {
    // Configure these variables for your use.
    // Maximum time for a cycle to complete. In milliseconds.
    // 20000 is the value that's for wxb as of 2020.3.18.
    const int cycle_max = 20000;
    int steps1 = (screen_end_x - screen_start_x) / x_step + 1;
    int steps2 = (screen_end_y - screen_start_y) / y_step + 1;
    long long total_steps = steps1 * steps2;
    int ans = cycle_max / total_steps;
    if (ans < 10) {
        printf("Error: the lowest speed to iterate over the screen is too high."
        " Cannot proceed.\n");
        ans = -1;
    }
    return ans;
}

void do_clicking(int interval) {
    for (int i = screen_start_x; i <= screen_end_x; i += x_step) {
        for (int j = screen_start_y; j <= screen_end_y; j += y_step) {
            SetCursorPos(i, j);
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(interval);
        }
    }
}

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
    int interval = step_interval();
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
    do do_clicking(interval);
    while (do_loop);
    return 0;
}
