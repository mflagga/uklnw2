ifeq ($(OS),Windows_NT)
	PC := python
	RM := del /q
	RMDIR := rmdir /s /q
	MV := move
	DEVNULL := NUL 2>&1
	VR = @echo nie ma valgrinda na windowsie
	SLASH = $(strip \)
else
	PC := python3
	RM := $(RM)
	RMDIR := rm -rf
	MV := mv
	DEVNULL := /dev/null
	VR = valgrind ./$(EXEC)
	SLASH = /
endif

.SUFFIXES: 

CXX := g++
CFLAGS := -Wall -Wextra
LIBS := -lm -lgsl -lgslcblas
SRCS := main.cpp defn.cpp eigsolver.cpp rozw.cpp
HDRS := decl.hpp
OBJS := main.o defn.o eigsolver.o rozw.o
EXEC := main.out
DATA := pkt1Ek.csv pkt1dE0.csv pkt1dEsum.csv pkt2kappa.csv pkt3ff.csv

SCRIPT := plot.py
MEDIA := pkt1dE0.png pkt1dEsum.png Ek0.png Ek1.png Ek2.png Ek3.png Ek4.png kb0.png kb1.png kb2.png kb3.png kb4.png kappa.png psi.png

STDFLAGS := -lualatex -interaction=nonstopmode
BUILDDIR := .build
TEXNAME := spr
TEX = $(TEXNAME).tex
REPORT := sprawozdanie.pdf

all: $(REPORT)

%.o: %.cpp $(HDRS)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CXX) $^ $(LIBS) -o $@

$(DATA): $(EXEC)
	./$<

$(MEDIA): $(SCRIPT) $(DATA)
	$(PC) $<

$(REPORT): $(TEX) $(MEDIA)
	latexmk $(STDFLAGS) -output-directory=$(BUILDDIR) $< > $(DEVNULL)
	$(MV) $(BUILDDIR)$(SLASH)$(TEXNAME).pdf $@ > $(DEVNULL)

gotowe: $(EXEC)
	./$<

safe: $(EXEC)
	$(VR)

clean:
	$(RM) $(OBJS)
	$(RM) $(EXEC)
	$(RM) $(DATA)
	$(RM) $(MEDIA)
	$(RMDIR) $(BUILDDIR)
# 	$(RM) $(REPORT)

.PHONY: all clean safe gotowe
