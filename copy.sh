#! /bin/bash

if [ ! -d ../V2V/V2V ];then
	echo "Please place V2V and V2V_Linux in the same directory"
	exit
fi

# First obtain the V2V's git version number

cd ../V2V/V2V/
uq=$(git rev-list --all | head -n 1)
uq=${uq:0:7}

# Write the format version information

description="## version_"$(date +%Y)"_"$(date +%m)"_"$(date +%d)"("$uq")"

cd ../../V2V_Linux

echo $description >> README.md

# Remove the old files
rm -f *.h *.cpp
rm -rf config log wt

sleep 2s

# Copy files from V2V
cp -a ../V2V/V2V/*.cpp  ../V2V/V2V/*.h  .
cp -a ../V2V/V2V/config ../V2V/V2V/log ../V2V/V2V/wt .

sleep 2s

# Begin converting the encoding format

files=$(find . -regex ".*\.\(h\|cpp\|xml\)")

for file in $files
do
	echo "Convert encoding format: "$file
	iconv -f gbk -t utf-8 $file -o $file
done

# Commit

git add .

git commit -m ${description:3}

git push origin master:master