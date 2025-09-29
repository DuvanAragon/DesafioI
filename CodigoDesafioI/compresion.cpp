#include "compresion.h"
#include "utilidadesBytes.h"

int tamanoRealDescomprimidoRLE(const unsigned char* textoComprimido, int tamanoTextoComprimido)
{
    int tamano = 0;

    for (int i = 0; i < tamanoTextoComprimido; i += 3) {
        unsigned char byteAlto = textoComprimido[i];
        unsigned char byteBajo = textoComprimido[i + 1];
        unsigned short vecesRepetido = unirBytes(byteBajo, byteAlto);

        tamano += vecesRepetido;
    }

    return tamano;
}

char* descompresionRLE(const unsigned char* textoComprimido, int tamanoTextoComprimido)
{
    int tamanoReal = tamanoRealDescomprimidoRLE(textoComprimido, tamanoTextoComprimido);

    char* textoDescomprimido = new char[tamanoReal + 1];

    int indiceSalida = 0;

    for (int i = 0; i < tamanoTextoComprimido; i += 3) {
        unsigned char byteAlto = textoComprimido[i];
        unsigned char byteBajo = textoComprimido[i + 1];
        unsigned char caracter = textoComprimido[i + 2];

        unsigned short vecesRepetido = unirBytes(byteBajo, byteAlto);

        for (int j = 0; j < vecesRepetido; j++) {
            textoDescomprimido[indiceSalida] = static_cast<char>(caracter);
            indiceSalida++;
        }
    }

    textoDescomprimido[indiceSalida] = '\0';
    return textoDescomprimido;
}

char* descompresionLZ78(unsigned char* textoComprimido, int tamanoComprimido, int &tamanoDescomprimido) {
    if (tamanoComprimido % 3 != 0 || tamanoComprimido == 0) {
        tamanoDescomprimido = 0;
        return nullptr;
    }

    int capacidad = tamanoComprimido * 3;
    char* textoDescomprimido = new char[capacidad];
    int indiceSalida = 0;

    int maxEntradas = tamanoComprimido / 3;
    char** diccionarioCadenas = new char*[maxEntradas];
    int* diccionarioLongitudes = new int[maxEntradas];
    int cantidadEntradas = 0;

    for (int i = 0; i < tamanoComprimido; i += 3) {
        unsigned char byteAlto = textoComprimido[i];
        unsigned char byteBajo = textoComprimido[i + 1];
        unsigned char caracterNuevo = textoComprimido[i + 2];

        unsigned short indicePrefijo = unirBytes(byteBajo, byteAlto);

        const char* prefijo = "";
        int longitudPrefijo = 0;

        if (indicePrefijo > 0 && indicePrefijo <= cantidadEntradas) {
            prefijo = diccionarioCadenas[indicePrefijo - 1];
            longitudPrefijo = diccionarioLongitudes[indicePrefijo - 1];
        }

        int longitudTotal = longitudPrefijo + 1;

        if (indiceSalida + longitudTotal > capacidad) {
            int nuevaCapacidad = capacidad * 2;
            char* nuevoBuffer = new char[nuevaCapacidad];

            for (int j = 0; j < indiceSalida; j++) {
                nuevoBuffer[j] = textoDescomprimido[j];
            }

            delete[] textoDescomprimido;

            textoDescomprimido = nuevoBuffer;
            capacidad = nuevaCapacidad;
        }

        for (int j = 0; j < longitudPrefijo; j++) {
            textoDescomprimido[indiceSalida] = prefijo[j];
            indiceSalida++;
        }

        textoDescomprimido[indiceSalida] = static_cast<char>(caracterNuevo);
        indiceSalida++;

        if (cantidadEntradas < maxEntradas) {
            char* nuevaEntrada = new char[longitudTotal];
            for (int j = 0; j < longitudPrefijo; j++) {
                nuevaEntrada[j] = prefijo[j];
            }
            nuevaEntrada[longitudPrefijo] = static_cast<char>(caracterNuevo);

            diccionarioCadenas[cantidadEntradas] = nuevaEntrada;
            diccionarioLongitudes[cantidadEntradas] = longitudTotal;
            cantidadEntradas++;
        }
    }

    tamanoDescomprimido = indiceSalida;

    for (int i = 0; i < cantidadEntradas; i++) {
        delete[] diccionarioCadenas[i];
    }
    delete[] diccionarioCadenas;
    delete[] diccionarioLongitudes;

    return textoDescomprimido;
}
