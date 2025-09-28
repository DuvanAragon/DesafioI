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

bool compararCadenas(const char* cadenaA, int longitudCadenaA, const char* cadenaB, int longitudCadenaB)
{
    if (longitudCadenaA != longitudCadenaB)
    {
        return false;
    }
    for (int i = 0; i < longitudCadenaA; i++)
    {
        if (cadenaA[i] != cadenaB[i])
        {
            return false;
        }
    }

    return true;
}
