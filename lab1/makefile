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
CFLAGS := -Wall -Wextra -Wpedantic
LIBS := -lm -lgsl -lgslcblas
SRCS := main.cpp defn.cpp rozw.cpp
OBJS := main.o defn.o rozw.o
HDRS := decl.hpp
EXEC := main.out
DATA := tfile.csv ufile.csv Snfile.csv nfile.csv Dnfile.csv

SCRIPT := plot.py
MEDIA := Sn.png u.png u0.png Dn.png

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
	$(RM) $(REPORT)

.PHONY: all clean safe gotowe
