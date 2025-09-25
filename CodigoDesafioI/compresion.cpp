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

