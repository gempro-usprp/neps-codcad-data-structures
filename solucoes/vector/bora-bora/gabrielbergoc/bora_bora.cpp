// WA

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, char> Card;
typedef vector<Card> Hand;

void sort_hand(Hand &hand)
{

    sort(hand.rbegin(), hand.rend());
}

Card get_top_card(Hand &deck)
{
    auto top = deck.front();
    deck.erase(deck.begin());
    return top;
}

string card_to_string(Card card)
{
    stringstream ss;
    ss << card.first << " " << card.second;
    return ss.str();
}

bool card_is(int n, Card card)
{
    return card.first == n;
}

bool can_play(Card player_card, Card discard_top)
{
    return player_card.first == discard_top.first || player_card.second == discard_top.second;
}

auto find_playable_card(Hand &hand, Card discard_top)
{
    for (auto it = hand.begin(); it != hand.end(); it++)
    {
        if (can_play(*it, discard_top))
        {
            return it;
        }
    }

    return hand.end();
}

/**
 * @brief Copy values from source Card to target Card.
 *
 * @param target Target card to copy.
 * @param source Source card to copy.
 */
void copy(Card &target, Card &source)
{
    target.first = source.first;
    target.second = source.second;
}

void buy_n_cards(int n, Hand &hand, Hand &deck)
{
    for (int i = 0; i < n; i++)
    {
        Card taken = get_top_card(deck);
        hand.push_back(taken);
    }

    sort_hand(hand);
}

string hand_to_string(Hand hand)
{
    stringstream ss;
    for (auto card : hand)
    {
        ss << card_to_string(card) << ", ";
    }

    string str = ss.str();
    str.pop_back();
    str.pop_back();

    return str;
}

int main()
{
    int P, M, N;

    while (true)
    {
        cin >> P >> M >> N;
        if (P == 0)
            break;

        // getting deck of cards
        Hand deck(N);
        for (auto &x : deck)
        {
            cin >> x.first >> x.second;
        }

        // distributing hands
        vector<Hand> hands(P, Hand(M));
        for (auto &hand : hands)
        {
            for (auto &card : hand)
            {
                auto top = get_top_card(deck);
                copy(card, top);
            }

            sort_hand(hand);
        }

        // game
        Card discard_pile_top = get_top_card(deck);
        int direction = 1;
        int next_player = card_is(12, discard_pile_top) ? 1 : -1;
        bool use_effect = true;
        int winner = -1;
        while (winner < 0 || deck.size() > 0)
        {
            direction *= use_effect && card_is(12, discard_pile_top) ? -1 : 1;
            next_player = (P + next_player + direction) % P;

            Hand &hand = hands.at(next_player);
            if (use_effect)
            {
                if (card_is(11, discard_pile_top))
                {
                    use_effect = false;
                    continue;
                }

                int cards_taken = card_is(7, discard_pile_top)   ? 2
                                  : card_is(1, discard_pile_top) ? 1
                                                                 : 0;

                if (cards_taken > 0)
                {
                    buy_n_cards(cards_taken, hand, deck);
                    use_effect = false;
                    continue;
                }
            }

            auto it_card_to_play = find_playable_card(hand, discard_pile_top);
            if (it_card_to_play != hand.end())
            {
                Card card_to_play = *it_card_to_play;
                hand.erase(it_card_to_play);
                copy(discard_pile_top, card_to_play);
                use_effect = true;

                if (hand.size() == 0)
                {
                    winner = next_player + 1;
                    break;
                }
            }
            else
            {
                Card card_taken = get_top_card(deck);
                if (can_play(card_taken, discard_pile_top))
                {
                    copy(discard_pile_top, card_taken);
                    use_effect = true;
                }
                else
                {
                    hand.push_back(card_taken);
                    sort_hand(hand);
                }
            }
        }

        cout << winner << endl;
    }
}