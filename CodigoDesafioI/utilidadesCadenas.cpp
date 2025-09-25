#include "utilidadesCadenas.h"

int longitudCadena(const char* cadena)
{
    if (cadena == nullptr) return 0;
    int longitud = 0;
    while(cadena[longitud] != '\0'){
        longitud++;
    }
    return longitud;
}
