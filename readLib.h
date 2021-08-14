#ifndef readLib
#define readLib
#include"various_utils.h"

fileStruct getFileStructure(FILE* opt){
    char *line = NULL; 
    size_t len = 0;
    ssize_t read; 
    fileStruct fs;
    int primvec_counter = 0;
    int atom_counter = 0;
    boolean isReadingAtoms = F;
    boolean isReadingVecs = F;
    
    while ((read = getline(&line, &len, opt)) != -1) {   
        //format the line
        line[strlen(line)-1] = '\0'; 
        if(strcmp(line, PRIMVEC_FLAG) == 0) isReadingVecs = T;
        if(strcmp(line, ATOM_FLAG) == 0) {isReadingAtoms = T; isReadingVecs = F;}
        if(strcmp(line, MULTIPLIER_FLAG) == 0) break;
        if(isReadingVecs) ++primvec_counter;
        if(isReadingAtoms == T) ++atom_counter;   
    }

    free(line);
    rewind(opt);

    fs.nPrimvecLines = primvec_counter-1; fs.nAtomLines = atom_counter-1; 
    return fs;
}

vector getPrimvec(char* line){
    vector output;
    double array_tmp[3];
    int index = 0;

    char* token = strtok(line, space_delim);

    while(token != NULL) {
        array_tmp[index++] = atof(token);
        token = strtok(NULL, space_delim);
    }

    output.x = array_tmp[0]; output.y = array_tmp[1]; output.z = array_tmp[2];
    return output;
}

atom getAtom(char* line){
    atom output;
    double array_tmp[3];
    int index = 0;
    
    char* token = strtok(line, space_delim);
    output.flag = token;
    token = strtok(NULL, space_delim);
    
    while(token != NULL){
        array_tmp[index++] = atof(token);
        token = strtok(NULL, space_delim);
    }

    output.v_atom.x = array_tmp[0]; output.v_atom.y = array_tmp[1]; output.v_atom.z = array_tmp[2];
    return output;
}

multiplier getMultiplier(char* line){
    multiplier output;
    int array_tmp[3];
    int index = 0;

    char* token = strtok(line, space_delim);

    while(token != NULL) {
        array_tmp[index++] = atoi(token);
        token = strtok(NULL, space_delim);
    }

    output.nx = array_tmp[0]; output.ny = array_tmp[1]; output.nz = array_tmp[2];
    return output;
}

fileStruct getParams(vector** vecs_list, atom** atoms_list, multiplier* reps, char* fileName){
    FILE* opt = fopen(fileName, "r");
    int lines = 0;
    //read variables
    char *line = NULL; 
    size_t len = 0;
    ssize_t read; 

    if(opt == NULL){
        fprintf(stdout, "error opening %s file", fileName);
        exit(EXIT_FAILURE);
    }

    //preprocess
    fileStruct fs = getFileStructure(opt);

    //variables to store into references
    int index_vec = 0;
    vector* new_vecs_list;
    new_vecs_list = realloc(*vecs_list, fs.nPrimvecLines*sizeof(vector));

    int index_atom = 0;
    atom* new_atom_list;
    new_atom_list = realloc(*atoms_list, fs.nAtomLines*sizeof(atom));

    if(new_vecs_list && new_atom_list){    
        while ((read = getline(&line, &len, opt)) != -1) {
            //line formatter (-> delete \n at the end)
            line[strlen(line)-1] = '\0';

            if(lines > 0 && lines <= fs.nPrimvecLines){
                int code = vecCopy(&new_vecs_list[index_vec++], getPrimvec(line));
                if(code==-1) {
                    fprintf(stderr, "ERROR IN PRIMVEC SECTION");
                    exit(EXIT_FAILURE);
                }
            }  
            else if(lines > (fs.nPrimvecLines + 1) && lines <=  ((fs.nPrimvecLines + 1) + (fs.nAtomLines))){
                int code = atomCopy(&new_atom_list[index_atom++], getAtom(line));
                if(code==-1) {
                    fprintf(stderr, "ERROR IN PRIMVEC SECTION");
                    exit(EXIT_FAILURE);
                }
            }         
            else if(lines > ( (fs.nPrimvecLines + 1) + ((fs.nAtomLines) + 1 )) ){
                multiplier mult_tmp = getMultiplier(line);
                reps->nx = mult_tmp.nx; reps->ny = mult_tmp.ny; reps->nz = mult_tmp.nz;
            }           
            lines++;           
        }
    }

    else{printf("REALLOC FAILED\n");} 
    *vecs_list = new_vecs_list;
    *atoms_list = new_atom_list;

    fclose(opt);
    
    return fs;
}
#endif

