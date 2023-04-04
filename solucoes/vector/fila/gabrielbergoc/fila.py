N = int(input())
fila = list(map(int, input().split(' ')))

M = int(input())
deixaram = list(map(int, input().split(' ')))

mapa = {id: True for id in fila}

for id in deixaram:
    mapa[id] = False

resposta = filter(lambda x: mapa[x], fila)
resposta = map(str, resposta)

print(" ".join(resposta))
