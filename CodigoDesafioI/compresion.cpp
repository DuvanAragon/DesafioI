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

int buscarEnDiccionario(char** diccionarioCadenas, int* diccionarioLongitudes, int cantidadEntradas, const char* subcadena, int longitudSubcadena) {

    for(int i = 0; i < cantidadEntradas; i++)
    {
        if(compararCadenas(diccionarioCadenas[i], diccionarioLongitudes[i], subcadena, longitudSubcadena))
        {
            return i + 1;
        }
    }

    return 0;
}

unsigned char* compresionLZ78(const char* textoComprimir, int &tamanoTextoComprimido)
{
    int longitudTexto  = longitudCadena(textoComprimir);

    unsigned char* textoComprimido = new unsigned char[longitudTexto  * 3];
    int indiceSalida = 0;

    char** diccionarioCadenas  = new char*[longitudTexto ];
    int* diccionarioLongitudes  = new int[longitudTexto ];
    int cantidadEntradas = 0;

    int indiceTexto = 0;

    while (indiceTexto < longitudTexto)
    {
        int mejorIndice  = 0;
        int mejorLongitud  = 0;

        for (int longitudActual = 1; indiceTexto+longitudActual < longitudTexto ; longitudActual++)
        {
            int indiceEncontrado = buscarEnDiccionario(diccionarioCadenas, diccionarioLongitudes, cantidadEntradas, textoComprimir + indiceTexto, longitudActual);

            if(indiceEncontrado != 0)
            {
                mejorIndice = indiceEncontrado;
                mejorLongitud = longitudActual;
            }else
            {
                break;
            }
        }

        int posicionSiguiente = indiceTexto + mejorLongitud;
        unsigned char caracterNuevo = static_cast<unsigned char>(textoComprimir[posicionSiguiente]);

        unsigned char byteBajo;
        unsigned char byteAlto;
        separarBytes(static_cast<unsigned short>(mejorIndice), byteBajo, byteAlto);

        textoComprimido[indiceSalida] = byteAlto;
        indiceSalida++;
        textoComprimido[indiceSalida] = byteBajo;
        indiceSalida++;
        textoComprimido[indiceSalida] = caracterNuevo;
        indiceSalida++;

        int nuevaLongitud = mejorLongitud + 1;

        diccionarioLongitudes[cantidadEntradas] = nuevaLongitud;
        diccionarioCadenas[cantidadEntradas] = new char[nuevaLongitud];

        for (int k = 0; k < nuevaLongitud; k++) {
            diccionarioCadenas[cantidadEntradas][k] = textoComprimir[indiceTexto + k];
        }

        cantidadEntradas++;
        indiceTexto += mejorLongitud + 1;
    }

    tamanoTextoComprimido = indiceSalida;

    for (int k = 0; k < cantidadEntradas; k++) {
        delete[] diccionarioCadenas[k];
    }
    delete[] diccionarioCadenas;
    delete[] diccionarioLongitudes;

    return textoComprimido;
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
