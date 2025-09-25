#ifndef COMPRESION_H
#define COMPRESION_H

unsigned char* compresionRLE(const char* textoComprimir, int &tamanoTextoComprimido);
int tamanoRealDescomprimidoRLE(const unsigned char* textoComprimido, int tamanoTextoComprimido);
char* descompresionRLE(const unsigned char* textoComprimido, int tamanoTextoComprimido);

#endif // COMPRESION_H
