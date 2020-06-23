#!/bin/bash

echo "versionを入力してください"
read input

if [ -z $input ] ; then

  echo "スクリプトを終了します"
  exit 1

else

  rm -r $input
  rm obniz-v$input.zip
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
  zip -r -q obniz-v$input.zip $input
  echo "Created zip file"
  SHA256=`sha256sum obniz-v$input.zip | cut -d " " -f 1`
  FILE_SIZE=`wc -c < obniz-v$input.zip`
  rm -r $input
  echo "Get checksum & file size"

  echo ""
  echo "Package.json info"
  echo ""

  echo "\"url\": \"http://wamisnet.github.io/obniz-v$input.zip\","
  echo "\"checksum\": \"SHA-256:$SHA256\","
  echo "\"size\": \"$FILE_SIZE\","
  echo "\"archiveFileName\": \"obniz-v$input.zip\","
  echo "\"version\": \"$input\","

fi

