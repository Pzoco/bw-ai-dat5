#!/bin/bash
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
#                       Compile with LaTeX or pdflatex before using this script. This script is meant to ease the process of correcting references.
#           - v1.2   :  2010-12-01 Clean-up now removes additional garbage files.
#           - v1.3   :  2011-02-03 Added recursive clean-up of garbage files
#           - v2.0   :  2011-02-04 Implemented automatic image converting for all images in ./Figures/*. Currently supports conversion of *.png, *.jpg, *.jpeg and *.bmp
#           - v3.0   :  2011-05-02 Adjusted to integrate with projDOC-project more properly. Does now take document to compile as command line argument.
#           - v3.1   :  2011-05-02 Does now check whether document exists before starting compileprocess.
#           - v3.2   :  2011-05-18 The clean-up process does now also remove the converted figures in ./Figures catalog
#           - v3.3   :  2011-05-18 Compile-doc does now detect whether an error has occurred while compiling the document.
#           - v3.4   :  2011-05-26 Document name passed from CLI may now contain fileextension
#           - v3.5   :  2011-05-26 Fixed 'no compilation' bug which occurred when no argument was passed from CLI
#           - v4.0   :  2011-05-26 The script now verifies that the engines used for compilation exist before calling them
#           - v5.0   :  2011-05-31 Compile-doc has been rewritten because it had grown quite large. It is now prettier and better!                                 
#           - v5.1   :  2011-06-16 Having %[COMPILE-DOC]nobib in main document file now makes compile-doc skip bibtex compilation
#           - v5.2   :  2011-06-16 Solved bug which caused compile-doc to fail whenever the execution path contained spaces.

# Default document name
DEFAULTDOC="doc"

# Retrieve commandline input
ARGUMENT=$1

# Global variables
DOCUMENT=
EXTENSION=".tex"
TEXLOG="texlog"
BIBLOG="biblog"
FIGURESPATH="./Figures/"
ERROROCCURRED=0
JOBNUM=0
JOBCOUNT=1
EXEC_DIR=$(pwd)
TEXENGINE="pdflatex"
BIBENGINE="bibtex"
CONVERTENGINE="convert"

# Verifies whether an executable file exists, returns 0 if true
ExecutableExists()
{
  type -p $1 > /dev/null
  rval=$?
  return $rval
}

# Verifies that the required executables exists
DoEngineCheck()
{
  declare -a engines=($TEXENGINE $BIBENGINE $CONVERTENGINE)
  
  for engine in "${engines[@]}"; do
    ExecutableExists $engine
    if [ $? -ne 0 ]
    then
      echo "** ERROR: Missing engine '$engine'"
      exit 1
    fi
  done
}

# Get document name without extension
GetDocName()
{
  echo $(basename $1 $EXTENSION)
}

# Determines whether a file exists, return 0 if true
FileExists() 
{
  fexists=0
  if [ ! -f "$1$2" ]
  then
    fexists=1
  fi
  return $fexists  
}

# Convert figures
ConvertFigures()
{
  declare -a figtypes=('.png' '.jpg' '.jpeg' '.bmp')
  for figtype in ${figtypes[@]}; do
    find ./$1/ -iname \*$figtype -exec convert {} {}.ps \; -exec convert {} {}.pdf \;
  done
  
  return $?
}

# TeXCompile
TeXCompile()
{
  $1 -interaction=nonstopmode $2 > $TEXLOG
  return $?
}

# Recursively deletes files with a given extension, parameter: array of strings
RemoveGarbage()
{
  declare -a garbagefiles=$@
  for garbage in ${garbagefiles[@]}; do
    find -iname \*$garbage | xargs rm 2> /dev/null
  done
}

# CleanUp procedure
CleanUp()
{
  # Define garbage files
  declare -a texGarbage=(.aux .log .toc .bbl .blg .brf .out)
  declare -a figGarbage=(.ps .pdf)
  declare -a logGarbage=($TEXLOG $BIBLOG)
  declare -a beamerGarbage=(.snm .nav)

  # Remove tex garbage files
  RemoveGarbage ${texGarbage[@]}
  # Remove beamer garbage files
  RemoveGarbage ${beamerGarbage[@]}
  
  # Remove converted figures
  if [ -d "$FIGURESPATH" ]
  then
    cd "$FIGURESPATH"
    RemoveGarbage ${figGarbage[@]}
    cd "$EXEC_DIR"
  fi
  
  # Do only remove logs if no compile errors occurred
  if [ $ERROROCCURRED -eq 0 ]
  then
    RemoveGarbage ${logGarbage[@]}
  fi
  
  return 0
}

# Callwrapper for ConvertFigures
ConvertJob() 
{
  # Convert figures
  echo "($JOBNUM/$JOBCOUNT) Converting Figures to ps and pdf format..."
  ConvertFigures "Figures"
  return $?
}

# Callwrapper for TeXCompile
CompileJob() 
{
  # Run pdflatex
  echo "($JOBNUM/$JOBCOUNT) Compiling document $DOCUMENT to pdf format..."
  TeXCompile "pdflatex" $DOCUMENT$EXTENSION
  return $?
}

# Callwrapper for bibtex
CompileBibJob()
{
  # Run bibtex
  echo "($JOBNUM/$JOBCOUNT) Compiling bibtex-file..."
  bibtex $DOCUMENT > $BIBLOG
  return $?
}

# Callwrapper for CleanUp
CleanUpJob() 
{
  # Run CleanUp
  echo "($JOBNUM/$JOBCOUNT) Commencing recursive clean-up..."
  CleanUp
}

# Job name translator
ErrorMessages() 
{
  case "$1" in
  ConvertJob) echo "** ERROR: An unhandled error occurred while converting figures.";;
  CompileJob) echo "** ERROR: An unhandled error occurred while running $TEXENGINE, please refer to '$TEXLOG' for error descriptions.";;
  CompileBibJob) echo "** ERROR: An unhandled error occurred while running $BIBENGINE, please refer to '$BIBLOG' for error descriptions.";;
  CleanUpJob) echo "** ERROR: An unhandled error occurred while performing clean-up procedure.";;
  *) echo "** ERROR: An unknown error has occurred!";;
  esac
}

# Pulls out %[COMPILE-DOC]nobib from main document file
ExcludeBibJob()
{
  grep COMPILE\-DOC $DOCUMENT$EXTENSION  | grep nobib > /dev/null
  rval=$?
  return $rval
}

# Call main procedure
Main()
{
  # Make sure the required executables exist
  DoEngineCheck
  # Retrieve document name without extension
  if [ -z $ARGUMENT ]
  then
    DOCUMENT=$DEFAULTDOC
    echo "** NOTICE: No document name was passed from CLI, assuming $DEFAULTDOC$EXTENSION"
  else
    DOCUMENT=$(GetDocName $ARGUMENT)
  fi
  # Make sure the file exists
  FileExists $DOCUMENT$EXTENSION
  if [ $? -ne 0 ]
  then
    echo "** ERROR: Document '$DOCUMENT' does not exist!"
    exit 1
  fi

  # Determines whether to exclude Bibtex compilation job
  ExcludeBibJob
  excludebib=$?
  
  # Declare array containing jobs
  if [[ -n $excludebib && $excludebib -eq 0 ]]
  then
    declare -a JobArray=(ConvertJob CompileJob CompileJob CleanUpJob)
  else
    declare -a JobArray=(ConvertJob CompileJob CompileBibJob CompileJob CompileJob CleanUpJob)
  fi

  JOBCOUNT=${#JobArray[*]}
  
  for job in ${JobArray[@]}; do
    JOBNUM=`expr $JOBNUM + 1`
    $job
    if [ $? -ne 0 ]
    then
      ErrorMessages $job
      ERROROCCURRED=1
    fi
  done
  echo "FINISHED!"
}

# Call Main procedure
Main
