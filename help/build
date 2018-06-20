#!/usr/bin/bash

# This creates .qch and .qhc output files. Optional argument is target directory

if [ $# -eq 0 ]; then
    DESTDIR=../bin/documentation
else
    DESTDIR=$1
fi

# Specifying ../bin/documentation directory here creates files in this directory
# AND ../bin/documentation (with different sizes) so we build into this directory
qcollectiongenerator engauge.qhcp -o engauge.qhc

# Move to target directory
mv engauge.qch $DESTDIR
mv engauge.qhc $DESTDIR

