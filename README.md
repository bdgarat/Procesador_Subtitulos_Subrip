# Procesador_Subtitulos_Subrip
Procesador de subtitulos (Subrip) Realizado en C

Realizado por: Giuliano De Pian y Braian David Garat

Presentado como Trabajo Practico Integrador (TPI) del Seminario de lenguajes, Opcion C de la Facultad de Informatica de la UNLP

Funcionalidad:
El programa deber´a permitir manipular archivos SubRip. Para ello aceptar´a los siguientes par´ametros:
-f filein ← file es el archivo a procesar.
-o fileout ← fileout es el archivo donde se guardar´an los cambios.
-b index ← borra el subt´ıtulo n´umero index.
-i startmilis endmillis texto ← inserta el subt´ıtulo texto en startmilis con duraci´on
hasta endmillis, corrige todos los ´ındices de los subt´ıtulos siguientes.
-v ← valida el subt´ıtulo buscando los siguientes errores:
• Los n´umeros de ´ındice dentro del archivo no son n´umeros consecutivos ordenados.
• Los n´umeros de ´ındice no arrancan en 1.
• Los subt´ıtulos est´an solapados (el tiempo de fin del subt´ıtulo i es mayor o
igual al tiempo de inicio del subt´ıtulo i + 1).
• Dura menos de 1 segundo.
• Dura m´as de 7 segundos.
• Tiene l´ıneas demasiado largas (m´as de 36 caracteres).
• Tiene demasiados caracteres por segundo (m´as de 25).
• Tiene m´as de 2 l´ıneas.
• Hay menos de 75 milisegundos entre el final del subt´ıtulo i y el principio del
i + 1.
Si la validaci´on encuentra alg´un error programa deber´a imprimir el n´umero de
´ındice del subt´ıtulo y una descripci´on del error, y deber´a seguir validando el archivo
en busca de m´as errores. Luego deber´a seguir procesando el resto de los par´ametros
por m´as que alguna validaci´on falle.
Modo de procesar los par´ametros:
El par´ametro -f es obligatorio y no se puede repetir.
El par´ametro -o es obligatorio cuando hay opciones que modifican al archivo (todas
excepto -v) y no se puede repetir.
El resto de los par´ametros son opcionales, pueden repetirse y las acciones que
representan deben ejecutarse en orden.
Si un par´ametro se repite, la acci´on indicada por el mismo deber´a repetirse.
Los par´ametros se reciben en cualquier orden (es conveniente hacer 2 pasadas, en la
primera se procesan -f y -o, y en la segunda se procesa el resto de los par´ametros).
Si se recibe m´as de un -f o -o el programa deber´a mostrar un mensaje de ayuda
con los par´ametros v´alidos y terminar con c´odigo de salida 1.
Si no se recibe un par´ametro obligatorio deber´a mostrar la ayuda anterior y terminar con c´odigo de salida 2.
Si se recibe un par´ametro inv´alido (por ejemplo: -z o -cM ) deber´a mostrar la ayuda
anterior y terminar con c´odigo de salida 3.
Si no se puede abrir el archivo de entrada o el de salida, el programa deber´a mostrar
un error indicando el nombre del archivo que no pudo abrir y terminar con c´odigo de
salida 4.
Por ejemplo la siguiente invocaci´on al programa verifica los errores, luego agrega una
entrada a las 7000 milisegundos (que se mostrar´a hasta las 8200 milisegundos) con el
texto .A la grande le puse Cuca”, verifica el resultado, borra el subt´ıtulo 3 y verifica el
resultado:
./tpintegrador -v -f "los_simpsons.srt" -o "salida.srt" -i 7000 8200 "A la grande le puse Cuca" -v -b 3 -v
Subt´ıtulos para probar: http://www.subdivx.com/X2X-subtitulos.html
Nota 1: Se puede usar cualquier funcionalidad incluida en GNU libc.
Nota 2: Oficialmente la pel´ıcula m´as larga de la historia “La cura para el insomnio”2
dura 5.220 minutos, unos 313.200.000 milisegundos, tener esto en cuenta a la hora de
almacenar los tiempos y duraciones.
