/**
 * The scoreboard for the Snek Game.
 */

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(WINDOW *scoreboardWin, int y, int x) : GameObject(scoreboardWin, y, x)
{
    // TODO: We need some way of tracking color palates.
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

void ScoreBoard::Draw()
{

    if (flash)
    {
        flashScore();
    }
    box(win, 0, 0);
    wmove(win, gety(), getx());
    wprintw(win, "Score: %d", score);
}


void ScoreBoard::IncreaseScore(int scoreToAdd)
{
    flash = true;
    flashCount = SCOREBOARD_TIMES_TO_FLASH;
    score += scoreToAdd;
}

void ScoreBoard::DecreaseScore(int scoreToRemove)
{
    score -= scoreToRemove;
    if (score < 0)
    {
        score = 0;
    }

}

void ScoreBoard::SetScore(int newScore)
{
    score = newScore;
}

void ScoreBoard::flashScore()
{
    if (flashCount <= 0)
    {
        wattroff(win, COLOR_PAIR(3));
        flash = false;
        return;
    }
    if (colorFlip)
    {
        wattron(win, COLOR_PAIR(3));
    }
    else
    {
        wattroff(win, COLOR_PAIR(3));
    }
    colorFlip = !colorFlip;
    flashCount--;
}
