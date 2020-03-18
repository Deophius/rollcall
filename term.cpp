#include <cstdlib>

int main() {
    // Terminate the rollcall clicker in case of emergency.
    // Recommended on the task bar.
    std::system("taskkill /f /im rollcall.exe");
}