#!/bin/bash

# Script to generate automatically the unified header for CoCoALib.

# Check we have one arg.
if [ $# -ne 1 ]
then
  echo                                                                  >/dev/stderr
  echo "ERROR: $0 requires 1 arg (the version ID of the CoCoALibrary)." >/dev/stderr
  exit 1
fi
VERSION="$1"

# Check we're in the CoCoALib/include/CoCoA/ directory.  Give error if not.
CWD=`pwd`
LAST=`basename "$CWD"`
TMP=`dirname "$CWD"`
LASTBUTONE=`basename "$TMP"`
if [ "$LAST" != "CoCoA" -o "$LASTBUTONE" != "include" ]
then
  echo                                                                         >/dev/stderr
  echo "ERROR: $0 should be run only in the directory CoCoALib/include/CoCoA/" >/dev/stderr
  exit 1
fi

UNIFIED_HDR=library.H

# Move existing unified header into a back-up file (with .old suffix).
if [ -f "$UNIFIED_HDR" ]
then
  /bin/rm -rf "$UNIFIED_HDR.old"
  /bin/mv "$UNIFIED_HDR" "$UNIFIED_HDR.old"
  echo "** Moved existing unified header file into $UNIFIED_HDR.old **"
  echo
fi

# BEFORE creating the new unified header file, get names of the CoCoALib header files.
# (otherwise the unified header file will include itself!)
COCOALIBHDRS=`/bin/ls *.H`

# Create preamble at start of unified header file.
# WARNING: the Makefile in the top CoCoALib directory looks for the version number using
#          a string search -- be careful if you change the format produced here!
TODAY=`date "+%Y%m%d"`
echo "#ifndef CoCoA_library_H"                                        >> "$UNIFIED_HDR"
echo "#define CoCoA_library_H"                                        >> "$UNIFIED_HDR"
echo                                                                  >> "$UNIFIED_HDR"
echo "// Unified header file for CoCoALib (version $VERSION)"         >> "$UNIFIED_HDR"
echo "// (produced automatically by MakeUnifiedHeader.sh on $TODAY)"  >> "$UNIFIED_HDR"
echo                                                                  >> "$UNIFIED_HDR"

# Now do an include directive for each individual header file (in COCOALIBHDRS).
for file in $COCOALIBHDRS
do
  echo "#include \"CoCoA/$file\""                                     >> "$UNIFIED_HDR"
done

# Postamble: close the read-once ifndef directive
echo                                                                  >> "$UNIFIED_HDR"
echo "#endif"                                                         >> "$UNIFIED_HDR"
