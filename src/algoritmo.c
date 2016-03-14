/**
 * https://computing.llnl.gov/tutorials/pthreads/#Overview
 */
#include "cac6.h"



// variables de localidades
extern int *loc_clave;
extern double *loc_lat;
extern double *loc_lon;
extern int *loc_pob;
extern int cantLocs;

// variables de recursos
extern int *rec_clave;
extern double *rec_lat;
extern double *rec_lon;
extern int *rec_itipo;
extern int *rec_id;
extern int cantRecs;


//variables locales


const double RT = 6378390.00;
FILE *fh;



char* stipos[] = {
    "auditorio",
    "biblioteca",
    "casa_c",
    "centro_c",
    "centro_cultural",
    "fnme",
    "fonoteca",
    "fototeca",
    "galeria",
    "libreria",
    "museo",
    "museo_ant",
    "museo_arq",
    "museo_art",
    "museo_cyt",
    "museo_esp",
    "museo_his",
    "otra_bib",
    "patrimonio_humanidad",
    "teatro",
    "universidad",
    "zona_arqueologica",
    "centro_educacion"
};


PGconn *conn = NULL;
PGresult *res = NULL;


//declaracion de funciones
void* calculoLocRec(void* parg);


void insertaDato(int i, int* j, double* dmin, int th);
int abreArchivo(void);
void cierraArchivo(void);


void algoritmo(void);

/**
 * @brief Función que genera los hilos y distribuye en ellos la carga
 *
 */
void algoritmo(void) {

    int iloc;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int t;
    int iret;
    void *status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    if (abreArchivo() == 1)return;

    for (iloc = 0; iloc < cantLocs; iloc += NUM_THREADS) {

        for (t = 0; t < NUM_THREADS; t++) {

            int parg[2];
            parg[0] = iloc + t;
            parg[1] = t;

            if ((iret = pthread_create(&threads[t], &attr, calculoLocRec, (void*) parg))) {
                fprintf(stderr, "error: pthread_create, iret: %d\n", iret);
            }

        } 

        for (t = 0; t < NUM_THREADS; t++) {
            iret = pthread_join(threads[t], &status);
            if (iret) {
                fprintf(stderr,"ERROR; return code from pthread_join() is %d\n", iret);
                return;
            }
            //printf("Completed join with thread %d having a status of %ld\n", t, (long) status);
        }

    }
    pthread_attr_destroy(&attr);
    cierraArchivo();

    pthread_exit(NULL);
}

/**
 * @brief Hilo de cálculo 
 */
void* calculoLocRec(void* parg) {
    int j = 0;
    int jmin[NUM_TEMAS];

    //recupera el indice y el tipo de recurso
    int* loc_i = (int *) parg;
    int itipo = 0;

    if (*loc_i >= cantLocs)pthread_exit(NULL);

    double daux = RT;
    double dmin[NUM_TEMAS];

    double lat_i = *(loc_lat + *loc_i);
    double lon_i = *(loc_lon + *loc_i);

    double lat_j = 0;
    double lon_j = 0;


    for (j = 0; j <= NUM_TEMAS; j++) {
        dmin[j] = RT;
    }


    for (j = 0; j < cantRecs; j++) {

        itipo = *(rec_itipo + j);

        lat_j = *(rec_lat + j);
        lon_j = *(rec_lon + j);

        daux = sin(lat_i) * sin(lat_j);
        daux += cos(lat_i) * cos(lon_i) * cos(lat_j) * cos(lon_j);
        daux += cos(lat_i) * sin(lon_i) * cos(lat_j) * sin(lon_j);

        daux = (daux > 1) ? 1 : (daux<-1) ? -1 : daux;
        daux = RT * acos(daux);

        if (daux < dmin[itipo]) {
            dmin[itipo] = daux;
            jmin[itipo] = j;
        }

    }



    insertaDato(*loc_i, jmin, dmin, *(loc_i + 1));




    pthread_exit(NULL);
}

/**
 *
 */
void insertaDato(int i_loc, int* j_rec, double* dmin, int th) {

    int i;

    int localidad_id = *(loc_clave + i_loc)-(int) floor(*(loc_clave + i_loc) / 10000)*10000;
    int estado_id = (int) (*(loc_clave + i_loc) / 10000000);
    int municipio_id = (int) (*(loc_clave + i_loc) - estado_id * 10000000 - localidad_id) / 10000;

    int localidadd_id = 0;
    int municipiod_id = 0;
    int estadod_id = 0;
    int j = 0;

    for (i = 0; i <= NUM_TEMAS; i++) {

        j = *(j_rec + i);

        localidadd_id = *(rec_clave + j)-(int) floor(*(rec_clave + j) / 10000)*10000;
        estadod_id = (int) (*(rec_clave + j) / 10000000);
        municipiod_id = (int) (*(rec_clave + j) - estadod_id * 10000000 - localidadd_id) / 10000;

        fprintf(fh, "%d,%d,%d,%s,%d,%.6f,%d,%d,%d,%d\n", estado_id, municipio_id, localidad_id, stipos[*(rec_itipo + j)], *(loc_pob + i_loc), *(dmin + i), estadod_id, municipiod_id, localidadd_id, *(rec_id + j));

    }


}

/**
 * 
 * @return 
 */
int abreArchivo(void) {

    fh = fopen("salida.csv", "w");
    if (fh == NULL) {
        return 1;
    }

    fprintf(fh, "estado_id,municipio_id,localidad_id,recurso,pobtot,dist,estadod_id,municipiod_id,localidadd_id,recurso_id\n");

    return 0;
}

/**
 * 
 */
void cierraArchivo() {
    if (fh != NULL) {
        fclose(fh);
    }
}