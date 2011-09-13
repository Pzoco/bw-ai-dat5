#!/bin/sh
#  ---- META DATA ----
#  Author            :  Daniel Hillerström - dhille10@student.aau.dk
#  Date (YYYY-MM-DD) :  2010-11-01
#  Description       :  Compiles a LaTeX document and outputs it as *.pdf
#
#  Copyright (c) Daniel Hillerström 2010
#
#  Version history   :
#           - v1.0   :  2010-11-01 initial release
#           - v1.1   :  2010-11-11 added parameter: -interaction=nonstopmode to suppress all error messages.
#                       Compile with LaTeX or pdflatex before using this script. This script meant to ease the process of correcting references.
#           - v1.2   :  2010-12-01 Clean-up now removes additional garbage files.
#           - v1.3   :  2011-02-03 Added recursive clean-up of garbage files
#           - v2.0   :  2011-02-04 Implemented automatic image converting for all images in ./Figures/*. Currently supports conversion of *.png, *.jpg, *.jpeg and *.bmp
#           - v3.0   :  2011-05-02 Adjusted to integrate with projDOC-project more properly. Does now take document to compile as command line argument.
#           - v3.1   :  2011-05-02 Does now check whether document exists before starting compileprocess.
#           - v3.2   :  2011-05-18 The clean-up process does now also remove the converted figures in ./Figures catalog
#           - v3.3   :  2011-05-18 Compile-doc does now detect whether an error has occurred while compiling the document.
#           - LEGACY :  2011-05-18 Frozen version - not for redistribution - made only for those with problems regarding execution of version 3.5

# Retrieve commandline input
arg=$1
doc=
ext='.tex'

# Determine whether a document name was passed from CLI
if [ -z "$arg" ] 
then
  doc='doc'
  echo "** NOTICE: No document name argument was passed from CLI, assuming $doc"
else
  doc=$arg
fi

# Determine whether the file actually exists
if [ ! -f "$doc$ext" ]
then
  echo "** ERROR: Document $doc$ext does not exists!"
  exit 1
fi


# Convert all image files in ./Figures/ to PostScript and PDF formats
echo "Converting Figures to ps and pdf format..."
find ./Figures/ -iname \*.png -exec convert {} {}.ps \; -exec convert {} {}.pdf \;
find ./Figures/ -iname \*.jpg -exec convert {} {}.ps \; -exec convert {} {}.pdf \;
find ./Figures/ -iname \*.jpeg -exec convert {} {}.ps \; -exec convert {} {}.pdf \;
find ./Figures/ -iname \*.bmp -exec convert {} {}.ps \; -exec convert {} {}.pdf \;

# Compiling to DVI
#echo Compiling document to dvi format...
#latex -interaction=nonstopmode doc > dvi-output

# Compiling to PDF
echo "Compiling document $doc to pdf format..."
pdflatex -interaction=nonstopmode $doc > pdf-output

# Compiling bibtex
echo "Compiling bibtex"
bibtex $doc > bib-output

# Compiling to final DVI
#echo Compiling document to dvi format \(1\)...
#echo ---------------- First run > dvi-output
#latex -interaction=nonstopmode p2DOC >> dvi-output
#echo Compiling document to dvi format \(2\)...
#echo >> dvi-output
#echo ---------------- Second run >> dvi-output
#latex -interaction=nonstopmode p2DOC >> dvi-output

# Compiling to final PDF
echo "Setting references in document $doc..."
echo ---------------- First run > pdf-output
pdflatex -interaction=nonstopmode $doc >> pdf-output
echo "Adjusting labels in document $doc..."
echo >> pdf-output
echo ---------------- Second run >> pdf-output
pdflatex -interaction=nonstopmode $doc >> pdf-output

# Assign latest pdflatex exitcode to the variable erroccr
erroccr=$?

# Clean-up LaTeX generated files
echo "Commencing recursive clean-up..."
find -iname \*.aux -or -iname \*.log -or -iname \*.toc -or -iname \*.bbl -or -iname \*.blg -or -iname \*.blg -or -iname \*.brf -or -iname \*.out | xargs rm
# Clean-up converted figures
cd ./Figures
find -iname \*.ps -or -iname \*.pdf | xargs rm
cd ../
#rm dvi-output
# Determines whether to remove logs
if [ $erroccr -eq 0 ]
then
  rm pdf-output
  rm bib-output
else
  echo "** ERROR: At least one error occurred while compiling the $doc, please refer the logs 'pdf-output' and 'bib-output' for error descriptions."
fi
echo "FINISHED!"

