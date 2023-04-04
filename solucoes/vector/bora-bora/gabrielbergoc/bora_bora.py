from operator import attrgetter


class Card:
    def __init__(self, n_suit):
        self.n, self.suit = n_suit.split(' ')
        self.n = int(self.n)

    def __str__(self):
        return f"{self.n} {self.suit}"

    def __repr__(self):
        return f"{self.n} {self.suit}"

    def __eq__(self, other):
        return self.n == other.n and self.suit == other.suit

    def is_queen(self):
        return self.n == 12

    def is_seven(self):
        return self.n == 7

    def is_ace(self):
        return self.n == 1

    def is_jack(self):
        return self.n == 11

    def can_play(self, other):
        return self.n == other.n or self.suit == other.suit


class Direction:
    def __init__(self, n_players, start_card):
        self._n_players = n_players
        self._dir = 1
        self._skip_next = 0
        self._curr_player = 1 if start_card.is_queen() else -1
        self.use_effect = True

    def invert(self):
        if self.use_effect:
            self._dir *= -1
        self.use_effect = False

    def skip_next(self):
        if self.use_effect:
            self._skip_next = 1
        self.use_effect = False

    def next_player(self):
        self._curr_player = self._curr_player + (1 + self._skip_next) * self._dir
        self._curr_player %= self._n_players
        self._skip_next = 0
        return self._curr_player


def sort_hand(hand):
    hand.sort(key=attrgetter('suit'), reverse=True)
    hand.sort(key=attrgetter('n'), reverse=True)


def get_card():
    return Card(input())


def get_effect(card, direction, deck):
    if card.is_queen():
        direction.invert()
    elif card.is_seven():
        if direction.use_effect:
            direction.use_effect = False
            return deck.pop(0), deck.pop(0)
    elif card.is_ace():
        if direction.use_effect:
            direction.use_effect = False
            return deck.pop(0)
    elif card.is_jack():
        direction.skip_next()


def main():
    while True:
        P, M, N = map(int, input().split(' '))
        if P == 0:
            break

        # distribute hands
        hands = [[] for _ in range(P)]
        for p in range(P):
            for m in range(M):
                hands[p].append(get_card())
            sort_hand(hands[p])

        # init discard pile
        discard_top = get_card()
        direction = Direction(P, discard_top)

        deck = [get_card() for _ in range(N - (P * M + 1))]

        # start game
        winner = None
        while len(deck) > 0 or winner is None:
            effect = get_effect(discard_top, direction, deck)
            p = direction.next_player()
            h = hands[p]
            if effect is None:
                play = next(
                    (card for card in h if card.can_play(discard_top)),
                    None  # if player can't play any cards
                )
                if play is None:
                    new_card = deck.pop(0)
                    if new_card.can_play(discard_top):
                        discard_top = new_card
                        direction.use_effect = True
                    else:
                        h.append(new_card)
                        sort_hand(h)
                else:
                    discard_top = play
                    h.remove(play)
                    direction.use_effect = True
                    if len(h) == 0:
                        winner = p
                        break
            else:
                if isinstance(effect, tuple):
                    h.extend(effect)
                else:
                    h.append(effect)
                sort_hand(h)

        print(winner + 1)


if __name__ == "__main__":
    main()
