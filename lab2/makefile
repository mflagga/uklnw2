.SUFFIXES: 

CXX := g++
CFLAGS := -Wall -Wextra
LIBS := -lm -lgsl -lgslcblas
SRCS := main.cpp defn.cpp eigsolver.cpp rozw.cpp
HDRS := decl.hpp
OBJS := main.o defn.o eigsolver.o rozw.o
EXEC := main.out
DATA := pkt1Ek.csv pkt1dE0.csv pkt1dEsum.csv pkt2kappa.csv

SCRIPT := plot.py
MEDIA := pkt1dE0.png pkt1dEsum.png Ek0.png Ek1.png Ek2.png Ek3.png Ek4.png kb0.png kb1.png kb2.png kb3.png kb4.png kappa.png

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
	rm -f $(MEDIA)

.PHONY: all clean safe gotowe
