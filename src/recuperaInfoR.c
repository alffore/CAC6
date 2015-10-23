#include "cac6.h"



int recuperaInfoRC(char * sarchivo);
int obtenClaveRec(char * stipo);

extern int *rec_clave;
extern double *rec_lat;
extern double *rec_lon;
extern int *rec_id;
extern int *rec_itipo;
int cantrec;




int recuperaInfoRC(char * sarchivo) {

   	int i=0;
    
    int id, edo_id, mun_id, loc_id;
    double lat, lon;
    char stipo[20];

    FILE *fh = fopen(sarchivo, "r");
    while (!feof(fh)) {
        if (fscanf(fh, "%d %d %d %lf %lf %s %d", &edo_id, &mun_id, &loc_id, &lat, &lon, stipo, &id) != 7) break;

        
        *(rec_clave+i)=(edo_id*100+mun_id)*1000+loc_id;
        *(rec_lat+i)=M_PI*lat/180.0;
        *(rec_lon+i)=M_PI*lon/180.0;
        *(rec_itipo+i)=obtenClaveRec(stipo);
        *(rec_id+i)=id;
        
       
		i++;
    }
    printf("cuentaRec: %d\n", i);
    fclose(fh);
    return i;
}


int obtenClaveRec(char * stipo){
    
    if(strcmp(stipo,"auditorio")==0){
        return auditorio;   
    }
    
    if(strcmp(stipo,"biblioteca")==0){
        return biblioteca;   
    }
    
     if(strcmp(stipo,"casa_c")==0){
        return casa_c;   
    }
     if(strcmp(stipo,"centro_c")==0){
        return centro_c;   
    }
     if(strcmp(stipo,"centro_cultural")==0){
        return centro_cultural;   
    }
     if(strcmp(stipo,"fnme")==0){
        return fnme;   
    }
     if(strcmp(stipo,"fonoteca")==0){
        return fonoteca;   
    }
     if(strcmp(stipo,"fototeca")==0){
        return fototeca;   
    }
     if(strcmp(stipo,"galeria")==0){
        return galeria;   
    }
     if(strcmp(stipo,"libreria")==0){
        return libreria;   
    }
     if(strcmp(stipo,"museo")==0){
        return museo;   
    }
     if(strcmp(stipo,"museo_ant")==0){
        return museo_ant;   
    }
     if(strcmp(stipo,"museo_arq")==0){
        return museo_arq;   
    }
     if(strcmp(stipo,"museo_art")==0){
        return museo_art;   
    }
     if(strcmp(stipo,"museo_cyt")==0){
        return museo_cyt;   
    }
     if(strcmp(stipo,"museo_esp")==0){
        return museo_esp;   
    }
     if(strcmp(stipo,"museo_his")==0){
        return museo_his;   
    }
     if(strcmp(stipo,"otra_bib")==0){
        return otra_bib;   
    }
     if(strcmp(stipo,"patrimonio_humanidad")==0){
        return patrimonio_humanidad;   
    }
     if(strcmp(stipo,"teatro")==0){
        return teatro;   
    }
     if(strcmp(stipo,"universidad")==0){
        return universidad;   
    }
     if(strcmp(stipo,"zona_arqueologica")==0){
        return zona_arqueologica;   
    }
  
    return -1;
}