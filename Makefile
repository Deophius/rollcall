CXXFLAGS = -std=c++17 -Wall

.PHONY: all
all: rollcall.exe term.exe report.exe killclass.exe

rollcall.exe: main.cpp
	g++ main.cpp -o rollcall $(CXXFLAGS)

term.exe: term.cpp
	g++ term.cpp -o term $(CXXFLAGS)

report.exe: report.cpp
	g++ report.cpp -o report $(CXXFLAGS)

killclass.exe: killclass.cpp
	g++ killclass.cpp -o killclass $(CXXFLAGS)

.PHONY: jumpstart
jumpstart: main.cpp
	g++ main.cpp -o rollcall -DJUMP_START $(CXXFLAGS)

.PHONY: clean
clean:
	rm *.exe
