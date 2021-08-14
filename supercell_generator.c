#include "readLib.h"
#include "writeLib.h"

int main(int argc, char *argv[]) {
    vector* vecs_list = NULL;
    atom* atoms_list = NULL;
    multiplier reps;

    fileStruct fs = getParams(&vecs_list, &atoms_list, &reps, argv[1]);
    int exit_code = write_output(vecs_list, atoms_list, reps, fs);
    return 0;

}


