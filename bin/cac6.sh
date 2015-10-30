#!/bin/bash

#a_locs="/var/www/html/renic/utiles/cac2/salida_localidades.txt"
#a_recs="/var/www/html/renic/utiles/cac2/salida_ipc.txt"


a_locs="../datos_ex/salida_localidades.txt"
a_recs="../datos_ex/salida_ipc.txt"


locs=`cat $a_locs|wc -l`

recs=`cat $a_recs|wc -l`



./CAC6.exe $recs $locs $a_locs $a_recs

