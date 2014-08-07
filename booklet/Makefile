
all: pdf

pdf: output/BOOKLET.pdf

misc = Makefile $(wildcard *.sty)
texsources = $(wildcard *.tex) $(wildcard statements/*.tex) $(wildcard solutions/*.tex)

output/BOOKLET.pdf: $(texsources) $(misc)
	mkdir -p output
	pdflatex -output-directory output $<
	pdflatex -output-directory output $<
	pdflatex -output-directory output $<

clean:
	rm -rf output
