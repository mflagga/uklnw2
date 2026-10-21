.SUFFIXES: 

CXX := g++
CFLAGS := -Wall -Wextra
LIBS := -lm -lgsl -lgslcblas
SRCS := main.cpp defn.cpp
HDRS := decl.hpp
OBJS := main.o defn.o
EXEC := main.out
DATA := 

all: gotowe

%.o: %.cpp $(HDRS)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CXX) $^ $(LIBS) -o $@

$(DATA): $(EXEC)
	./$<

gotowe: $(EXEC)
	./$<

safe: $(EXEC)
	valgrind ./$<

clean:
	rm -f $(OBJS)
	rm -f $(EXEC)
	rm -f $(DATA)

.PHONY: all clean safe gotowe
