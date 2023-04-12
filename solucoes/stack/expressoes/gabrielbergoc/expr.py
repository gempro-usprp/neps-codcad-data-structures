class Pilha:
    def __init__(self):
        self.__pilha = []

    def push(self, value):
        self.__pilha.append(value)

    def pop(self):
        return self.__pilha.pop()

    def is_empty(self):
        return len(self.__pilha) == 0


def abre(char):
    return char in ('(', '[', '{')


def validar(expressao):
    fecha = {'(': ')', '[': ']', '{': '}'}
    pilha = Pilha()

    for char in expressao:
        if abre(char):
            pilha.push(char)
            continue

        if pilha.is_empty():
            return False

        topo = pilha.pop()
        if fecha[topo] != char:
            return False

    return pilha.is_empty()


def main():
    T = int(input())

    for _ in range(T):
        expressao = input()
        valida = validar(expressao)
        print('S' if valida else 'N')


if __name__ == '__main__':
    main()
