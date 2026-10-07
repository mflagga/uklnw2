.SUFFIXES:

CXX := g++
CFLAGS := -Wall -Wextra
LIBS := -lm -lgsl -lgslcblas
SRCS := main.cpp defn.cpp rozw.cpp
OBJS := main.o defn.o rozw.o
HDRS := decl.hpp
EXEC := main.out
DATA := tfile.csv ufile.csv Snfile.csv nfile.csv
SCRIPT := plot.py
MEDIA := Sn.png u.png u0.png

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
# 	rm -f $(MEDIA)

.PHONY: all clean safe gotowe
