//
// Jul 3, 2021
//

#include "player.h"

string Player::getName(){return name;};

int Player::getID(){return ID;};

Team Player::getTeam(){return team;};

void Player::setPlayer(Team tm, int id)
{
    team = tm;
    ID = id;
    if(team == SOSBrigade) name = SOS_Name[ID - 1];
    else name = SC_Name[ID - 1];
}

class SimplePlayer: public Player
{
public:
    SimplePlayer() = default;
    int bet(unsigned int bankroll, unsigned int minimum) override;
    bool draw(Card dealer, const Hand& player) override;
    void expose(Card c) override {};
    void shuffled() override {};
    string getName() override{return name;};
    int getID() override {return ID;};
    Team getTeam() override {return team;};
    void setPlayer(Team tm, int id) override
    {
        team = tm;
        ID = id;
        if(team == SOSBrigade) name = SOS_Name[ID - 1];
        else name = SC_Name[ID - 1];
    };
};

int SimplePlayer::bet(unsigned int bankroll, unsigned int minimum)
{
    if(ID == 1 && team == SOSBrigade) return (int) (2*minimum); // Suzumiya Harushi
    else return (int) minimum;
}

bool SimplePlayer::draw(Card dealer, const Hand& player)
{
    int valueHand = player.handValue().count;
    bool is_soft = player.handValue().soft;
    Spot spot_dealer = dealer.spot;
    if(!is_soft)
    {
        return (valueHand <= 11) || 
               (valueHand == 12 && !(spot_dealer >= FOUR && spot_dealer <= SIX)) ||
               (valueHand >= 13 && valueHand <= 16 && !(spot_dealer >= TWO && spot_dealer <= SIX));
    }
    else
    {
        return (valueHand <= 17) ||
               (valueHand == 18 && ! (spot_dealer == TWO || spot_dealer == SEVEN || spot_dealer == EIGHT));
    }
}

class CountingPlayer: public Player
{
private:
    int count;
public:
    CountingPlayer();
    int bet(unsigned int bankroll, unsigned int minimum) override;
    bool draw(Card dealer, const Hand& player) override;
    void expose(Card c) override;
    void shuffled()override;
    string getName() override {return name;};
    int getID() override {return ID;};
    Team getTeam() override {return team;};
    void setPlayer(Team tm, int id) override
    {
        team = tm;
        ID = id;
        if(team == SOSBrigade) name = SOS_Name[ID - 1];
        else name = SC_Name[ID - 1];
    };
};

CountingPlayer::CountingPlayer(): count(0) {}

int CountingPlayer::bet(unsigned int bankroll, unsigned int minimum)
{   
    if(ID == 3 && team == SOSBrigade)
    {
        if(count <= -2 && minimum * 2 <= bankroll) return (int) (minimum * 2);
        else return (int) minimum;
    }
    else if(ID == 4 && team == StardustCrusaders)
    {
        if(count >= 4 && minimum * 2 <= bankroll) return (int) (minimum *2);
        else return (int) minimum;
    }
    else // Normal Counting Bet Behavior
    {
        if(count >= 2 && minimum * 2 <= bankroll) return (int) (minimum * 2);
        else return (int) minimum;
    }
}

bool CountingPlayer::draw(Card dealer, const Hand& player)
{
    return SimplePlayer{}.draw(dealer, player);
}

void CountingPlayer::expose(Card c)
{
    if(c.spot >= TEN) count--;
    else if(c.spot >= TWO && c.spot <= SIX) count++;
}

void CountingPlayer::shuffled()
{
    count = 0;
}

extern Player* get_Player(string& dealerSide, string& playerType, int& ID)
{
    Player *player = nullptr;

    if(playerType == "simple") player = new SimplePlayer();
    else if(playerType == "counting") player = new CountingPlayer();

    if(dealerSide == "sos") player->setPlayer(SOSBrigade, ID);
    else if(dealerSide == "sc") player->setPlayer(StardustCrusaders, ID);
    
    return player;
}