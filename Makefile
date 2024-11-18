CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I. 
LDFLAGS = -L/usr/lib/x86_64-linux-gnu

SOURCES = main.cpp Interface.cpp Comm_Client.cpp Connection.cpp Calc.cpp Recorder.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = server

LIBS = -lboost_program_options -lcrypto -lpthread 

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)  

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

HEADERS = Interface.h Comm_Client.h Connection.h Calc.h Recorder.h Mistakes.h
