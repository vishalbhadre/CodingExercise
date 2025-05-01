// ConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BowlingGame.h"
#include <algorithm>
#include <string>

using namespace std;

uint16_t GetNumberAsInput(std::string printBeforeInputAcceptance)
{
    char buff[3];
    uint16_t number = 0;

    while (true)
    {
        std::cout << printBeforeInputAcceptance;
        std::cin.clear();
        std::cin.getline(buff, 3);
        bool validEntry = true;

        validEntry = std::all_of(std::begin(buff), std::begin(buff) + 2, [](char ch) {
            return ((ch >= 0x30) && (ch <= 0x39) || (0x00 == ch));
            });

        number = std::strtoul(buff, nullptr, 10);

        if ((!validEntry) || std::cin.fail())
        {
            std::cin.clear();
            std::cout << "Invalid inputs ..." << std::endl;
        }
        else
        {
            break;
        }
    }
    return number;
}

int main()
{
    std::cout << "Welcome to the Bowling Game!\n";
    BowlingGame game;

    char buff[3];
    uint16_t numberOfPlayers = 0;

    try
    {
        numberOfPlayers = GetNumberAsInput("Enter number of players : ");

        game.SetNumberOfPlayers(numberOfPlayers);
        for (uint16_t currPlayerIndex = 0; currPlayerIndex < numberOfPlayers; currPlayerIndex++)
        {
            std::string name;
            std::cout << "Enter player name : ";
            std::cin >> name;
            game.SetPlayerName(currPlayerIndex, name);
        }

        game.DisplayPlayers();

        std::cin.clear();
        cin.ignore(INT_MAX, '\n');

        for (uint16_t currFrameIndex = 0; currFrameIndex < n_numberOfFrames; currFrameIndex++)
        {
            for (uint16_t currPlayerIndex = 0; currPlayerIndex < numberOfPlayers; currPlayerIndex++)
            {
                uint16_t tryIndex = 0;
                while (true)
                {
                    tryIndex++;
                    uint16_t numberOfPinsKnockedDown = 0;

                    while (true)
                    {
                        numberOfPinsKnockedDown = GetNumberAsInput("Enter number of pins knowed down for this try of frame " + std::to_string(currFrameIndex + 1) + " by " + game.GetPlayerName(currPlayerIndex) + " : ");

                        if (game.isValidInput(currPlayerIndex, currFrameIndex, tryIndex, numberOfPinsKnockedDown))
                            break;
                        else
                        {
                            std::cout << "Invalid inputs ..." << std::endl;
                        }
                    }
                    if (numberOfPinsKnockedDown == n_numberOfPins)
                    {
                        game.UpdateFrameScoreAfterATry(currPlayerIndex, currFrameIndex, tryIndex, numberOfPinsKnockedDown);
                        break;
                    }
                    else
                    {
                        game.UpdateFrameScoreAfterATry(currPlayerIndex, currFrameIndex, tryIndex, numberOfPinsKnockedDown);
                    }

                    if ((currFrameIndex < (n_numberOfFrames - 1)) && (tryIndex == 2))
                        break;
                    else if (currFrameIndex == (n_numberOfFrames - 1))
                    {
                        bool isSpareOrStrike = false;
                        if (game.isFrameAStrike(currPlayerIndex, currFrameIndex))
                        {
                            isSpareOrStrike = true;
                        }
                        else if (game.isFrameASpare(currPlayerIndex, currFrameIndex))
                        {
                            isSpareOrStrike = true;
                        }

                        if (isSpareOrStrike)
                        {
                            if (tryIndex == 3)
                            {
                                break;
                            }
                        }
                        else if (tryIndex == 2)
                            break;
                    }
                }
            }
        }
        game.DisplayScore();
    }
    catch (...)
    {
        std::cout << "Unexpected behavior observed..." << std::endl;
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
