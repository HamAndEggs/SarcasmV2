#/bin/bash
# ************************
# Some colours
# ************************
RED='\033[0;31m'
BOLDRED='\033[1;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
BOLDBLUE='\033[1;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

#********************************************************************************************************************
# Some functions
#********************************************************************************************************************
function Message()
{
	if [ -z "$2" ]; then
        echo -e "$GREEN$1$NC"
    else
        echo -e "$1$2$NC"
    fi
}

#********************************************************************************************************************
PROJECT_NAME="SarcasmV2"
EXEC_OUTPUT_FILE="$PROJECT_NAME.uf2"
DESTINATION_FOLDER="/media/richard/RPI-RP2/"

# Pop into the build folder where cmake creates a million files. :-/
mkdir -p ./build
cd ./build

# I always do this, had issue with sometimes not updating.
cmake ..

# I always do a simple clean local bits, I hate it when you're changing source and it's not being built for some random make bug.
rm -f ./$PROJECT_NAME.*
rm -f ./*.pio.h

# And build.
make -j16

# Did it work? Can we upload?
if [ -f $EXEC_OUTPUT_FILE  ]; then
    Message "Compiled :)"
    if [ -d $DESTINATION_FOLDER ]; then
        Message $Blue "Copying file $EXEC_OUTPUT_FILE"
        cp ./$EXEC_OUTPUT_FILE $DESTINATION_FOLDER
    else
        Message $RED "Destination folder missing $DESTINATION_FOLDER"
    fi
else
    Message $RED "Build failed!"
fi

cd ..

