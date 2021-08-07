#pragma once

class Tile
{
private:
    bool hidden;
    bool mine;
    bool isNum;
    int num;
    int position[2];
    int numMines;
    bool rightClicked;
    bool correctlyIdentified;
    
public:
    Tile();
    Tile(int x, int y);
    bool IsMine();
    bool IsNum();
    bool IsHidden();
    bool IsNothing();
    void SetMine(bool cond);
    void SetNum(bool num);
    void SetHidden(bool cond);
    bool Matches(int x, int y);
    void SetNumMines(int numMines);
    int GetNumMines();
    int GetPosX();
    int GetPosY();
    void RightClick(bool clickState);
    bool IsRightClicked();
    bool IsCorrect();
};
