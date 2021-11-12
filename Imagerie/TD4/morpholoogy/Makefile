CPPFLAGS= -I. -I/opt/opencv/include 
CXXFLAGS= -Wall -Wextra
LDFLAGS = -Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui

#modify DATA or VIEWER path command if not applicable
VIEWER= eog
DATA= ../data

OBJ= morphology.o
BIN= \
	make-se\
	dilation\
	erosion\
	opening\
	closing\
	otsu\
	labeling\
	labeling-color

.PHONY: all
all: $(BIN)

$(BIN): morphology.o

.PHONY: test-deploy
test-deploy: all
	@./make-se ; true
	@./dilation ; true
	make extract-gear
	make extract-cell

.PHONY: extract-gear
extract-gear:
	make clean
	make all
	./make-se 2 15 se_for_gear.png
	./opening se_for_gear.png $(DATA)/gear.png gear_without_teeth.png
	composite -compose difference $(DATA)/gear.png gear_without_teeth.png gear_teeth_only.png
	./otsu gear_teeth_only.png gear-res.png
	./labeling-color gear-res.png gear-r.png gear-res-color.png
	$(VIEWER) $(DATA)/gear.png
	$(VIEWER) gear-res.png
	$(VIEWER) gear-res-color.png

.PHONY: extract-cell
extract-cell:
	make clean
	make all
	# On applique l'opening pour récuperer que les cells
	./make-se 2 20 se_for_cell.png
	./opening se_for_cell.png $(DATA)/cell.png cell_open.png
	./otsu cell_open.png cell-res.png
	./labeling-color cell-res.png cell-r.png cell-res-color.png
	# On récupère les contours blancs 	
	./make-se 2 5 se_boundaries.png
	./erosion se_boundaries.png cell-res.png cell-minus.png
	composite -compose difference cell-res.png cell-minus.png cell-res-boundary.png
	# On récupère les contours colorés en prenant soin de supprimer aussi l'intérieur des cellules
	convert cell-res-boundary.png -transparent white cell-res-boundary_transparent.png
	composite -compose Over cell-res-boundary_transparent.png cell-res-color.png cell-res-boundary-color.png
	# On applique les contours colorés sur l'image de départ
	convert cell-res-boundary-color.png -transparent black cell-res-boundary-color_transparent.png
	composite -compose Over cell-res-boundary-color_transparent.png $(DATA)/cell.png cell-final.png
	# On affiche les images	
	$(VIEWER) $(DATA)/cell.png
	$(VIEWER) cell-res.png
	$(VIEWER) cell-res-color.png
	$(VIEWER) cell-res-boundary.png
	$(VIEWER) cell-final.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf


