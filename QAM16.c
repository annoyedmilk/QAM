#include <stdio.h>    // Für Standard-Ein-/Ausgabefunktionen
#include <string.h>   // Für String-Manipulationsfunktionen
#include <math.h>     // Für mathematische Funktionen wie cos() und sin()

const char message[] = "Hello World!";  // Die zu modulierende Nachricht
const float carrierFrequency = 1.0;     // Trägerfrequenz für die Modulation, hier auf 1 Hz gesetzt

int main() {
    // Ein Array deklarieren, um die I- und Q-Komponenten für die 16-QAM-Modulation zu speichern.
    // Die Größe des Arrays ist halb so groß wie bei 4-QAM, da wir jetzt 4 Bits pro Symbol verwenden.
    int QAM_sequence[2 * strlen(message) * 8 / 2];

    int index = 0;  // Index, um die Position im QAM_sequence-Array zu verfolgen

    // Die Nachricht in eine 16-QAM-Sequenz umwandeln
    for (int i = 0; i < strlen(message); i++) {  // Über jedes Zeichen in der Nachricht iterieren
        for (int j = 6; j >= 0; j -= 4) {       // Über jedes 4-Bit-Gruppe im Zeichen iterieren
            int bit1 = (message[i] >> j) & 1;   // Das erste Bit der Gruppe extrahieren
            int bit2 = (message[i] >> (j - 1)) & 1;  // Das zweite Bit der Gruppe extrahieren
            int bit3 = (message[i] >> (j - 2)) & 1;  // Das dritte Bit der Gruppe extrahieren
            int bit4 = (message[i] >> (j - 3)) & 1;  // Das vierte Bit der Gruppe extrahieren

            // Die 4 Bits in 16-QAM-Symbole umwandeln
            int I = (bit1 << 1 | bit2);
            int Q = (bit3 << 1 | bit4);

            // Convert to QAM16 constellation points
            QAM_sequence[index++] = (I == 0) ? 3 : (I == 1) ? 1 : (I == 2) ? -3 : -1;  // I-Komponente
            QAM_sequence[index++] = (Q == 0) ? 3 : (Q == 1) ? 1 : (Q == 2) ? -3 : -1;  // Q-Komponente
        }
    }

    // Die modulierten Werte generieren und ausgeben
    for (int m = 0; m < 2 * strlen(message) * 8 / 2; m += 2) {  // Über jedes I/Q-Paar in der QAM_sequence iterieren
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