#!/bin/bash

cd src
make
rm *.o
mv program ../
