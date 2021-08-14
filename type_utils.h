#ifndef type_utils
#define type_utils

const char* space_delim = " ";
const char* PRIMVEC_FLAG = "PRIMVEC";
const char* ATOM_FLAG  = "PRIMCOORD";
const char* MULTIPLIER_FLAG = "NREPS";
typedef enum { F, T } boolean;
const int EXIT_CODE_OK = 0;
const int EXIT_CODE_KO = -1;
const int EXIT_CODE_EXCEPTION = 1;

//useful types
typedef struct{
    int nPrimvecLines;
    int nAtomLines;
} fileStruct;

typedef struct{
    double x;
    double y;
    double z;
}vector;

typedef struct{
    char* flag;
    vector v_atom;
} atom;

typedef struct{
    int nx;
    int ny;
    int nz;
} multiplier;
#endif