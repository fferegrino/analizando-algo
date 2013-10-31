:: Forma de invocación para codificar
::	a.exe ruta_archivo_a_codificar ruta_archivo_codificado ruta_tabla_de_frecuencias
a.exe "C:\Users\Antonio\Dropbox\CSharpsKit.psd" comprimidos/psd.comprimido salidas/psd.txt 
:: Forma de invocación para descodificar
::	a.exe -d ruta_tabla_de_frecuencias ruta_archivo_codificado ruta_de_archvo_descomprimido
a.exe -d salidas/psd.txt comprimidos/psd.comprimido descomprimidos/x.sql
::>> salidas/resultados.txt