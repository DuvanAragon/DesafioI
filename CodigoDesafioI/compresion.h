#ifndef COMPRESION_H
#define COMPRESION_H

unsigned char* compresionRLE(const char* textoComprimir, int &tamanoTextoComprimido);
int tamanoRealDescomprimidoRLE(const unsigned char* textoComprimido, int tamanoTextoComprimido);
char* descompresionRLE(const unsigned char* textoComprimido, int tamanoTextoComprimido);
int buscarEnDiccionario(char** diccionarioCadenas, int* diccionarioLongitudes, int cantidadEntradas, const char* subcadena, int longitudSubcadena);
unsigned char* compresionLZ78(const char* textoComprimir, int &tamanoTextoComprimido);
char* descompresionLZ78(unsigned char* textoComprimido, int tamanoComprimido, int &tamanoDescomprimido);

#endif // COMPRESION_H
