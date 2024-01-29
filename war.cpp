#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

// ---------- DECLARATIONS
string deck[] = {
    "2h","3h","4h","5h","6h","7h","8h","9h","10h","Jh","Qh","Kh","Ah",
    "2d","3d","4d","5d","6d","7d","8d","9d","10d","Jd","Qd","Kd","Ad",
    "2c","3c","4c","5c","6c","7c","8c","9c","10c","Jc","Qc","Kc","Ac",
    "2s","3s","4s","5s","6s","7s","8s","9s","10s","Js","Qs","Ks","As"
};
vector<string> pDeck;
vector<string> cDeck;
vector<string> dealt;
vector<string> onTable;
vector<string> warTable;
string newCard;
char keyPress;
int getRandomIndex(int num);
void currentState(vector<string> pDeck, vector<string> cDeck);
bool cardAlreadyDealt(string card, vector<string> dealtCards);
void drawCards(vector<string> &pDeck, vector<string> &cDeck, vector<string> &table);
void printCards(vector<string> table);
void printAllCards(vector<string> table);
int getCardValue(string card);
void checkCardsAndGiveToWinner(vector<string> &table, vector<string> &pDeck, vector<string> &cDeck, vector<string> &warTable);

void startWar(vector<string> &table, vector<string> &pDeck, vector<string> &cDeck, vector<string> &warTable);

void dealCard(string *deck, vector<string> &playerDeck, vector<string> &dealtCards);
// --------------------

int main() {

    cout << "---------------------\n";
    cout << "         War         \n";
    cout << "---------------------\n";
    cout << "\n";

    // ---------- Deal Cards
    int counter = 52;
    do {
        dealCard(deck, pDeck, dealt);
        counter--;

        dealCard(deck, cDeck, dealt);
        counter--;
    } while(counter > 0);
    // --------------------

    // --------------------
    currentState(pDeck, cDeck);
    // --------------------

    // --------------------
    do {
        cout << "En garde! Draw cards? (press 'd')\n";
        cout << endl;
        char keyPress;
        cin >> keyPress;

        if(keyPress == 'd') {
            drawCards(pDeck, cDeck, onTable);
            printCards(onTable);
            checkCardsAndGiveToWinner(onTable, pDeck, cDeck, warTable);
        }

        // --------------------
        currentState(pDeck, cDeck);
        // --------------------
        
    } while (pDeck.size() > 0 || cDeck.size() > 0);
    // --------------------

    return 0;
}

// ---------- Utilities
void startWar(vector<string> &table, vector<string> &pDeck, vector<string> &cDeck, vector<string> &warTable) {
    bool flag = false;
    warTable.push_back(table[0]);
    warTable.push_back(table[1]);
    table.erase(table.begin());
    table.erase(table.begin());
    do {
        for (int i = 0; i < 3; i++) {
            drawCards(pDeck, cDeck, warTable);
        }
        printAllCards(warTable);

        int lastTableIndex = warTable.size() - 1;
        int pCardVal = getCardValue(warTable[lastTableIndex - 1]);
        int cCardVal = getCardValue(warTable[lastTableIndex]);

        if(pCardVal > cCardVal) {         // players card is greater than computers
            for(string card : warTable) {
                pDeck.push_back(card);
            }
            for(string card : warTable) {
                warTable.erase(warTable.begin());
            }
            cout << "You won the war!" << endl;
        }
        if(cCardVal > pCardVal) {  // computers card is greater than players
            for(string card : warTable) {
                cDeck.push_back(card);
            }
            for(string card : warTable) {
                warTable.erase(warTable.begin());
            }
            cout << "You lost the war!" << endl;
        } 
        if(pCardVal == cCardVal) {
            flag = true;
        }
    } while(flag);
}

void checkCardsAndGiveToWinner(vector<string> &table, vector<string> &pDeck, vector<string> &cDeck, vector<string> &warTable) {
    int pCardVal = getCardValue(table[0]);
    int cCardVal = getCardValue(table[1]);

    if(pCardVal > cCardVal) {         // players card is greater than computers
        pDeck.push_back(table[0]);
        pDeck.push_back(table[1]);
        table.erase(table.begin());
        table.erase(table.begin());
    } else if(cCardVal > pCardVal) {  // computers card is greater than players
        cDeck.push_back(table[0]);
        cDeck.push_back(table[1]);
        table.erase(table.begin());
        table.erase(table.begin());
    } else {
        cout << "Tie! Start a War! (press 'w')\n";
        char keyPress;
        cin >> keyPress;

        if(keyPress == 'w') {
            startWar(onTable, pDeck, cDeck, warTable);
        }
    }
}

void printAllCards(vector<string> table) {
    cout << "-------------------\n";
    cout << "Player: ";
    for (int i = 0; i < table.size(); i++) {
        if(i % 2 == 0) {
            cout << table[i] << " ";
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
    cout << endl;
    cout << "Computer: ";
    for (int i = 0; i < table.size(); i++) {
        if(i % 2 == 1) {
            cout << table[i] << " ";
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
    cout << endl;
    cout << "-------------------\n";
    cout << "\n";
}

void printCards(vector<string> table) {
    cout << "-------------------\n";
    cout << "Player: " << table[0] << "    Computer: " << table[1] << "\n";
    cout << "-------------------\n";
    cout << "\n";    
}

void drawCards(vector<string> &pDeck, vector<string> &cDeck, vector<string> &table) {
    table.push_back(pDeck[0]);
    pDeck.erase(pDeck.begin());

    table.push_back(cDeck[0]);
    cDeck.erase(cDeck.begin());
}

void dealCard(string *deck, vector<string> &playerDeck, vector<string> &dealtCards) {
    srand(time(0));
    int index = rand() % 52;
    string card = deck[index];
    while (cardAlreadyDealt(card, dealtCards)) {
        int index = rand() % 52;
        card = deck[index];
    }
    playerDeck.push_back(card);
    dealtCards.push_back(card);
}


bool cardAlreadyDealt(string card, vector<string> dealtCards) {
    for(string e : dealt) {
        if(card == e) {
            return true;
        }
    }
    return false;
}

void currentState(vector<string> pDeck, vector<string> cDeck) {
    cout << "-------------------\n";
    cout << "Player Deck: \n";
    for(string card : pDeck){
        cout << card << " ";
    }
    cout << "\n";
    cout << "Computer Deck: \n";
    for(string card : cDeck){
        cout << card << " ";
    }
    cout << "\n";
    cout << "-------------------\n";
    cout << "\n";    
}

int getCardValue(string card) {
    char cardValue = card[0];
    int value;
    switch (cardValue) {
        case '2':
            value = 2;
            break;
        case '3':
            value = 3;
            break;
        case '4':
            value = 4;
            break;
        case '5':
            value = 5;
            break;
        case '6':
            value = 6;
            break;
        case '7':
            value = 7;
            break;
        case '8':
            value = 8;
            break;
        case '9':
            value = 9;
            break;
        case '1':
            value = 10;
            break;
        case 'J':
            value = 11;
            break;
        case 'Q':
            value = 12;
            break;
        case 'K':
            value = 13;
            break;
        case 'A':
            value = 14;
            break;
        default:
            break;
    }
    return value;
}