#include "Card.hpp"
#include "URL.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv)
{
    URL* u1 = new URL("https://api.hearthstonejson.com/v1/25770/enUS/cards.json");
    string jsonString = u1->getContents();
    json parsedJson = json::parse(jsonString);
    //Card* theMinionCards[parsedJson.size()];


    //Attempt to make an array that fits all of the minion cards in the JSON file
    int numberOfMinionCards = 0;
    for(int i = 0; i < parsedJson.size(); i++)
    {
        json currentValue = parsedJson[i]; //I think this line is the source of my woes
        if(currentValue["type"] == "MINION")
        {
            numberOfMinionCards++;
        }
    }
    Card* theMinionCards[numberOfMinionCards];

    int count = 0;
    if(parsedJson.is_array()) //Fills theMinionCards[] with all the minion cards
    {
        for(int i = 0; i < parsedJson.size(); i++) 
        {
            json currValue = parsedJson[i];
            if(currValue.is_object())
            {
                if(currValue["type"] == "MINION")
                {
                    count++;
                    cout << "Minion card number: " << count << endl;
                    string name = currValue.value("name", "N/A");
                    int attack = currValue.value("attack", -1);
                    int defense = currValue.value("health", -1);
                    int manaCost = currValue.value("cost", -1);
                    theMinionCards[i] = new Card(name, manaCost, attack, defense);
                    theMinionCards[i]->display();
                }
            }
        }
    }

    //Insertion sort
    Card* tempSwap;
    int theFollower;
    for(int currStart = 1; currStart < sizeof(theMinionCards)/sizeof(theMinionCards[0]); currStart++)
    {
        theFollower = currStart;
        while(theFollower > 0 && theMinionCards[theFollower]->getDefense() < theMinionCards[theFollower-1]->getDefense())
        {
            tempSwap = theMinionCards[theFollower];
            theMinionCards[theFollower] = theMinionCards[theFollower-1];
            theMinionCards[theFollower-1] = tempSwap;
            theFollower--;
        }
    }

    //Display after sort is completed
    for(int i = 0; i < sizeof(theMinionCards)/sizeof(theMinionCards[0]); i++)
    {
        theMinionCards[i]->display();
    }

    cout << "Number of Cards: " << parsedJson.size() << endl;
    return 0;
}