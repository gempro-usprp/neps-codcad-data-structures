#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<int> fila(N);
    unordered_map<int, bool> mapa;
    for (int i = 0; i < N; i++)
    {
        cin >> fila[i];
        mapa.insert({fila[i], true});
    }

    int M;
    cin >> M;

    for (int x, i = 0; i < M; i++)
    {
        cin >> x;
        mapa[x] = false;
    }

    stringstream ss;
    for (auto id : fila)
    {
        if (mapa[id])
        {
            ss << id << " ";
        }
    }

    string answer = ss.str();
    answer.pop_back();

    cout << answer << endl;
}
