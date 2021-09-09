
##### COLORS #####

GREEN='\033[1;32m'
YELLOW='\033[1;33m'
RED='\033[1;31m'
NC='\033[0m'


##### FILES #####

if [ ! -f ft ] || [ ! -f std ]; then
    echo "error: executables does not exists"
    exit 1
fi



ft()
{
    ./ft > file
}

std()
{
    ./std > file1
}

# START=$(date +%s.%N)

# sleep 1

# END=$(date +%s.%N)

# TIME=$(($END-$START))

echo $TIME

std
ft

# diff file file1

# diff ft std
# rm -rf file file1

