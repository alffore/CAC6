/**
 *
 */

#include "cac6.h"

// variables de localidades
int *loc_clave;
double *loc_lat;
double *loc_lon;
int *loc_pob;
int cantLocs;

// variables de recursos
int *rec_clave;
double *rec_lat;
double *rec_lon;
int *rec_id;
int *rec_itipo;
int cantRecs;


void asignaMemLoc(void);
void liberaMemLoc(void);

void asignaMemRec(void);
void liberaMemRec(void);

void imprimeLocs(void);
void imprimeRecs(void);



//funciones externas
extern int recuperaInfoLoc(char * sarchivo);
extern int recuperaInfoRC(char * sarchivo);

extern void algoritmo(void);



/**
 *
 */
int main(int argc, char** argv) {

    
    clock_t t;
    t = clock();
    
    

    if (argc < 5) {
        fprintf(stderr, "Error: parámetros incompletos (%d)\n", argc);
        return (EXIT_FAILURE);
    }

    cantLocs = atoi(*(argv + 1));
    cantRecs = atoi(*(argv + 2));

    asignaMemLoc();
    asignaMemRec();


    recuperaInfoLoc(*(argv + 3));
    //imprimeLocs();
    recuperaInfoRC(*(argv + 4));
    //imprimeRecs();

    algoritmo();


    liberaMemRec();
    liberaMemLoc();

    
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("Tomo %f segundos to execute T(%d) \n", time_taken,NUM_THREADS);
    
    
    return (EXIT_SUCCESS);
}

/**
 *
 */
void asignaMemLoc(void) {

    loc_clave = (int *) malloc(sizeof (int)*cantLocs);
    loc_pob = (int *) malloc(sizeof (int)*cantLocs);


    loc_lat = (double *) malloc(sizeof (double)*cantLocs);
    loc_lon = (double *) malloc(sizeof (double)*cantLocs);
}

/**
 *
 */
void liberaMemLoc(void) {

    if (loc_clave != NULL)free(loc_clave);
    if (loc_pob != NULL)free(loc_pob);

    if (loc_lat != NULL)free(loc_lat);
    if (loc_lon != NULL)free(loc_lon);
}

/**
 *
 */
void asignaMemRec(void) {
    rec_clave = (int *) malloc(sizeof (int)*cantRecs);
    rec_id = (int *) malloc(sizeof (int)*cantRecs);
    rec_itipo = (int *) malloc(sizeof (int)*cantRecs);

    rec_lat = (double *) malloc(sizeof (double)*cantRecs);
    rec_lon = (double *) malloc(sizeof (double)*cantRecs);
}

/**
 *
 */
void liberaMemRec(void) {

    if (rec_clave != NULL)free(rec_clave);
    if (rec_id != NULL)free(rec_id);
    if (rec_itipo != NULL)free(rec_itipo);

    if (rec_lat != NULL)free(rec_lat);
    if (rec_lon != NULL)free(rec_lon);


}


void imprimeLocs(void){
    int i;
    for(i=0;i<cantLocs;i++){
        
        printf("%d::::clave:%d p: %d lon:%f lat:%f\n",i,*(loc_clave+i),*(loc_pob+i),*(loc_lon+i),*(loc_lat+i));
        
    }
}


void imprimeRecs(void){
    int i;
    
    for(i=0;i<cantRecs; i++){
        printf("%d::::clave: %d tipo: %d lon:%f lat:%f\n", i, *(rec_clave+i),*(rec_itipo+i),*(rec_lon+i),*(rec_lat+i));
        
    }
}