// ConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BowlingGame.h"

using namespace std;

int main()
{
    std::cout << "Welcome to the Bowling Game!\n";
    BowlingGame game;

    for (uint16_t currFrameIndex = 0; currFrameIndex < n_numberOfFrames; currFrameIndex++)
    {
        uint16_t tryIndex = 0;
        while (true)
        {
            tryIndex++;
            uint16_t numberOfPinsKnockedDown = 0;
            while (true)
            {
                std::cout << "Bowl and enter number of pins knowed down for this try of frame " << currFrameIndex + 1 << " : ";
                std::cin >> numberOfPinsKnockedDown;

                if (game.isValidInput(currFrameIndex, tryIndex, numberOfPinsKnockedDown))
                    break;
                else
                {
                    std::cout << "Invalid inputs for this try of frame " << currFrameIndex + 1 << std::endl;
                }
            }
            if (numberOfPinsKnockedDown == n_numberOfPins)
            {
                game.UpdateFrameScoreAfterATry(currFrameIndex, tryIndex, numberOfPinsKnockedDown);
                break;
            }
            else
            {
                game.UpdateFrameScoreAfterATry(currFrameIndex, tryIndex, numberOfPinsKnockedDown);
            }

            if ((currFrameIndex < (n_numberOfFrames - 1)) && (tryIndex == 2))
                break;
            else if (currFrameIndex == (n_numberOfFrames - 1))
            {
                bool isSpareOrStrike = false;
                if (game.isFrameAStrike(currFrameIndex))
                {
                    isSpareOrStrike = true;
                }
                else if (game.isFrameASpare(currFrameIndex))
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
    game.DisplayScore();
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
