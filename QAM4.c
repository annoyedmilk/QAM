#include <stdio.h>    // Für Standard-Ein-/Ausgabefunktionen
#include <string.h>   // Für String-Manipulationsfunktionen
#include <math.h>     // Für mathematische Funktionen wie cos() und sin()

const char message[] = "Hello World!";  // Die zu modulierende Nachricht
const float carrierFrequency = 1.0;     // Trägerfrequenz für die Modulation, hier auf 1 Hz gesetzt

int main() {
    // Ein Array deklarieren, um die I- und Q-Komponenten für die 4-QAM-Modulation zu speichern.
    // Die Größe des Arrays ist doppelt so groß wie die Anzahl der Bits in der Nachricht, da
    // jedes Bit durch einen I- oder Q-Wert dargestellt wird.
    int QAM_sequence[2 * strlen(message) * 8];

    int index = 0;  // Index, um die Position im QAM_sequence-Array zu verfolgen

    // Die Nachricht in eine 4-QAM-Sequenz umwandeln
    for (int i = 0; i < strlen(message); i++) {  // Über jedes Zeichen in der Nachricht iterieren
        for (int j = 7; j >= 0; j -= 2) {       // Über jedes Bitpaar im Zeichen iterieren
            int bit1 = (message[i] >> j) & 1;   // Das erste Bit des Paares extrahieren
            int bit2 = (message[i] >> (j - 1)) & 1;  // Das zweite Bit des Paares extrahieren

            // Die Bits in 4-QAM-Symbole umwandeln:
            // Für die I-Komponente: 0 -> 1, 1 -> -1
            // Für die Q-Komponente: 0 -> 1, 1 -> -1
            QAM_sequence[index++] = (bit1 == 0) ? 1 : -1;  // I-Komponente
            QAM_sequence[index++] = (bit2 == 0) ? 1 : -1;  // Q-Komponente
        }
    }

    // Die modulierten Werte generieren und ausgeben
    for (int m = 0; m < 2 * strlen(message) * 8; m += 2) {  // Über jedes I/Q-Paar in der QAM_sequence iterieren
        for (float t = 0; t < 2 * M_PI; t += 0.1) {  // Einen Zyklus der Trägerwelle generieren
            // Die I- und Q-Komponenten auf die Trägerwelle modulieren:
            // Die I-Komponente wird auf eine Kosinuswelle moduliert
            // Die Q-Komponente wird auf eine Sinuswelle moduliert
            float S_i = QAM_sequence[m] * cos(carrierFrequency * t);
            float S_q = QAM_sequence[m + 1] * sin(carrierFrequency * t);

            // Die modulierten I- und Q-Komponenten kombinieren, um das endgültige modulierte Signal zu erzeugen
            float S = S_i + S_q;

            // Den modulierten Wert auf der Konsole ausgeben
            printf("%f\n", S);
        }
    }

    return 0;  // Das Programm beenden
}