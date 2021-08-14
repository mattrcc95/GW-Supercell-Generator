#ifndef various_utils
#define various_utils
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"type_utils.h"

void printFileStructure(fileStruct fs){
    printf("# of primvec lines: %d\n", fs.nPrimvecLines);
    printf("# of atom lines: %d\n", fs.nAtomLines);
}

char* vecToString(vector v){
    char* vec_string = malloc(50*sizeof(char));
    sprintf(vec_string, "%lf\t%lf\t%lf\n", v.x, v.y, v.z);
    return vec_string;
}

char* atomToString(atom at){
    char* atom_string = malloc(60*sizeof(char));
    sprintf(atom_string, "%s\t%s", at.flag, vecToString(at.v_atom));
    return atom_string;
}

char* printMultiplier(multiplier m){
    printf("nx reps: %d\t", m.nx); printf("ny reps: %d\t", m.ny); printf("nz reps: %d\n", m.nz);
}

int vecCopy(vector* vecTo, vector vecFrom){
    if(vecTo){
        vecTo->x = vecFrom.x; vecTo->y = vecFrom.y; vecTo->z = vecFrom.z;
        return EXIT_CODE_OK;
    } 
    else{return EXIT_CODE_KO;}
}

int atomCopy(atom* atTo, atom atFrom){
    if(atTo){
        atTo->flag = malloc(10*sizeof(char));
        strcpy(atTo->flag, atFrom.flag);
        atTo->v_atom.x = atFrom.v_atom.x; atTo->v_atom.y = atFrom.v_atom.y; atTo->v_atom.z = atFrom.v_atom.z;
        return EXIT_CODE_OK;
    }
    else{return EXIT_CODE_KO;}
}


vector getMultipliedVector(vector v, int factor){
    vector v_res;
    v_res.x = factor*v.x; v_res.y = factor*v.y; v_res.z = factor*v.z;
    return v_res;
}

vector getSupercellVector(vector v, multiplier m, int index){
    if(index == 0) return getMultipliedVector(v, m.nx);
    else if (index == 1) return getMultipliedVector(v, m.ny);
    else return getMultipliedVector(v, m.nz);
}

vector getSum(vector v1, vector v2){
    vector v_res;
    v_res.x = v1.x + v2.x;
    v_res.y = v1.y + v2.y;
    v_res.z = v1.z + v2.z;
    return v_res;
}

atom translatedAtom(atom at, vector transl){
    atom at_res;
    at_res.flag = malloc(2*sizeof(char)); strcpy(at_res.flag, at.flag);
    at_res.v_atom = getSum(at.v_atom, transl);
    return at_res;
}

vector getLinearCombination(vector* vecs_basis, int fx, int fy, int fz){
    vector v_out;
    vector v1 = vecs_basis[0]; vector v2 = vecs_basis[1]; vector v3 = vecs_basis[2];
    double x_component = fx*v1.x + fy*v2.x + fz*v3.x;
    double y_component = fx*v1.y + fy*v2.y + fz*v3.y;
    double z_component = fx*v1.z + fy*v2.z + fz*v3.z;
    v_out.x = x_component; v_out.y = y_component; v_out.z = z_component;
    return v_out;
}
#endif
