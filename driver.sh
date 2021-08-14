#!/bin/sh
#compile and run the program
gcc -o supercell_generator.exe supercell_generator.c
./supercell_generator.exe opt.txt

#create a copy of the skeleton file
cp skeleton.scf.in supercell.scf.in

#copy content of opt.txt after line 24 of tmp
sed -i 27rout.txt supercell.scf.in

#open editor to change ,anually nat and ntypes
vi supercell.scf.in
