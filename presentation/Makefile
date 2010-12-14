SRC = src
TMP = tmp
BIN = .
TEX_BASE_NAME = presentation
PDF_BASE_NAME = presentation

all:
	cp $(SRC)/*.tex $(TMP)/ && cd $(TMP) && pdflatex $(TEX_BASE_NAME).tex && mv $(TEX_BASE_NAME).pdf ../$(BIN)/$(PDF_BASE_NAME).pdf

clean:
	rm -rf $(TMP)/*
