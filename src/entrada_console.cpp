#include "entrada_console.h"

using namespace std;

int lerOpcao() {
    int opcao;
    if (!(cin >> opcao)) {
        if (cin.eof()) {
            return 0;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return opcao;
}

bool lerPalavra(string* texto) {
    return static_cast<bool>(cin >> *texto);
}

bool lerLinha(string* texto) {
    cin >> ws;
    return static_cast<bool>(getline(cin, *texto));
}
