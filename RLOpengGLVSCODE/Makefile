CXX = g++
CXXFLAGS = -Wall -g

SOURCES = main.cpp
EXECUTABLE = myprogram

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

clean:
	rm -f $(EXECUTABLE)
