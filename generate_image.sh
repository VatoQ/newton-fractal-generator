#!/bin/bash
make

./main &> output.txt

python make_png.py
