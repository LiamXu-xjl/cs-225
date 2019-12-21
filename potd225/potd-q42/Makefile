EXENAME = main
OBJS = main.o

CXX = c++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = c++
LDFLAGS = -std=c++0x

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

main.o: main.cpp potd.cpp
	$(CXX) $< $(CXXFLAGS)

clean:
	-rm -f *.o $(EXENAME)
