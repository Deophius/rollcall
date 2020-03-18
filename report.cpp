#include <windows.h>
#include <cstdlib>
#include <cstdio>

int main() {
    // Reports the current cursor position to stdout.
    ::POINT cursor;
    ::GetCursorPos(&cursor);
    std::printf("The cursor position is {%ld,%ld}\n", cursor.x, cursor.y);
    std::system("pause");
}