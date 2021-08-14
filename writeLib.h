#ifndef writeLib
#define writeLib
#include"various_utils.h"

//return "out_nx_ny_nz.txt"
char* get_FileOut_Name(multiplier m){
    char* result = malloc(13*sizeof(char));
    sprintf(result, "out.%d_%d_%d.txt", m.nx, m.ny, m.nz);
    return result;
}

void write_CELL_PARAMETERS(vector* vecs_list, multiplier reps, FILE* out, int vecs_length) {
    char* header = malloc(20*sizeof(char));
    header = "CELL_PARAMETERS { angstrom }\n";

    fprintf(out, "%s", header);
    for(int i = 0; i < vecs_length; ++i) {
        vector multiplied = getSupercellVector(vecs_list[i], reps, i);
        fprintf(out, "%s", vecToString(multiplied));
    }
    
}

void fill_ATOMIC_POSITIONS(atom* atoms_list, vector* vecs_list, multiplier reps, FILE* out, fileStruct fs){
    char* header = malloc(20*sizeof(char));
    header = "ATOMIC_POSITIONS { angstrom }\n";

    fprintf(out, "%s", header);
    int n_basis = reps.nx*reps.ny*reps.nz;
    vector* vecs_reps = malloc(n_basis*sizeof(vector));
    int index_reps = 0;

    //create translation vectors
    for(int x=0; x < reps.nx; ++x){
        for(int y=0; y < reps.ny; ++y){
            for(int z=0; z < reps.nz; ++z){
                vecs_reps[index_reps++] = getLinearCombination(vecs_list, x, y, z);
            }
        }
    }

    //translate atomic basis
    for(int j=0; j < index_reps; ++j){
        for(int i = 0; i < fs.nAtomLines; ++i){
            atom at_transl = translatedAtom(atoms_list[i], vecs_reps[j]);
            fprintf(out, "%s", atomToString(at_transl));
        }
    }

}

int write_output(vector* vecs_list, atom* atoms_list, multiplier reps, fileStruct fs){
    char* fileOut_Name = "out.txt";

    FILE* out = fopen(fileOut_Name, "w");
    int lines = 0;
    
    write_CELL_PARAMETERS(vecs_list, reps, out, fs.nPrimvecLines);
    fill_ATOMIC_POSITIONS(atoms_list, vecs_list, reps, out, fs);
    fclose(out);
    return 0;
}
#endif