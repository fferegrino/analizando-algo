echo Pruebas iniciadas %DATE% %TIME%
::a.exe archivos/voltorb-hit.png comprimidos/voltorb-hit.cpr salidas/voltorb-hit.txt > salidas/resultados.txt
a.exe archivos/lorem.txt comprimidos/lorem.cpr salidas/lorem.txt >> salidas/resultados.txt
::a.exe archivos/profileSata.itlu comprimidos/profileSata.cpr salidas/profileSata.txt >> salidas/resultados.txt
::a.exe archivos/monalisa512.bmp comprimidos/monalisa512.cpr salidas/monalisa.txt >> salidas/resultados.txt
::a.exe -d salidas/monalisa.txt archivos/monalisa512.bmp comprimidos/monalisa512.cpr
a.exe -d salidas/lorem.txt archivos/lorem.txt comprimidos/lorem.cpr
::a.exe -d salidas/profileSata.txt archivos/profileSata.itlu comprimidos/profileSata.cpr
::a.exe -d salidas/monalisa.txt archivos/monalisa512.bmp comprimidos/monalisa512.cpr