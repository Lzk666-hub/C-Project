//
// Created by 12077 on 2021/6/29.
//
#include "deck.h"

Deck::Deck() {
    this->reset();
}

void Deck::reset() {
    this->next=0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            deck[i * 13 + j].suit = (Suit)(i);
            deck[i * 13 + j].spot = (Spot)(j);
        }
    }
}

void Deck::shuffle(int n) {
    this->next=0;
    Card shuffleCard[52];
    if (n <= 26) {
        for (int i = 0; i < n; ++i) {
            shuffleCard[2 * i] = this->deck[i + n];
            shuffleCard[2 * i + 1] = this->deck[i];
        }
        for (int j = 2 * n; j < 52; ++j) {
            shuffleCard[j] = this->deck[j];
        }
    } else {
        for (int i = 0; i < 52 - n; ++i) {
            shuffleCard[2 * i] = this->deck[i + n];
            shuffleCard[2 * i + 1] = this->deck[i];
        }
        for (int j = 52 - n; j < n; ++j) {
            shuffleCard[j + 52 - n] = this->deck[j];
        }
    }
    for (int i = 0; i < 52;i++ ) {
        this->deck[i] = shuffleCard[i];
    }
}

Card Deck::deal() {
    if(this->next>=52){
        throw DeckEmpty();
    } else return this->deck[this->next++];
}

int Deck::cardsLeft() {
    return 52- this->next;
}