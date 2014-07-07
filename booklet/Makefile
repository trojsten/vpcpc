
all: pdf

pdf: output/BOOKLET.pdf

misc = Makefile $(wildcard *.sty)
texsources = $(wildcard statements/*.tex) $(wildcard solutions/*.tex)

output/BOOKLET.pdf: BOOKLET.tex $(texsources) $(misc)
	mkdir -p output
	pdflatex -output-directory output $<
	pdflatex -output-directory output $<
	pdflatex -output-directory output $<

clean:
	rm -rf output
