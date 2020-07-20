#pragma once
#include <windows.h>
#include <cstdio>

namespace Rollcall {
    // Clicking errors are reminded with the error sound
    // Configure these variables for your use.
    // Default config is for screen with 1366 * 678.
    // Start of the region for madness clicking.
    const int screen_start_x = 190;
    const int screen_start_y = 250;
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
        const int cycle_max = 10000;
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

    // Return to "home base" after each click.
    void do_clicking(int interval, int homex, int homey) {
        for (int i = screen_start_x; i <= screen_end_x; i += x_step) {
            for (int j = screen_start_y; j <= screen_end_y; j += y_step) {
                // Prepare the input structures
                INPUT inputs[2];
                for (int k = 0; k < 2; k++) {
                    inputs[k].type = INPUT_MOUSE;
                    inputs[k].mi.dx = 0;
                    inputs[k].mi.dy = 0;
                }
                inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
                SetCursorPos(i, j);
                if (SendInput(2, inputs, sizeof(INPUT)) != 2)
                    MessageBeep(MB_ICONERROR);
                SetCursorPos(homex, homey);
                Sleep(interval);
            }
        }
    }
}