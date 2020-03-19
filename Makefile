CXXFLAGS = -std=c++17 -Wall

.PHONY: all
all: rollcall.exe term.exe report.exe killclass.exe jumpstart.exe

rollcall.exe: main.cpp
	g++ main.cpp -o rollcall $(CXXFLAGS)

term.exe: term.cpp
	g++ term.cpp -o term $(CXXFLAGS)

report.exe: report.cpp
	g++ report.cpp -o report $(CXXFLAGS)

killclass.exe: killclass.cpp
	g++ killclass.cpp -o killclass $(CXXFLAGS)

jumpstart.exe: main.cpp
	g++ main.cpp -o jumpstart -DJUMP_START $(CXXFLAGS)

.PHONY: clean
clean:
	rm *.exe

.PHONY: produce
produce:
	make all -j 4
	cp *.exe bin/