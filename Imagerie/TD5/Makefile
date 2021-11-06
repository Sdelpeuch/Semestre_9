CC := g++
CPPFLAGS=-I/opt/opencv/include 
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui\
  	-lopencv_features2d\
  	-lopencv_nonfree\
  	-lopencv_calib3d

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
	./panorama view-1.png view-2.png
	./panorama tower-1.png tower-2.png

.PHONY: clean
clean:
	$(RM) *~ *.png $(LIST)

.PHONY: cleanall
cleanall: clean
	-rm -r $(BINDIR)
	$(RM) $(BIN) *.o
