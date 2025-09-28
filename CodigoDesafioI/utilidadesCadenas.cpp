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


bool buscarSubcadena(const char* cadenaPrincipal, const char* subcadena) {

    if (subcadena[0] == '\0') {
        return true;
    }

    for (int i = 0; cadenaPrincipal[i] != '\0'; i++) {
        bool encontrada = true;

        for (int j = 0; subcadena[j] != '\0'; j++) {
            if (cadenaPrincipal[i + j] == '\0') {
                encontrada = false;
                break;
            }

            if (cadenaPrincipal[i + j] != subcadena[j]) {
                encontrada = false;
                break;
            }
        }

        if (encontrada) {
            return true;
        }
    }

    return false;
}


