#include "utilidadesBytes.h"

void separarBytes(unsigned short valor, unsigned char& byteBajo, unsigned char& byteAlto)
{
    byteBajo = static_cast<unsigned char>(valor & 255);
    byteAlto = static_cast<unsigned char>((valor >> 8) & 255);
}
