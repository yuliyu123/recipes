#!/usr/bin/env bash
 for file in ./*
 do
     if [ "${file##*.}"x = "cc"x ]||[ "${file##*.}"x = "cpp"x ]
     then
         echo $file will compiled as cpp file
         g++ -g -o ${file%.*} $file  ../build/libleveldb.a  -lpthread -I../build/include
     fi
     if test -d $file
     then
         echo $file is directory
     else
         echo $file is other file type
     fi
 done

# "${file##*.}"x = "cc"x --> 提取后缀
# ${file%.*} 提取前缀
