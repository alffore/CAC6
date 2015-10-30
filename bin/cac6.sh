#!/bin/bash


locs=`cat /var/www/html/renic/utiles/cac2/salida_localidades.txt|wc -l`

recs=`cat /var/www/html/renic/utiles/cac2/salida_ipc.txt|wc -l`

#./CAC6.exe 4844 1654 ../datos_ex/salida_localidades_15.txt ../datos_ex/salida_ipc_15.txt

./CAC6.exe $recs $locs ../datos_ex/salida_localidades.txt ../datos_ex/salida_ipc.txt

