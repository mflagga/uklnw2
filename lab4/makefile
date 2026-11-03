.SUFFIXES: 

CXX := g++
CFLAGS := -Wall -Wextra
LIBS := -lm -lgsl -lgslcblas
SRCS := main.cpp defn.cpp eigsolver.cpp rozw.cpp
HDRS := decl.hpp
OBJS := main.o defn.o eigsolver.o rozw.o
EXEC := main.out
DATA := Efile.csv psifile.csv psiprimfile.csv

SCRIPT := plot.py
MEDIA := psi.png psiprim.png

all: $(MEDIA)

%.o: %.cpp $(HDRS)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CXX) $^ $(LIBS) -o $@

$(DATA): $(EXEC)
	./$<

$(MEDIA): $(SCRIPT) $(DATA)
	python3 $<

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
