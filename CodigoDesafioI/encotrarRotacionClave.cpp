#include "encotrarRotacionClave.h"
#include "utilidadesBytes.h"

bool caracterValido(unsigned char caracter) {
    if (caracter >= 'a' && caracter <= 'z') return true;
    if (caracter >= 'A' && caracter <= 'Z') return true;
    if (caracter >= '0' && caracter <= '9') return true;
    return false;
}

bool RotacionClaveValida(unsigned char* textoCifrado, int tamanoTextoCifrado, unsigned char& posibleClave, int* rotacionCandidata, int claveInicial)
{
    for (int paso = 0; paso < 2; paso++) {
        for (int k = claveInicial; k < 256; k++) {
            if (paso == 0) {
                posibleClave = textoCifrado[2];
            } else {
                posibleClave = static_cast<unsigned char>(k);
            }
            if (paso == 1 && posibleClave == textoCifrado[2]) {
                continue;
            }

            int numeroRotado = 7;
            for (int i = 0; i < 7; i++) {
                rotacionCandidata[i] = i + 1;
            }

            bool claveValida = true;

            for (int idx = 2; idx < tamanoTextoCifrado && numeroRotado > 0; idx += 3) {
                unsigned char valor = textoCifrado[idx];
                unsigned char byteXor = static_cast<unsigned char>(valor ^ posibleClave);

                int rotacionesValidas[7];
                int cantidadValidas = 0;

                for (int j = 0; j < numeroRotado; j++) {
                    int n = rotacionCandidata[j];
                    unsigned char rotado = rotacionBytsDerecha(byteXor, n);

                    if (caracterValido(rotado)) {
                        rotacionesValidas[cantidadValidas] = n;
                        cantidadValidas++;
                    }
                }

                if (cantidadValidas == 0) {
                    claveValida = false;
                    break;
                }

                numeroRotado = cantidadValidas;
                for (int j = 0; j < cantidadValidas; j++) {
                    rotacionCandidata[j] = rotacionesValidas[j];
                }
            }

            if (claveValida && numeroRotado > 0) {
                int rotFinal = rotacionCandidata[0];
                rotacionCandidata[0] = rotFinal;
                for (int j = 1; j < 7; j++) rotacionCandidata[j] = 0;
                return true;
            }
        }
    }
    return false;
}
