CXXFLAGS = -std=c++17 -Wall

.PHONY: all
all: rollcall.exe term.exe report.exe killclass.exe jumpstart.exe sender.exe

rollcall.exe: main.cpp click.h transfer.h
	g++ main.cpp -o rollcall $(CXXFLAGS)

term.exe: term.cpp
	g++ term.cpp -o term $(CXXFLAGS)

report.exe: report.cpp
	g++ report.cpp -o report $(CXXFLAGS)

killclass.exe: killclass.cpp
	g++ killclass.cpp -o killclass $(CXXFLAGS)

jumpstart.exe: main.cpp click.h transfer.h
	g++ main.cpp -o jumpstart -DJUMP_START $(CXXFLAGS)

sender.exe: sender.cpp transfer.h
	g++ sender.cpp -o sender $(CXXFLAGS)

.PHONY: clean
clean:
	rm *.exe

.PHONY: produce
produce:
	$(MAKE) all
	cp *.exe bin/