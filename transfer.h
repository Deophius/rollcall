#pragma once
#include <windows.h>
#include <fileapi.h>
#include <exception>
#include <iostream>

// Errors about pipes are notified with an asterisk beep

namespace Rollcall {
    // Command constants
    constexpr char kill_command = 0;
    constexpr char toggle_command = 1;
    constexpr char pause_command = 2;
    constexpr char resume_command = 3;
    constexpr char rewind_command = 4;
    constexpr char unknown_command = 255;

    // The name of the pipe
    const char* pipe_name = "\\\\.\\pipe\\rollcall";

    // Creates the named pipe and returns the handle
    HANDLE create_pipe() {
        HANDLE pipe = ::CreateNamedPipe(
            pipe_name,
            PIPE_ACCESS_INBOUND,
            PIPE_TYPE_BYTE | PIPE_NOWAIT,
            10, 50, 50, 0, NULL);
        if (pipe == INVALID_HANDLE_VALUE) {
            MessageBeep(MB_ICONASTERISK);
            MessageBox(NULL, TEXT("Error creating pipe!"), TEXT("Error"),
                MB_ICONERROR | MB_OK);
            std::terminate();
        }
        return pipe;
    }

    bool send_command(char command) {
        HANDLE pipe = ::CreateFile(pipe_name, GENERIC_WRITE, 0, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (pipe == INVALID_HANDLE_VALUE) {
            MessageBeep(MB_ICONASTERISK);
            MessageBox(NULL, TEXT("Error sending bytes to the pipe!"),
                TEXT("ERROR"), MB_ICONERROR | MB_OK);
            return false;
        }
        DWORD written = 0;
        ::WriteFile(pipe, &command, 1, &written, NULL);
        return bool(written);
    }

    bool read_command(char& command) {
        command = unknown_command;
        HANDLE pipe = ::CreateFile(pipe_name, GENERIC_READ, 0, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        ERROR_ACCESS_DENIED;
        if (pipe == INVALID_HANDLE_VALUE) {
            std::cout << "Error code: " << GetLastError() << std::endl;
            MessageBeep(MB_ICONASTERISK);
            MessageBox(NULL, TEXT("Error opening pipe to read!"),
                TEXT("Error"), MB_ICONERROR | MB_OK);
            return false;
        }
        DWORD read = 0;
        ::ReadFile(pipe, &command, 1, &read, NULL);
        return (bool)read;
    }

    void server_func() {
        HANDLE pipe = create_pipe();
        while (true) {
            char command;
            ::Sleep(1000);
            // Check for input
            if (read_command(command)) {
                std::cout << "Got command: " << (int)command << std::endl;
            }
        }
        CloseHandle(pipe);
    }
}