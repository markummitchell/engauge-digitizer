# This bash script creates .qch and .qhc output files. Optional argument is target directory.
# Since bash has different locations depending on the operating system, no #! line is included.
#
# Usage: .../build.bash [destdir]
# where:
#   [destdir]   Optional destination directory relative to the directory containing this script.
#               Default is ../bin/documentation

# Run this script in the 'help' subdirectory to prevent confusion about $1 argument being relative
# script directory or current working directory. Flathub build script likes the 'cd' command in
# this script rather than outside
SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
WORKPATH=`pwd`
WORKDIR=`basename $WORKPATH`
if [[ $WORKDIR != "help" ]]; then
    # Changing to script directory
    cd $SCRIPTDIR
fi

if [ $# -eq 0 ]; then
    DESTDIR=../bin/documentation
else
    DESTDIR=$1
fi

# Specifying ../bin/documentation directory here creates files in this directory
# AND ../bin/documentation (with different sizes) so we build into the local directory
qcollectiongenerator engauge.qhcp -o engauge.qhc

# Move to target directory which is relative to the help subdirectory
mkdir -p $DESTDIR
mv engauge.qch $DESTDIR
mv engauge.qhc $DESTDIR

