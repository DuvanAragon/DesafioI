#include "utilidadesBytes.h"

void separarBytes(unsigned short valor, unsigned char& byteBajo, unsigned char& byteAlto)
{
    byteBajo = static_cast<unsigned char>(valor & 255);
    byteAlto = static_cast<unsigned char>((valor >> 8) & 255);
}

unsigned short unirBytes(unsigned char byteBajo, unsigned char byteAlto)
{
    unsigned short bytesCombinados  = (byteAlto << 8) | byteBajo;

    return bytesCombinados;
}

unsigned char rotacionBytsDerecha(unsigned char valorRotar, int rotamientos)
{
    unsigned char rotacionDerecha = (valorRotar >> rotamientos) | (valorRotar << (8 - rotamientos));

    return rotacionDerecha;
}
