RASTERIZE=inkscape --export-pdf
GRAPHICS_EXTENSION=pdf

GRAPHICSPATH=./raster/
RESSOURCESPATH=./src/

RESSOURCES=$(wildcard $(RESSOURCESPATH)/*.svg)
GRAPHICS=$(patsubst $(RESSOURCESPATH)/%.svg,$(GRAPHICSPATH)/%.$(GRAPHICS_EXTENSION),$(RESSOURCES))

.PHONY: all clean 

#--------------------------------------------------
# RULES
#--------------------------------------------------

all: $(GRAPHICS)

$(GRAPHICSPATH)/%.$(GRAPHICS_EXTENSION): $(RESSOURCESPATH)/%.svg
	$(RASTERIZE) $@ $<

#--------------------------------------------------
# TOOLS
#--------------------------------------------------

clean:
	@$(RM) $(GRAPHICSPATH)/*

