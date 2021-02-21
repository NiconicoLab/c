#!/bin/sh
echo start:`date`
ls
echo end:`date`
echo "$./hello"
./hello
echo "return vale :" $?
echo "$./hello test"
./hello test
echo "return vale :" $?
exit 0
