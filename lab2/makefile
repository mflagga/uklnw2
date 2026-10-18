.SUFFIXES: 

CXX := g++
CFLAGS :=
LIBS := -lm -lgsl -lgslcblas
SRCS := main.cpp defn.cpp eigsolver.cpp rozw.cpp
HDRS := decl.hpp
OBJS := main.o defn.o eigsolver.o rozw.o
EXEC := main.out
DATA := pkt1Ek.csv pkt1dE0.csv pkt1dEsum.csv

SCRIPT := plot.py
MEDIA := dE0.png

all: $(MEDIA)

%.o: %.cpp $(HDRS)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CXX) $^ $(LIBS) -o $@

$(DATA): $(EXEC)
	./$<

$(MEDIA): $(SCRIPT) $(DATA)
	python3 plot.py

gotowe: $(EXEC)
	./$<

safe: $(EXEC)
	valgrind ./$<

clean: 
	rm -f $(OBJS)
	rm -f $(EXEC)
	rm -f $(DATA)

.PHONY: all clean safe gotowe
