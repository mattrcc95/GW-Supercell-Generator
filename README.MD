HOW TO:
1) edit the opt.txt file, choosing the # units desired, DON'T change PRIMVEC, PRIMCOORD AND NREPS FLAGS!
2) compile the driver -> chmod +x driver.sh.
3) execute the driver -> ./driver.sh
4) once the execution is completed, VI editor opens, showing the QE input file created (supercell.scf.in).
5) IMPORTANT!! NOTE THAT IN THE OUTPUT FILE (supercell.scf.in) THE PREFIX, NAT AND NTYPS FLAGS ARE EMPTY-> FILL THEM BY HAND


NB:  in the TiS2 case, the only parameter in the opt.txt file that should be changed is the # units.
     NORMCONS PPs are provided in the PPs folder.

NB2: This code can be used for other materials as well, just put in the PRIMVEC section the appropriate unit cell vectors 
     then put in the PRIMCOORD section the atomic basis of interest and finally change NREPS section as desired. 
     In this case, modify by hand the ATOMIC_SPECIES section of the skeleton.scf.in as well.

NB3: ALWAYS USE SINGLE SPACE BETWEEN EVERYTHING otherwise it won't work.

NB4: Modify the skeleton.scf.in file only if needed, since it is used to generate the final QE input file. 
