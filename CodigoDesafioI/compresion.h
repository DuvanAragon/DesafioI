#ifndef COMPRESION_H
#define COMPRESION_H

int tamanoRealDescomprimidoRLE(const unsigned char* textoComprimido, int tamanoTextoComprimido);
char* descompresionRLE(const unsigned char* textoComprimido, int tamanoTextoComprimido);
char* descompresionLZ78(unsigned char* textoComprimido, int tamanoComprimido, int &tamanoDescomprimido);

#endif // COMPRESION_H
