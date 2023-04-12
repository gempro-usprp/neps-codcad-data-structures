#include <bits/stdc++.h>

using namespace std;

set<char> abre_ = {'(', '[', '{'};
unordered_map<char, char> fecha_ = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
};

bool abre(char c) {
    return abre_.find(c) != abre_.end();
}

char fecha(char c) {
    return fecha_[c];
}

bool validar(string expressao) {
    stack<char> fila;

    for (auto c : expressao) {
        if (abre(c)) {
            fila.push(c);
            continue;
        }

        if (fila.empty()) {
            return false;
        }

        char topo = fila.top();
        fila.pop();

        if (c != fecha(topo)) {
            return false;
        }

    }

    return fila.empty();
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        string expressao;
        cin >> expressao;
        bool valida = validar(expressao);
        cout << (valida ? "S\n" : "N\n");
    }
}
