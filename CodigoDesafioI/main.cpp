#include <iostream>
#include "manejoArchivos.h"
#include "encotrarRotacionClave.h"
#include "compresion.h"
#include "utilidadesCadenas.h"
#include "utilidadesBytes.h"

using namespace std;

int main() {
    int n;
    cout << "Ingrese el numero de archivos a evaluar: ";
    cin >> n;

    for (int caso = 1; caso <= n; caso++) {
        cout << "\n=== Archivo Encriptado " << caso << " ===\n";

        char rutaPista[100];
        char rutaCifrado[100];
        sprintf(rutaPista, "Documentos/pista%d.txt", caso);
        sprintf(rutaCifrado, "Documentos/Encriptado%d.txt", caso);

        int tamanoPista = 0;
        unsigned char* pistaBytes = lecturaArchivos(rutaPista, tamanoPista);

        if (!pistaBytes || tamanoPista == 0) {
            cerr << "Error leyendo " << rutaPista << "\n";
            continue;
        }

        char* pista = new char[tamanoPista + 1];
        for (int i = 0; i < tamanoPista; i++){
            pista[i] = static_cast<char>(pistaBytes[i]);
        }
        pista[tamanoPista] = '\0';
        delete[] pistaBytes;

        int tamanoCifrado = 0;
        unsigned char* cifrado = lecturaArchivos(rutaCifrado, tamanoCifrado);
        if (!cifrado || tamanoCifrado == 0) {
            cerr << "Error leyendo " << rutaCifrado << "\n";
            delete[] pista;
            continue;
        }

        unsigned char clave = 0;
        int rotaciones[7] = {0};
        int keyInicial = 0;
        bool encontrado = false;

        while (RotacionClaveValida(cifrado, tamanoCifrado, clave, rotaciones, keyInicial)) {
            int rot = rotaciones[0];

            unsigned char* descCifrado = new unsigned char[tamanoCifrado];
            for (int i = 0; i < tamanoCifrado; i++) {
                unsigned char x = cifrado[i] ^ clave;
                descCifrado[i] = rotacionBytsDerecha(x, rot);
            }

            char* descomprimidoRLE = descompresionRLE(descCifrado, tamanoCifrado);
            if (descomprimidoRLE) {
                if (buscarSubcadena(descomprimidoRLE, pista)) {
                    cout << "Clave XOR en hexadecimal : " << std::hex << static_cast<int>(clave);
                    cout << "\nRotacion de bytes a la derecha: " << rot << "\n";

                    cout << "La pista fue encontrada con RLE.\n\n";
                    cout << "----- Texto descomprimido (RLE) -----\n";
                    cout << descomprimidoRLE << "\n";
                    cout << "------------------------------------\n";
                    encontrado = true;
                }
                delete[] descomprimidoRLE;
            }

            if (!encontrado) {
                int tamDescompLZ = 0;
                char* descomprimidoLZ = descompresionLZ78(descCifrado, tamanoCifrado, tamDescompLZ);
                if (descomprimidoLZ && tamDescompLZ > 0) {
                    descomprimidoLZ[tamDescompLZ] = '\0';
                    if (buscarSubcadena(descomprimidoLZ, pista)) {
                        cout << "Clave XOR en hexadecimal : " << std::hex << static_cast<int>(clave);
                        cout << "\nRotacion de bytes a la derecha: " << rot << "\n";

                        cout << "La pista fue encontrada con LZ78.\n\n";
                        cout << "----- Texto descomprimido (LZ78) -----\n";
                        cout << descomprimidoLZ << "\n";
                        cout << "-------------------------------------\n";
                        encontrado = true;
                    }
                    delete[] descomprimidoLZ;
                }
            }

            delete[] descCifrado;

            if (encontrado) break;

            keyInicial = static_cast<int>(clave) + 1;
        }

        if (!encontrado) {
            cout << "La pista no se encontro con ninguna clave.\n";
        }

        delete[] cifrado;
        delete[] pista;
    }

    return 0;
}
