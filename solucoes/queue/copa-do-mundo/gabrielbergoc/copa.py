class Fila:
    def __init__(self, fila = None):
        if fila is None:
            self.__fila = []
        else:
            self.__fila = fila
        
    def push(self, value):
        self.__fila.append(value)
        
    def pop(self):
        return self.__fila.pop(0)

    def front(self):
        return self.__fila[0]

    def is_empty(self):
        return len(self.__fila) == 0


jogos = Fila([input() for _ in range(15)])
times = Fila([chr(c) for c in range(ord('A'), ord('P') + 1)])

while not jogos.is_empty():
    time_1, time_2 = times.pop(), times.pop()
    gols_1, gols_2 = (int(gols) for gols in jogos.pop().split(' '))
    vencedor = time_1 if gols_1 > gols_2 else time_2
    times.push(vencedor)

print(times.front())
