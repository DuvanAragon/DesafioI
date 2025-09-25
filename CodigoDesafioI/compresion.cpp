#include "compresion.h"
#include "utilidadesCadenas.h"
#include "utilidadesBytes.h"

unsigned char* compresionRLE(const char* textoComprimir, int &tamanoTextoComprimido)
{
    if (textoComprimir == nullptr) {
        tamanoTextoComprimido = 0;
        return nullptr;
    }

    int longitudTexto = longitudCadena(textoComprimir);

    if (longitudTexto == 0) {
        tamanoTextoComprimido = 0;
        return nullptr;
    }

    unsigned char* ptrTextoComprimido = new unsigned char[longitudTexto * 3];
    int indiceSalida = 0;
    int indiceActual = 0;

    while (indiceActual < longitudTexto) {
        char caracterActual = textoComprimir[indiceActual];
        unsigned short vecesRepetido = 1;

        while (indiceActual + vecesRepetido < longitudTexto && textoComprimir[indiceActual + vecesRepetido] == caracterActual) {
            vecesRepetido++;
        }

        unsigned char byteAlto;
        unsigned char byteBajo;
        separarBytes(vecesRepetido, byteBajo, byteAlto);

        ptrTextoComprimido[indiceSalida] = byteAlto;
        indiceSalida++;
        ptrTextoComprimido[indiceSalida] = byteBajo;
        indiceSalida++;
        ptrTextoComprimido[indiceSalida] = static_cast<unsigned char>(caracterActual);
        indiceSalida++;

        indiceActual += vecesRepetido;
    }

    tamanoTextoComprimido = indiceSalida;
    return ptrTextoComprimido;
}

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
