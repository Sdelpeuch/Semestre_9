CC := g++
CPPFLAGS=-I/opt/opencv/include 
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui

BINDIR=./
SOURCEDIR=./

SRCS := $(wildcard *.cpp)
NAMES = $(basename $(SRCS))
LIST := $(addprefix $(BINDIR)/,$(NAMES))

.PHONY: all 
all: $(LIST)

$(BINDIR)/%:  $(SOURCEDIR)%.cpp
	mkdir -p $(BINDIR)
	$(CC) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@ 

.PHONY: test
test:
	./readwriteshow ../data/lena_color.png a.png; pvisu a.png
	./crop ../data/lena_color.png 10 200 300 100; pvisu crop.png; pvisu crop-cv.png
	./pixels-loops ../data/lena_color.png
	./video-player ../data/video-tribot.mp4
	./video-player ../data/video-seq4.mp4

.PHONY: clean
clean:
	$(RM) *~ *.png $(LIST)

.PHONY: cleanall
cleanall: clean
	-rm -r $(BINDIR)
	$(RM) $(BIN) *.o
