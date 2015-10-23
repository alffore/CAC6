
#include "cac6.h"

// variables de localidades

extern double *loc_lat;
extern double *loc_lon;

extern int cantloc;

// variables de recursos

extern double *rec_lat;
extern double *rec_lon;
extern int *rec_itipo;
extern int cantrec;


//variables locales


const double RT = 6378390.00;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


//variables locales DB

const char scc[]="hostaddr=127.0.0.1 port=5432 dbname=nuevadbrenic user=userrenic";

PGconn *conn=NULL;
PGresult *res=NULL;


//declaracion de funciones
void* calculoLocRec(void* parg);

int abreConexionBD(void);
int cierraConexionBD(void);
void insertaDatoBD(int i,int j,double dmin);

void algoritmo(void);


/**
* @brief Función que genera los hilos y distribuye en ellos la carga
*
*/
void algoritmo(void){
	
	int it;
	
	int iloc;
	pthread_t thread1, thread2;
	int  iret1, iret2;



	
	//abreConexionBD();
	
	
	
	for(it=0;it<22;it++){

		
		for(iloc=0;iloc<cantloc;iloc+=2){
			
			int parg1[2];
			parg1[0]=iloc;
			parg1[1]=it;
			
			iret1 = pthread_create( &thread1, NULL, calculoLocRec, (void*) parg1);

			int parg2[2];
			parg2[0]=iloc+1;
			parg2[1]=it;
			
			iret2 = pthread_create( &thread2, NULL, calculoLocRec, (void*) parg2);
			
			pthread_join( thread1, NULL);
		    pthread_join( thread2, NULL);

		}
		
	
	}
	
	//cierraConexionBD();
	
	
}






/**
* @brief Hilo de cálculo 
*/
void* calculoLocRec(void* parg){
	int j=0,jmin=0;
	
	//recupera el indice y el tipo de recurso
	int* loc_i=(int *)parg;
	int itipo=*(loc_i+1);
	
	if(*loc_i>=cantloc)return NULL;
	
	double daux,dmin;
	
	double lat_i=*(loc_lat+*loc_i);
	double lon_i=*(loc_lon+*loc_i);
	
	double lat_j=0;
	double lon_j=0;
	
	
	
	for(j=0; j<cantrec; j++ ){
		
		if(*(rec_itipo+j)!=itipo)
		
		lat_j=*(rec_lat+j);
		lon_j=*(rec_lon+j);
		
		daux=sin(lat_i)*sin(lat_j);
		daux+=cos(lat_i)*cos(lon_i)*cos(lat_j)*cos(lon_j);
		daux+=cos(lat_i)*sin(lon_i)*cos(lat_j)*sin(lon_j);
		
		daux=(daux>1)?1:(daux<-1)?-1:daux;    
    	daux=RT*acos(daux);
		
		if(j==0){
			dmin=daux;
			jmin=j;
		}else if(daux<dmin){
				dmin=daux;
				jmin=j;
			}			
							
	}
	
	
	
	pthread_mutex_lock( &mutex1 );

		insertaDatoBD(*loc_i,jmin,dmin);

	pthread_mutex_unlock( &mutex1 );

}

/**
*
*/
void insertaDatoBD(int i_loc,int j_rec,double dmin){
	
	printf("i_loc: %d, j_rec:%d, dmin:%f\n",i_loc,j_rec,dmin);
	
}


/**
 * @brief Función que abre una conexión a la BD
 *
 *
 */
int abreConexionBD(void){

	conn=PQconnectdb(scc);

	if(PQstatus(conn)!= CONNECTION_OK){
		fprintf(stderr,"Conexion a BD fallo: %s\n",PQerrorMessage(conn));
		cierraConexionBD();
		return 1;
	}


	return 0;
}


/**
 *
 * 
 */
int cierraConexionBD(void){

	if(conn!=NULL){
		PQfinish(conn);
	}


	return 0;
}