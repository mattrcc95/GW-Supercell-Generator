HOW TO:
1) edit the opt.txt file, choosing the # units desired, DON'T change PRIMVEC, PRIMCOORD AND NREPS FLAGS!
2) compile the driver -> chmod +x driver.sh
3) execute the driver -> ./driver.sh
4) vi opens showing the QE input file created.
5) IMPORTANT!! NOTE THAT NATOMS AND NTYPES ARE MISSING-> CHANGE THEM BY HAND


NB: in the TiS2 case, the only parameter in the opt.txt file that should be changed is the # units.
    This can be used for other materials, just put in the PRIMVEC section the appropriate cell vectors (IN ANGSTROM AND 
    SEPARATED BY SINGLE SPACE),
    then put in the PRIMCOORD section the atomic basis of interest (ALWAYS ANGSTROM AND SINGLE SPACE) and finally change NREPS section as desired.
    int this case, modify by hand the ATOMIC_SPECIES section as well.
    Remember to use always single space between everything, no tabs, no multiple spaces, etc otherwise it won't work.
    Finally, modify the skeleton.scf.in file only if needed, since it is used to generate the final QE input file. 
