#ifndef UTILIDADESBYTES_H
#define UTILIDADESBYTES_H

void separarBytes(unsigned short valor, unsigned char& byteBajo, unsigned char& byteAlto);
unsigned short unirBytes(unsigned char byteBajo, unsigned char byteAlto);
unsigned char rotacionBytsDerecha(unsigned char valorRotar, int rotamientos);

#endif // UTILIDADESBYTES_H
