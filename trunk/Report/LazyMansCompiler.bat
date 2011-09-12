@echo off
:: Closing Adobe reader.
tasklist /FI "IMAGENAME eq acrord32.exe" | find /i "acrord32.exe" 
 
IF ERRORLEVEL 2 GOTO EXIST
IF ERRORLEVEL 1 GOTO NOTEXIST 
 
:EXIST
taskkill /F /IM "acrord32.exe"
set reopenvar=yes
goto FIRSTCLEANING
 
:NOTEXIST
set reopenvar=no
goto FIRSTCLEANING


:FIRSTCLEANING
IF NOT EXIST doc.aux goto COMPILING
::Cleaning if last compile failed
del doc.aux
del doc.log
del doc.out
del doc.synctex.gz
del doc.toc
del doc.bbl
del doc.synctex.gz(busy)
del doc.blg
GOTO COMPILING

::ERROR
:ERRORMASTER
echo doc.tex not found.
goto ENDWITHPAUSE

::Compiling
:COMPILING
IF NOT EXIST doc.tex goto ERRORMASTER
pdflatex.exe doc.tex -quiet
pdflatex.exe doc.tex -quiet
bibtex.exe doc.aux -quiet
pdflatex.exe doc.tex -quiet
pdflatex.exe doc.tex -quiet
del doc.aux
del doc.log
del doc.out
del doc.synctex.gz
del doc.toc
del doc.bbl
del doc.synctex.gz(busy)
del doc.blg
del /S *.aux
del biblog
del doc.brf
del texlog

::Starting adobe reader again
:START
IF %reopenvar%==yes start acrord32.exe doc.pdf
goto END

:ENDWITHPAUSE
pause

:END