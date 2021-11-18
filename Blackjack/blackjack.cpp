#include <iostream>
#include <string>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

using namespace std;

const int BET_MIN = 5;
const string SC = "Game over. The winner is Stardust Crusaders. SOS Brigade will return the computer to Joseph Joestar and Suzumiya Haruhi will become a member of Stardust Crusaders";
const string SOS = "Game over. The winner is SOS Brigade. SOS Brigade got four computers and Stardust Crusaders become an affiliate group of SOS Brigade";
const string JJ = "Player: Joseph Joestar: \"Ni Ge Run Da Yo\"";
const string FREEZE = ": \"Star Platinum, Za Warudo\"";

void shuffle(Deck &deck, Player *player) {
    cout << "Shuffling the deck" << endl;
    int cutPosition;
    for (int i = 0; i < 7; i++) {
        cutPosition = get_cut();
        deck.shuffle(cutPosition);
        cout << "cut at " << cutPosition << endl;
    }
    player->shuffled();
}

string judgePlayer(const string &dealerSide, string &playerSide) {
    if (dealerSide == "sc") playerSide = "sos";
    else if (dealerSide == "sos") playerSide = "sc";
    return playerSide;
}

string showCard(const Card &card) {
    return string(SpotNames[card.spot]) + " of " + SuitNames[card.suit];
}

void stupidSentences(const string &name, bool is_player) {
    if (name == "Kakyoin Noriaki") {
        if (is_player) cout << "Player: Kakyoin Noriaki: \"rerorerorero rerorerorero\"" << endl;
        else cout << "Dealer: Kakyoin Noriaki: \"rerorerorero rerorerorero\"" << endl;
    } else if (name == "Joseph Joestar") {
        if (is_player) cout << "Player: Joseph Joestar: \"Nice!\"" << endl;
        else cout << "Dealer: Joseph Joestar: \"Nice!\"" << endl;
    }
}

void exposeInfo(Card card, bool expose, bool player, Player *player1) {
    if (expose) {
        if (!player) {
            cout << "Dealer: " << player1->getName() << " dealt "
                 << showCard(card) << endl;
        } else {
            player1->expose(card);
            cout << "Player: " << player1->getName() << " dealt "
                 << showCard(card) << endl;
        }
    }
}

Card deal(int &thisHand, Deck &deck, Hand &hand, Player *player, const bool is_player, const bool is_expose,
          bool &is_deck_empty) {
    Card card{};
    try { card = deck.deal(); }
    catch (DeckEmpty e) {
        is_deck_empty = true;
        cout << "Hand " << thisHand << " card used up, this hand will start again" << endl;
        return Card{};
    }
    hand.addCard(card);
    exposeInfo(card, is_expose, is_player, player);
    return card;
};

void simulation(Player *player,Player *dealer,Deck &deck,int &thisHand,const int hands,int &bankroll,const int initialBankroll,bool &firstRound,bool &detect,bool &win,int &pIndex,int &dIndex){
    Hand dHand, pHand;
    while (thisHand <= hands && bankroll >= BET_MIN && !detect) {
        bool pBust=false, dBust=false;
        dHand.discardAll();
        pHand.discardAll();
        Card hole_card{}, dealer_up_card{};

        cout << "Hand " << thisHand << " bankroll " << bankroll << endl;
        if (deck.cardsLeft() < 20) {
            shuffle(deck, player);
        }
        int wager(player->bet(bankroll, BET_MIN));
        cout << "Player: " << player->getName() << " bets " << wager << endl;


        deal(thisHand, deck, pHand, player, true, true, detect);
        if (detect) {
            shuffle(deck, player);
            detect = false;
            continue;
        }
        dealer_up_card = deal(thisHand, deck, dHand, dealer, false, true, detect);
        if (detect) {
            shuffle(deck, player);
            detect = false;
            continue;
        }
        deal(thisHand, deck, pHand, player, true, true, detect);
        if (detect) {
            shuffle(deck, player);
            detect = false;
            continue;
        }
        hole_card = deal(thisHand, deck, dHand, dealer, false, false, detect);
        if (detect) {
            shuffle(deck, player);
            detect = false;
            continue;
        }


        if (pHand.handValue().count == 21) {
            cout << "Player: " << player->getName() << " dealt natural 21" << endl;
            bankroll += (3 / 2) * wager;
            thisHand++;
            continue;
        }
        int card_count = 0;
        while (player->draw(dealer_up_card, pHand)) {
            deal(thisHand, deck, pHand, player, true, true, detect);
            card_count++;
            if (detect) break;
            if (pHand.handValue().count > 21 && player->getName() != SC_Name[1]) {
                pBust = true;
                break;
            } else if (pHand.handValue().count > 21 && player->getName() == SC_Name[1]) {
                pBust = false;
                while (pHand.handValue().count > 21) {
                    cout << "Player: " << player->getName() << FREEZE << endl;
                    pHand.discardAll();
                    for (int i = 0; i < (card_count + 2); i++) {
                        deal(thisHand, deck, pHand, player, true, false, detect);
                        if (detect) break;
                    }
                    if (detect) break;
                }
                if (detect) break;
            }
        }
        if (detect) {
            shuffle(deck, player);
            detect = false;
            continue;
        }
        cout << "Player: " << player->getName() << "'s total is " << pHand.handValue().count << endl;
        if (pBust) {
            cout << "Player: " << player->getName() << " busts" << endl;
            bankroll -= wager;
            thisHand++;
            continue;
        } else {
            cout << "Dealer: " << dealer->getName() << "'s hole card is "
                 << showCard(hole_card) << endl;
            player->expose(hole_card);
            card_count = 0;
            while (dHand.handValue().count < 17) {
                deal(thisHand, deck, dHand, dealer, false, true, detect);
                card_count++;
                if (detect) break;
                if (dHand.handValue().count > 21 && dealer->getName() == SC_Name[1]) {
                    cout << "Dealer: " << dealer->getName() << FREEZE << endl;
                    dBust = false;
                    while (dHand.handValue().count > 21) {
                        dHand.discardAll();
                        for (int i(0); i < (card_count + 2); i++) {
                            deal(thisHand, deck, dHand, dealer, true, false, detect);
                            if (detect) break;
                        }
                        if (detect) break;
                    }
                    if (detect) break;
                }
                if (dHand.handValue().count > 21 && dealer->getName() != SC_Name[1]) {
                    dBust = true;
                    break;
                }
            }
            if (detect) {
                shuffle(deck, player);
                detect = false;
                continue;
            }
            cout << "Dealer: " << dealer->getName() << "'s total is " << dHand.handValue().count << endl;
            if (dBust) {
                cout << "Dealer: " << dealer->getName() << " busts" << endl;
                bankroll += wager;
                thisHand++;
                continue;
            } else {
                if (pHand.handValue().count < dHand.handValue().count) {
                    cout << "Dealer: " << dealer->getName() << " wins this hand" << endl;
                    bankroll -= wager;
                } else if (pHand.handValue().count > dHand.handValue().count) {
                    cout << "Player: " << player->getName() << " wins this hand" << endl;
                    bankroll += wager;
                } else if (pHand.handValue().count == dHand.handValue().count) {
                    cout << "Push" << endl;
                }
                thisHand++;
                continue;
            }
        }
    }
    if (bankroll < BET_MIN || thisHand == hands + 1) {
        cout << "Player: " << player->getName() << " has " << bankroll << " after " << (thisHand - 1) << " hands"
             << endl;
    }
    if (bankroll >= BET_MIN) {
        cout << "Dealer: " << dealer->getName() << " has been kicked out. The winner of this round is "
             << player->getName() << "." << endl;
        stupidSentences(player->getName(), true);
        win = true;
        firstRound = false;
        dIndex++;
    } else if (bankroll < BET_MIN || (bankroll < (initialBankroll / 2) && player->getName() == "Joseph Joestar")) {
        if (player->getName() == "Joseph Joestar" && (bankroll < initialBankroll / 2))
            cout << JJ << endl;
        cout << "Player: " << player->getName() << " has been kicked out. The winner of this round is "
             << dealer->getName() << "." << endl;
        stupidSentences(dealer->getName(), false);
        win = false;
        firstRound = true;
        pIndex++;
    }
};



int main(int argc, char *argv[]) {
    Deck deck;
    Player *player, *dealer;

    bool win = false;
    bool detect = false;
    bool firstRound = true;
    int bankroll = stoi(argv[1]);
    int hands = stoi(argv[2]);
    string playerType = argv[3], dealerSide = argv[4], playerSide;
    int pIndex = 1, dIndex = 1;
    string type;
    judgePlayer(dealerSide, playerSide);


    while (pIndex != 6 && dIndex != 6) {
        int thisHand = 1;
        type = playerType;
        if (!win) bankroll = stoi(argv[1]);


        if (playerSide == "sos") {
            if (pIndex == 1 || pIndex == 4) type = "simple";
            else if (pIndex == 2 || pIndex == 3) type = "counting";
        } else if (playerSide == "sc") {
            if (pIndex != 3 && pIndex != 5 && pIndex != 6) type = "counting";
            else if (pIndex == 3) type = "simple";
        } else type = playerType;


        player = get_Player(playerSide, type, pIndex);
        dealer = get_Player(dealerSide, playerType, dIndex);


        if (player->getName() == SC_Name[0] && firstRound) bankroll = 2*bankroll;


        shuffle(deck, player);

        simulation(player,dealer,deck,thisHand,hands,bankroll,stoi(argv[1]),firstRound,detect,win,pIndex,dIndex);

        delete dealer;
        delete player;
    }
    if (((dIndex == 6) && (playerSide == "sc")) || ((pIndex == 6) && (dealerSide == "sc"))) {
        cout << SC << endl;
    } else {
        cout << SOS << endl;
    }
    return 0;
}


