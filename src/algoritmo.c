
#include "cac6.h"

/*
#define NUM_THREADS 20
 */

// variables de localidades

extern double *loc_lat;
extern double *loc_lon;

extern int cantLocs;

// variables de recursos

extern double *rec_lat;
extern double *rec_lon;
extern int *rec_itipo;
extern int cantRecs;


//variables locales


const double RT = 6378390.00;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;



//variables locales DB

const char scc[] = "hostaddr=127.0.0.1 port=5432 dbname=nuevadbrenic user=userrenic";

PGconn *conn = NULL;
PGresult *res = NULL;


//declaracion de funciones
void* calculoLocRec(void* parg);

int abreConexionBD(void);
int cierraConexionBD(void);
void insertaDatoBD(int i, int* j, double* dmin, int th);

void algoritmo(void);

/**
 * @brief Función que genera los hilos y distribuye en ellos la carga
 *
 */
void algoritmo(void) {

   

    int iloc;
    pthread_t threads[NUM_THREADS];
    int t;
    int iret;




    //abreConexionBD();






    for (iloc = 0; iloc < cantLocs; iloc += NUM_THREADS) {

        for (t = 0; t < NUM_THREADS; t++) {

            int parg[2];
            parg[0] = iloc + t;
            parg[1] = t;


            //printf("thread: %d, iloc: %d, it: %d\n",t,parg[0],parg[1]);

            if ((iret = pthread_create(&threads[t], NULL, calculoLocRec, (void*) parg))) {
                fprintf(stderr, "error: pthread_create, iret: %d\n", iret);
            }

            pthread_join(threads[t], NULL);




        }
    }




    //cierraConexionBD();


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



    pthread_mutex_lock(&mutex1);


    insertaDatoBD(*loc_i, jmin, dmin, *(loc_i + 1));

    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);
}

/**
 *
 */
void insertaDatoBD(int i_loc, int* j_rec, double* dmin, int th) {

    int i;
    printf("th: %d, i_loc: %d\n", th, i_loc);
    for(i=0;i<=NUM_TEMAS;i++){
        printf("\t j_rec:%d, dmin:%f\n",*(j_rec+i), *(dmin+i));
        
    }

}

/**
 * @brief Función que abre una conexión a la BD
 *
 *
 */
int abreConexionBD(void) {

    conn = PQconnectdb(scc);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Conexion a BD fallo: %s\n", PQerrorMessage(conn));
        cierraConexionBD();
        return 1;
    }


    return 0;
}

/**
 *@brief Función que cirra la conexión a la BD
 * 
 */
int cierraConexionBD(void) {

    if (conn != NULL) {
        PQfinish(conn);
    }


    return 0;
}