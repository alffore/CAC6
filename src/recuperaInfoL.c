
#include "cac6.h"

int recuperaInfoLoc(char * sarchivo);

extern int *loc_clave;
extern double *loc_lat;
extern double *loc_lon;
extern int *loc_pob;
extern int cantloc;


/**
 * 
 * @param sarchivo
 * @return 
 */
int recuperaInfoLoc(char * sarchivo) {

    
    PLocalidad pr = PLr;

    int edo_id, mun_id, loc_id, pob;
    double lat, lon;
    int i=0;


    FILE *fh = fopen(sarchivo, "r");

    while (!feof(fh)) {
        if (fscanf(fh, "%d %d %d %lf %lf %d", &edo_id, &mun_id, &loc_id, &lat, &lon, &pob) != 6) break;
        
        *(loc_clave+i)=(edo_id*100+mun_id)*1000+loc_id;
        *(loc_lat+i)=lat;
        *(loc_lon+i)=lon;
        *(loc_pob+i)=pob;

        i++;
    }
    printf("cuentaLoc: %d\n", i);
    fclose(fh);
    return i;
}
