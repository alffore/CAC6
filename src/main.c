/**
*
*/

#include "cac6.h"

// variables de localidades
int *loc_clave;
double *loc_lat;
double *loc_lon;
int *loc_pob;
int cantloc;

// variables de recursos
int *rec_clave;
double *rec_lat;
double *rec_lon;
int *rec_id;
int *rec_itipo;
int cantrec;


void asignaMemLoc(void);
void liberaMemLoc(void);

void asignaMemRec(void);
void liberaMemRec(void);


extern int recuperaInfoLoc(char * sarchivo);
extern int recuperaInfoRC(char * sarchivo);




/**
*
*/
int main(int argc, char** argv){
	
	
	cantloc=atoi(*(argv+1));
	cantrec=atoi(*(argv+2));
	
	asignaMemLoc();
	asignaMemRec();
	
	
	
	
	
	
	
	liberaMemRec();
	liberaMemLoc();
	
	return (EXIT_SUCCESS);
}

/**
*
*/
void asignaMemLoc(void){
	
	loc_clave=(int *) malloc(sizeof(int)*cantloc);
	loc_pob=(int *) malloc(sizeof(int)*cantloc);
	
	
	loc_lat=(double *)malloc(sizeof(double)*cantloc);
	loc_lon=(double *)malloc(sizeof(double)*cantloc);
}

/**
*
*/
void liberaMemLoc(void){
	
	if(loc_clave!=NULL)free(loc_clave);
	if(loc_pob!=NULL)free(loc_pob);
	
	if(loc_lat!=NULL)free(loc_lat);
	if(loc_lon!=NULL)free(loc_lon);
}

/**
*
*/
void asignaMemRec(void){
	rec_clave=(int *) malloc(sizeof(int)*cantrec);
	rec_id=(int *) malloc(sizeof(int)*cantrec);
	rec_itipo=(int *) malloc(sizeof(int)*cantrec);
	
	rec_lat=(double *)malloc(sizeof(double)*cantrec);
	rec_lon=(double *)malloc(sizeof(double)*cantrec);
}

/**
*
*/
void liberaMemRec(void){
	
	if(rec_clave!=NULL)free(rec_clave);
	if(rec_id!=NULL)free(rec_id);
	if(rec_itipo!=NULL)free(rec_itipo);
	
	if(rec_lat!=NULL)free(rec_lat);
	if(rec_lon!=NULL)free(rec_lon);
	
	
}