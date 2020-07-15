This is a tool to automatically cover a rectangle on the screen with repetitive clicking.
First intentional use was against rollcall facility of wxb programs.
Just a little junk, actually. Uses WinAPI's SendInput() as the core of things.

How to build:
1. Make a bin/ directory.
2. Run "make produce", and the executables are in bin/.

What each file does:
  "jumpstart""rollcall" are quite similar. They are the core programs of the toolset.
  They cover a screen rectangle with mouse clickings by moving the mouse with SetCursorPos, and simulates clicking
with SendInput().
  The configuration variables are in click.h. The actual clicking function is there, too.
  Note that these two executables share the same source and differs in compilation by a preprocessor switch.
  "Rollcall" waits for 18s before starting the work. "Jumpstart" waits for 13s.
  Each have a functionality called "development run", where the clicking will be done once.
  "Jumpstart" is more suitable for serious use.
  
  preclass.bat contains a command that must be run as root/admin. It activates WinuponService, so that the core
  programs work correctly. If WinuponService is not running, core programs cannot work correctly.
  
  report.exe reports the current mouse position. This is used to gather information and configure the program.
  
  killclass.exe kills iMeeting.exe forcefully, in case it misbehaves.
  
  term.exe terminates the core programs. It should be on the taskbar during class, so you can use Win+<num> key
  shortcut to access it.
  
How to configure:
  The code assumes that the rectangle is (190, 250) to (1070, 720). This should work for a wxb session on a 
1366*768 screen with chatting bar visible and toolbars hidden.
  Assumed size for the "confirm" button is 200*20 (horizontal * vertical).
  Assumed time for a rollcall confirmation to time out is 20s. But we use 10s to make sure that we don't miss
the clicking when program first starts.
  Assumed minimum time between clicks is 100ms. Otherwise, the mouse moving too quickly is suspicious, and it
makes the system overloaded.
  You can make changes to those variables easily, except for 100ms. Adjust the variables in click.h to suit
your needs.

How to use:
  1. Gather some info about your screen and wxb sessions. Then, configure the program correctly. Perhaps you should
take a screenshot and use that to check that the "confirm" button's size is correct. You can use excel to check that
clicking is functioning correctly.
  2. Build the program and test it with screenshots and excel.
  3. Stick "term.exe" to the taskbar, and make yourself familar with the win+<num-key> combination to open it.
  4. Find a way to open "jumpstart.exe" during class. Noting that the screen is locked, you can have as much imagi-
nation as you dare here. One idea is to stick that to taskbar as well. Another is to put the "address toolbar" of
Windows into use, and copy-paste the command line to start the program into the toolbar.
  5. Whenever you want to terminate the rollcall tools, use win+<num-key> combination to call term.exe, and it should
kill the core programs and exit after 0.5s.

Thanks to these wonderful people around me, who helped me come up with this idea.
Thanks to the developers of the winapi, who provides me with such a rich set of functionality to use.
Thanks to helpful people on CSDN, who helped me out with the mouse event simulation.

This is free software, licensed under GPL-3.0.
