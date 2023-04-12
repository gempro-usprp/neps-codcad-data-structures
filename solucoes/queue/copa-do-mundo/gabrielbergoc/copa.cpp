#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Jogo;
typedef char Time;

int main() {
    queue<Time> times;
    for (Time c = 'A'; c < 'P' + 1; c++) {
        times.push(c);
    }

    queue<Jogo> jogos;
    for (int x, y, i = 0; i < 15; i++) {
        cin >> x >> y;
        jogos.emplace(x, y);
    }

    while (!jogos.empty()) {
        Time time_1 = times.front();
        times.pop();
        
        Time time_2 = times.front();
        times.pop();

        int gols_1 = jogos.front().first;
        int gols_2 = jogos.front().second;
        jogos.pop();

        Time vencedor = gols_1 > gols_2 ? time_1 : time_2;
        times.push(vencedor);
    }

    cout << times.front() << endl;
}
