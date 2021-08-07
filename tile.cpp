#include "tile.hpp"
#include <vector>
using namespace std;

Tile::Tile()
{
    hidden = true;
    mine = false;
    isNum = false;
    rightClicked = false;
    correctlyIdentified = false;
    num = 10;
}

Tile::Tile(int x, int y)
{
    hidden = true;
    mine = false;
    isNum = false;
    rightClicked = false;
    correctlyIdentified = false;
    position[0] = x;
    position[1] = y;
    num = 10;
}

bool Tile::IsMine()
{
    return mine;
}

bool Tile::IsNum()
{
    return isNum;
}

bool Tile::IsHidden()
{
    return hidden;
}

void Tile::SetNum(bool num)
{
    this->isNum = num;
}

void Tile::SetHidden(bool cond)
{
    hidden = cond;
}

void Tile::SetMine(bool cond)
{
    mine = cond;
}

bool Tile::Matches(int x, int y)
{
    if (position[0] == x && position[1] == y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Tile::SetNumMines(int numMines)
{
    this->numMines = numMines;
}


int Tile::GetNumMines()
{
    return numMines;
}

int Tile::GetPosX()
{
    return position[0];
}

int Tile::GetPosY()
{
    return position[1];
}

bool Tile::IsNothing()
{
    if (isNum == false && mine == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tile::IsRightClicked()
{
    return rightClicked;
}

void Tile::RightClick(bool clickState)
{
    rightClicked = clickState;
}

bool Tile::IsCorrect()
{
    if (rightClicked && mine)
    {
        correctlyIdentified = true;
    }

    return correctlyIdentified;
}
