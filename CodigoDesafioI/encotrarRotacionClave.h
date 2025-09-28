#ifndef ENCOTRARROTACIONCLAVE_H
#define ENCOTRARROTACIONCLAVE_H

bool caracterValido(unsigned char caracter);
bool RotacionClaveValida(unsigned char* textoCifrado, int tamanoTextoCifrado, unsigned char& posibleClave, int* rotacionCandidata, int claveInicial);

#endif // ENCOTRARROTACIONCLAVE_H
