:::::::: Encode
a.exe archivos/voltorb-hit.png comprimidos/voltorb-hit.cpr salidas/voltorb-hit.txt > salidas/resultadosCompresion.csv
::a.exe archivos/monalisa512.bmp comprimidos/monalisa512.cpr salidas/monalisa.txt  >> salidas/resultadosCompresion.csv
::a.exe archivos/entradaprueba.txt comprimidos/entradaprueba.cpr salidas/entradaprueba.txt >> salidas/resultadosCompresion.csv
::a.exe archivos/test.txt comprimidos/test.cpr salidas/test.txt >> salidas/resultadosCompresion.csv
::a.exe archivos/profileSata.itlu comprimidos/profileSata.cpr salidas/profileSata.txt >> salidas/resultadosCompresion.csv
::a.exe archivos/main.c comprimidos/main.cpr salidas/main.txt >> salidas/resultadosCompresion.csv
:::::::: Decode
::a.exe -d salidas/monalisa.txt comprimidos/monalisa512.cpr descomprimidos/MonalisaDesc.bmp
a.exe -d salidas/voltorb-hit.txt comprimidos/voltorb-hit.cpr descomprimidos/voltorb.png
::a.exe -d salidas/test.txt comprimidos/test.cpr
::a.exe -d salidas/entradaprueba.txt comprimidos/entradaprueba.cpr
::a.exe -d salidas/profileSata.txt comprimidos/profileSata.cpr descomprimidos/profileSataC.xml
::a.exe -d salidas/main.txt comprimidos/main.cpr
::a.exe -d salidas/test.txt salidas/t.txt
::>> salidas/resultados.txt