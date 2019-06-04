//
// Created by jordan on 5/31/19.
//

#ifndef SNEK_SCOREBOARD_H
#define SNEK_SCOREBOARD_H

#include "GameObjects/GameObject.h"

#define SCOREBOARD_TIMES_TO_FLASH 10

class ScoreBoard : public GameObject
{
public:
    ScoreBoard(WINDOW *scoreboardWin, int y, int x);
    void Draw() override;
    void IncreaseScore(int scoreToAdd);
    void DecreaseScore(int scoreToRemove);
    void SetScore(int newScore);
    void flashScore();
private:
    bool    flash           {false};
    int     flashCount     {0};
    bool    colorFlip       {false};
    int     score           {0};
};


#endif //SNEK_SCOREBOARD_H
