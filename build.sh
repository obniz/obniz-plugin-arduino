#!/bin/bash

echo "versionを入力してください"
read input

if [ -z $input ] ; then

  echo "スクリプトを終了します"
  exit 1

else

  echo "--------- arduino start ---------"
  rm -r $input
  rm ./docs/obniz-v$input.zip
  mkdir $input
  echo "Files copy"
  cp -r ./cores ./$input/cores
  echo "- cores copied"
  cp -r ./libraries ./$input/libraries
  echo "- libraries copied"
  mkdir  $input/tools
  cp -r ./tools/*.exe ./tools/*.py  ./$input/tools/
  cp -r ./tools/partitions ./$input/tools
  cp -r ./tools/sdk ./$input/tools
  echo "- tools copied"
  cp -r ./variants ./$input/variants
  echo "- variants copied"
  cp boards.txt programmers.txt ./$input/
  cp arduino_platform.txt ./$input/platform.txt
  echo "- settingfiles copied"

  echo "Create zip file"
  zip -r -q ./docs/obniz-v$input.zip $input
  echo "Created zip file"
  SHA256=`sha256sum ./docs/obniz-v$input.zip | cut -d " " -f 1`
  FILE_SIZE=`wc -c < ./docs/obniz-v$input.zip`
  rm -r $input
  echo "Get checksum & file size"

  echo ""
  echo "Package.json info"
  echo ""

  Node build.js https://obniz.github.io/obniz-plugin-arduino/obniz-v$input.zip SHA-256:$SHA256 $FILE_SIZE obniz-v$input.zip $input

  echo "\"url\": \"https://obniz.github.io/obniz-plugin-arduino/obniz-v$input.zip\","
  echo "\"checksum\": \"SHA-256:$SHA256\","
  echo "\"size\": \"$FILE_SIZE\","
  echo "\"archiveFileName\": \"obniz-v$input.zip\","
  echo "\"version\": \"$input\","

  echo ""
  echo "--------- arduino end ---------"

#  echo "--------- platformIO start ---------"
#  rm -r $input-platformIO
#  rm obnizPlatformIO-v$input.zip
#  mkdir $input-platformIO
#  echo "Files copy"
#  cp -r ./cores ./$input-platformIO/cores
#  echo "- cores copied"
#  cp -r ./libraries ./$input-platformIO/libraries
#  echo "- libraries copied"
#  mkdir  $input-platformIO/tools
#  cp -r ./tools/*.exe ./tools/*.py  ./$input-platformIO/tools/
#  cp -r ./tools/partitions ./$input-platformIO/tools
#  cp -r ./tools/sdk ./$input-platformIO/tools
#  echo "- tools copied"
#  cp -r ./variants ./$input-platformIO/variants
#  echo "- variants copied"
#  cp *.txt package.json *.projbuild *.mk  ./$input-platformIO/
#  echo "- settingfiles copied"
#
#  echo "Create zip file"
#  zip -r -q obnizPlatformIO-v$input.zip $input-platformIO
#  echo "Created zip file"
#  SHA1=`sha1sum obnizPlatformIO-v$input.zip | cut -d " " -f 1`
#  FILE_SIZE=`wc -c < obnizPlatformIO-v$input.zip`
#  rm -r $input-platformIO
#  echo "Get checksum & file size"
#
#  echo ""
#  echo "Platform.json info"
#  echo ""
#
#  echo "\"url\": \"http://wamisnet.github.io/obnizPlatformIO-v$input.zip\","
#  echo "\"sha1\": \"$SHA1\","
#  echo "\"system\": \"*\","
#  echo "\"version\": \"$input\","
#
#  echo ""
#  echo "--------- platformIO end ---------"

fi

