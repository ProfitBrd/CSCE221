#include <string>
#include <sstream>

#include "Card.h"

int rand221(void) {
    return rand();
}

// You may want to write the following three functions, but they are not required

// std::istream& operator>>(std::istream& in, Suit& suit) {
//    
// }

// Rank to_rank(const std::string& string) {
//    
// }

// std::istream& operator>>(std::istream& in, Card& card) {
//    
// }


List<Card> buildDeck(std::istream& file) {
    List<Card> deck;
    while (!file.eof()){
        std::istringstream inSS;
        std::string nextLine;
        
        getline(file, nextLine);
        if (nextLine.empty()){
            break;
        }
        inSS.str(nextLine);

        std::string cardSuit;
        std::string cardRank;
        Card currentCard;
        
        
        inSS >> cardSuit;
        inSS >> cardRank;
        
        if (cardSuit == "spades"){
            currentCard.suit = Suit::SPADES;
        }
        else if (cardSuit == "diamonds"){
            currentCard.suit = Suit::DIAMONDS;
        }
        else if (cardSuit == "clubs"){
            currentCard.suit = Suit::CLUBS;
        }
        else if (cardSuit == "hearts"){
            currentCard.suit = Suit::HEARTS;
        }
        
        if (cardRank == "ace"){
            currentCard.rank = ACE;
        }
        else if (cardRank == "jack"){
            currentCard.rank = JACK;
        }
        else if (cardRank == "queen"){
            currentCard.rank = QUEEN;
        }
        else if (cardRank == "king"){
            currentCard.rank = KING;
        }
        else{
            currentCard.rank = std::stoi(cardRank);
        }
        deck.push_back(currentCard);
    }
    return deck;
}

List<Card> shuffle(const List<Card>& deck) {
    List<Card> newDeck;
    
    for (Card currentCard : deck){
        if (rand221()%2 == 0){
            newDeck.push_front(currentCard);
        }
        else{
            newDeck.push_back(currentCard);
        }
    }
    return newDeck;
}