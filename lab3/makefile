.SUFFIXES: 

CXX := g++
CFLAGS := -Wall -Wextra
LIBS := -lm -lgsl -lgslcblas
SRCS := main.cpp defn.cpp rozw.cpp
HDRS := decl.hpp
OBJS := main.o defn.o rozw.o
EXEC := main.out
DATA := wez.csv fun.csv dp.csv

PC := python3
SCRIPT := plot.py
MEDIA := wez.png fun.png deltafun.png dp.png

all: $(MEDIA)

%.o: %.cpp $(HDRS)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CXX) $^ $(LIBS) -o $@

$(DATA): $(EXEC)
	./$<

$(MEDIA): $(SCRIPT) $(DATA)
	$(PC) $<

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
