#include "manejoArchivos.h"
#include <fstream>
#include <iostream>

using namespace std;

unsigned char* lecturaArchivos(const char *rutaArchivo, int &tamanoArchivo)
{
    ifstream archivo(rutaArchivo, ios::binary );

    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo: " << rutaArchivo << endl;
        tamanoArchivo = 0;
        return NULL;
    }

    char letra;
    tamanoArchivo = 0;

    while (archivo.get(letra))
    {
        tamanoArchivo++;
    }

    unsigned char *DatosArchivo = new unsigned char[tamanoArchivo + 1];

    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    while (archivo.get(letra))
    {
        DatosArchivo[i++] = static_cast<unsigned char>(letra);
    }

    archivo.close();

    return DatosArchivo;
}

