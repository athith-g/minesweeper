#include "board.hpp"
#include <iostream>

Board::Board(int columns, int rows, int mines)
{
    this->width = columns * 32;
    this->height = (rows * 32) + 88;
    this->numTiles = columns * rows;
    numMines = mines;
    notFound = Tile(1000, 1000);
    hidden = true;
    isWon = false;
    isLost = false;
    this->rows = rows;
    this->columns = columns;
    
    
    // LOAD TEXTURES
    sf::Texture texture;
    texture.loadFromFile("images/debug.png");
    textures.emplace("debug", texture);
    texture.loadFromFile("images/digits.png");
    textures.emplace("digits", texture);
    texture.loadFromFile("images/face_happy.png");
    textures.emplace("happy", texture);
    texture.loadFromFile("images/face_lose.png");
    textures.emplace("lose", texture);
    texture.loadFromFile("images/face_win.png");
    textures.emplace("win", texture);
    texture.loadFromFile("images/flag.png");
    textures.emplace("flag", texture);
    texture.loadFromFile("images/mine.png");
    textures.emplace("mine", texture);
    texture.loadFromFile("images/number_1.png");
    textures.emplace("1", texture);
    texture.loadFromFile("images/number_2.png");
    textures.emplace("2", texture);
    texture.loadFromFile("images/number_3.png");
    textures.emplace("3", texture);
    texture.loadFromFile("images/number_4.png");
    textures.emplace("4", texture);
    texture.loadFromFile("images/number_5.png");
    textures.emplace("5", texture);
    texture.loadFromFile("images/number_6.png");
    textures.emplace("6", texture);
    texture.loadFromFile("images/number_7.png");
    textures.emplace("7", texture);
    texture.loadFromFile("images/number_8.png");
    textures.emplace("8", texture);
    texture.loadFromFile("images/test_1.png");
    textures.emplace("test1", texture);
    texture.loadFromFile("images/test_2.png");
    textures.emplace("test2", texture);
    texture.loadFromFile("images/test_3.png");
    textures.emplace("test3", texture);
    texture.loadFromFile("images/tile_hidden.png");
    textures.emplace("hidden", texture);
    texture.loadFromFile("images/tile_revealed.png");
    textures.emplace("revealed", texture);
    
    texture.loadFromFile("images/digits.png", sf::IntRect(0, 0, 21, 32));
    digits.emplace("d0", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(21, 0, 21, 32));
    digits.emplace("d1", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(42, 0, 21, 32));
    digits.emplace("d2", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(63, 0,21, 32));
    digits.emplace("d3", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(84, 0, 21, 32));
    digits.emplace("d4", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(105, 0, 21, 32));
    digits.emplace("d5", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(126, 0, 21, 32));
    digits.emplace("d6", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(147, 0, 21, 32));
    digits.emplace("d7", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(168, 0, 21, 32));
    digits.emplace("d8", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(189, 0, 21, 32));
    digits.emplace("d9", texture);
    texture.loadFromFile("images/digits.png", sf::IntRect(210, 0, 21, 32));
    digits.emplace("d-", texture);

}

sf::Texture& Board::GetTexture(string texture)
{
    return textures.find(texture)->second;
}

sf::Texture& Board::GetDigitTexture(string texture)
{
    return digits.find(texture)->second;
}

int Board::GetWidth()
{
    return width;
}

int Board::GetHeight()
{
    return height;
}

void Board::AddRow(vector<Tile> tiles)
{
    this->tiles.push_back(tiles);
}

vector<vector<Tile>>& Board::GetTiles()
{
    return tiles;
}

Tile& Board::FindTile(int x, int y)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        for (int j = 0; j < tiles.at(i).size(); j++)
        {
            if (tiles.at(i).at(j).Matches(x, y))
            {
                return tiles.at(i).at(j);
            }
        }
    }
    return notFound;
}

void Board::SetState(string state)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        for (int j = 0; j < tiles.at(i).size(); j++)
        {
            if (state == "show")
            {
                if (tiles.at(i).at(j).IsMine())
                {
                    tiles.at(i).at(j).SetHidden(false);
                }
            }
            else if (state == "hide")
            {
                tiles.at(i).at(j).SetHidden(true);
                tiles.at(i).at(j).RightClick(false);
            }
        }
    }
    
    if (state == "show")
    {
        hidden = false;
    }
    else
    {
        hidden = true;
    }
}

void Board::SetMines()
{
    for (int i = 0; i < tiles.size() - 1; i++)
    {
        // Setting numbers for first row
        if (i == 0)
        {
            for (int j = 0; j < tiles.at(i).size(); j++)
            {
                // TOP LEFT CORNER
                if (j == 0 && !tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
                // TOP RIGHT CORNER
                else if (j == (tiles.at(i).size() - 1) && !tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
                // ROW OTHER THAN CORNERS
                else if (!tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
            }
        }
        
        else if (i == (tiles.size() - 1))
        {
            for (int j = 0; j < tiles.at(i).size(); j++)
            {
                // BOTTOM LEFT CORNER
                if (j == 0 && !tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
                // BOTTOM RIGHT CORNER
                else if (j == (tiles.at(i).size() - 1) && !tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
                // ROW OTHER THAN CORNERS
                else if (!tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
            }
        }
        
        else
        {
            for (int j = 0; j < tiles.at(i).size(); j++)
            {
                if (j == 0 && !tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
                else if (j == (tiles.at(i).size() - 1) && !tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
                else if (!tiles.at(i).at(j).IsMine())
                {
                    int count = 0;
                    
                    if (tiles.at(i).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i + 1).at(j).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j - 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j + 1).IsMine())
                    {
                        count++;
                    }
                    if (tiles.at(i - 1).at(j).IsMine())
                    {
                        count++;
                    }
                    
                    if (count > 0)
                    {
                        tiles.at(i).at(j).SetNum(true);
                        tiles.at(i).at(j).SetNumMines(count);
                    }
                }
            }
        }
    }
}

void Board::StartCascade(Tile &tile)
{
    if (tile.GetPosX() == 0 && tile.GetPosY() == 0)
    {
        Tile& right = this->FindTile(tile.GetPosX() + 1, tile.GetPosY());
        Tile& bottom = this->FindTile(tile.GetPosX(), tile.GetPosY() + 1);
        Tile& bottomRight = this->FindTile(tile.GetPosX() + 1, tile.GetPosY() + 1);
        
        if (right.IsNothing() && right.IsHidden() && !right.IsRightClicked())
        {
            right.SetHidden(false);
            StartCascade(right);
        }
        else if (right.IsNum() && !right.IsRightClicked())
        {
            right.SetHidden(false);
        }
        if (bottom.IsNothing() && bottom.IsHidden() && !bottom.IsRightClicked())
        {
            bottom.SetHidden(false);
            StartCascade(bottom);
        }
        else if (bottom.IsNum() && !bottom.IsRightClicked())
        {
            bottom.SetHidden(false);
        }
        if (bottomRight.IsNothing() && bottomRight.IsHidden()  && !bottomRight.IsRightClicked())
        {
            bottomRight.SetHidden(false);
            StartCascade(bottomRight);
        }
        else if (bottomRight.IsNum()  && !bottomRight.IsRightClicked())
        {
            bottomRight.SetHidden(false);
        }
        
    }
    else if (tile.GetPosX() == (tiles.at(0).size() - 1) && tile.GetPosY() == 0)
    {
        Tile& left = this->FindTile(tile.GetPosX() - 1, tile.GetPosY());
        Tile& bottom = this->FindTile(tile.GetPosX(), tile.GetPosY() + 1);
        Tile& bottomLeft = this->FindTile(tile.GetPosX() - 1, tile.GetPosY() + 1);
        
        if (left.IsNothing() && left.IsHidden() && !left.IsRightClicked())
        {
            left.SetHidden(false);
            StartCascade(left);
        }
        else if (left.IsNum() && !left.IsRightClicked())
        {
            left.SetHidden(false);
        }
        if (bottom.IsNothing() && bottom.IsHidden() && !bottom.IsRightClicked())
        {
            bottom.SetHidden(false);
            StartCascade(bottom);
        }
        else if (bottom.IsNum() && !bottom.IsRightClicked())
        {
            bottom.SetHidden(false);
        }
        if (bottomLeft.IsNothing() && bottomLeft.IsHidden() && !bottomLeft.IsRightClicked())
        {
            bottomLeft.SetHidden(false);
            StartCascade(bottomLeft);
        }
        else if (bottomLeft.IsNum() && !bottomLeft.IsRightClicked())
        {
            bottomLeft.SetHidden(false);
        }
        
    }
    else if(tile.GetPosY() == 0)
    {
        Tile& right = this->FindTile(tile.GetPosX() + 1, tile.GetPosY());
        Tile& left = this->FindTile(tile.GetPosX() - 1, tile.GetPosY());
        Tile& bottom = this->FindTile(tile.GetPosX(), tile.GetPosY() + 1);
        Tile& bottomRight = this->FindTile(tile.GetPosX() + 1, tile.GetPosY() + 1);
        Tile& bottomLeft = this->FindTile(tile.GetPosX() - 1, tile.GetPosY() + 1);
        
        if (right.IsNothing() && right.IsHidden() && !right.IsRightClicked())
        {
            right.SetHidden(false);
            StartCascade(right);
        }
        else if (right.IsNum() && !right.IsRightClicked())
        {
            right.SetHidden(false);
        }
        if (left.IsNothing() && left.IsHidden() && !left.IsRightClicked())
        {
            left.SetHidden(false);
            StartCascade(left);
        }
        else if (left.IsNum() && !left.IsRightClicked())
        {
            left.SetHidden(false);
        }
        if (bottom.IsNothing() && bottom.IsHidden() && !bottom.IsRightClicked())
        {
            bottom.SetHidden(false);
            StartCascade(bottom);
        }
        else if (bottom.IsNum() && !bottom.IsRightClicked())
        {
            bottom.SetHidden(false);
        }
        if (bottomRight.IsNothing() && bottomRight.IsHidden() && !bottomRight.IsRightClicked())
        {
            bottomRight.SetHidden(false);
            StartCascade(bottomRight);
        }
        else if (bottomRight.IsNum() && !bottomRight.IsRightClicked())
        {
            bottomRight.SetHidden(false);
        }
        if (bottomLeft.IsNothing() && bottomLeft.IsHidden() && !bottomLeft.IsRightClicked())
        {
            bottomLeft.SetHidden(false);
            StartCascade(bottomLeft);
        }
        else if (bottomLeft.IsNum() && !bottomLeft.IsRightClicked())
        {
            bottomLeft.SetHidden(false);
        }
    }
    else if (tile.GetPosX() == 0 && tile.GetPosY() == (tiles.size() - 2))
    {
        Tile& right = this->FindTile(tile.GetPosX() + 1, tile.GetPosY());
        Tile& top = this->FindTile(tile.GetPosX(), tile.GetPosY() - 1);
        Tile& topRight = this->FindTile(tile.GetPosX() + 1, tile.GetPosY() - 1);
        
        if (right.IsNothing() && right.IsHidden() && !right.IsRightClicked())
        {
            right.SetHidden(false);
            StartCascade(right);
        }
        else if (right.IsNum() && !right.IsRightClicked())
        {
            right.SetHidden(false);
        }
        if (top.IsNothing() && top.IsHidden() && !top.IsRightClicked())
        {
            top.SetHidden(false);
            StartCascade(top);
        }
        else if (top.IsNum() && !top.IsRightClicked())
        {
            top.SetHidden(false);
        }
        if (topRight.IsNothing() && topRight.IsHidden() && !topRight.IsRightClicked())
        {
            topRight.SetHidden(false);
            StartCascade(topRight);
        }
        else if (topRight.IsNum() && !topRight.IsRightClicked())
        {
            topRight.SetHidden(false);
        }
    }
    else if (tile.GetPosX() == (tiles.at(0).size() - 1) && tile.GetPosY() == (tiles.size() - 2))
    {
        Tile& left = this->FindTile(tile.GetPosX() - 1, tile.GetPosY());
        Tile& top = this->FindTile(tile.GetPosX(), tile.GetPosY() - 1);
        Tile& topLeft = this->FindTile(tile.GetPosX() - 1, tile.GetPosY() - 1);
        
        if (left.IsNothing() && left.IsHidden() && !left.IsRightClicked())
        {
            left.SetHidden(false);
            StartCascade(left);
        }
        else if (left.IsNum() && !left.IsRightClicked())
        {
            left.SetHidden(false);
        }
        if (top.IsNothing() && top.IsHidden() && !top.IsRightClicked())
        {
            top.SetHidden(false);
            StartCascade(top);
        }
        else if (top.IsNum() && !top.IsRightClicked())
        {
            top.SetHidden(false);
        }
        if (topLeft.IsNothing() && topLeft.IsHidden() && !topLeft.IsRightClicked())
        {
            topLeft.SetHidden(false);
            StartCascade(topLeft);
        }
        else if (topLeft.IsNum() && !topLeft.IsRightClicked())
        {
            topLeft.SetHidden(false);
        }
    }
    else if (tile.GetPosY() == (tiles.size() - 2))
    {
        Tile& right = this->FindTile(tile.GetPosX() + 1, tile.GetPosY());
        Tile& left = this->FindTile(tile.GetPosX() - 1, tile.GetPosY());
        Tile& top = this->FindTile(tile.GetPosX(), tile.GetPosY() - 1);
        Tile& topRight = this->FindTile(tile.GetPosX() + 1, tile.GetPosY() - 1);
        Tile& topLeft = this->FindTile(tile.GetPosX() - 1, tile.GetPosY() - 1);
        
        if (top.IsNothing() && top.IsHidden() && !top.IsRightClicked())
        {
            top.SetHidden(false);
            StartCascade(top);
        }
        else if (top.IsNum() && !top.IsRightClicked())
        {
            top.SetHidden(false);
        }
        if (right.IsNothing() && right.IsHidden() && !right.IsRightClicked())
        {
            right.SetHidden(false);
            StartCascade(right);
        }
        else if (right.IsNum() && !right.IsRightClicked())
        {
            right.SetHidden(false);
        }
        if (left.IsNothing() && left.IsHidden() && !left.IsRightClicked())
        {
            left.SetHidden(false);
            StartCascade(left);
        }
        else if (left.IsNum() && !left.IsRightClicked())
        {
            left.SetHidden(false);
        }
        if (topRight.IsNothing() && topRight.IsHidden() && !topRight.IsRightClicked())
        {
            topRight.SetHidden(false);
            StartCascade(topRight);
        }
        else if (topRight.IsNum() && !topRight.IsRightClicked())
        {
            topRight.SetHidden(false);
        }
        if (topLeft.IsNothing() && topLeft.IsHidden() && !topLeft.IsRightClicked())
        {
            topLeft.SetHidden(false);
            StartCascade(topLeft);
        }
        else if (topLeft.IsNum() && !topLeft.IsRightClicked())
        {
            topLeft.SetHidden(false);
        }
    }
    else
    {
        Tile& top = this->FindTile(tile.GetPosX(), tile.GetPosY() - 1);
        Tile& topRight = this->FindTile(tile.GetPosX() + 1, tile.GetPosY() - 1);
        Tile& topLeft = this->FindTile(tile.GetPosX() - 1, tile.GetPosY() - 1);
        Tile& right = this->FindTile(tile.GetPosX() + 1, tile.GetPosY());
        Tile& left = this->FindTile(tile.GetPosX() - 1, tile.GetPosY());
        Tile& bottom = this->FindTile(tile.GetPosX(), tile.GetPosY() + 1);
        Tile& bottomRight = this->FindTile(tile.GetPosX() + 1, tile.GetPosY() + 1);
        Tile& bottomLeft = this->FindTile(tile.GetPosX() - 1, tile.GetPosY() + 1);
        
        if (top.IsNothing() && top.IsHidden() && !top.IsRightClicked())
        {
            top.SetHidden(false);
            StartCascade(top);
        }
        else if (top.IsNum() && !top.IsRightClicked())
        {
            top.SetHidden(false);
        }
        if (right.IsNothing() && right.IsHidden() && !right.IsRightClicked())
        {
            right.SetHidden(false);
            StartCascade(right);
        }
        else if (right.IsNum() && !right.IsRightClicked())
        {
            right.SetHidden(false);
        }
        if (left.IsNothing() && left.IsHidden() && !left.IsRightClicked())
        {
            left.SetHidden(false);
            StartCascade(left);
        }
        else if (left.IsNum() && !left.IsRightClicked())
        {
            left.SetHidden(false);
        }
        if (topRight.IsNothing() && topRight.IsHidden() && !topRight.IsRightClicked())
        {
            topRight.SetHidden(false);
            StartCascade(topRight);
        }
        else if (topRight.IsNum() && !topRight.IsRightClicked())
        {
            topRight.SetHidden(false);
        }
        if (topLeft.IsNothing() && topLeft.IsHidden() && !topLeft.IsRightClicked())
        {
            topLeft.SetHidden(false);
            StartCascade(topLeft);
        }
        else if (topLeft.IsNum() && !topLeft.IsRightClicked())
        {
            topLeft.SetHidden(false);
        }
        if (bottom.IsNothing() && bottom.IsHidden() && !bottom.IsRightClicked())
        {
            bottom.SetHidden(false);
            StartCascade(bottom);
        }
        else if (bottom.IsNum() && !bottom.IsRightClicked())
        {
            bottom.SetHidden(false);
        }
        if (bottomRight.IsNothing() && bottomRight.IsHidden() && !bottomRight.IsRightClicked())
        {
            bottomRight.SetHidden(false);
            StartCascade(bottomRight);
        }
        else if (bottomRight.IsNum() && !bottomRight.IsRightClicked())
        {
            bottomRight.SetHidden(false);
        }
        if (bottomLeft.IsNothing() && bottomLeft.IsHidden() && !bottomLeft.IsRightClicked())
        {
            bottomLeft.SetHidden(false);
            StartCascade(bottomLeft);
        }
        else if (bottomLeft.IsNum() && !bottomLeft.IsRightClicked())
        {
            bottomLeft.SetHidden(false);
        }
    }
}

bool Board::IsHidden()
{
    return hidden;
}

bool Board::IsWon()
{
    return isWon;
}

bool Board::IsLost()
{
    return isLost;
}

void Board::UpdateStatus()
{
    int count = 0;
    
    for (int i = 0; i < tiles.size() - 1; i++)
    {
        for (int j = 0; j < tiles.at(i).size()-1; j++)
        {
            if (!tiles.at(i).at(j).IsMine() && !tiles.at(i).at(j).IsHidden())
            {
                count++;
            }
        }
    }
    
    int numOfMines = 0;
    
    for (int i = 0; i < tiles.size() - 1; i++)
    {
        for (int j = 0; j < tiles.at(i).size(); j++)
        {
            if (tiles.at(i).at(j).IsMine())
            {
                numOfMines++;
            }
        }
    }
    
    if (count == (numTiles - numOfMines))
    {
        isWon = true;
        
        for (int i = 0; i < tiles.size() - 1; i++)
        {
            for (int j = 0; j < tiles.at(i).size(); j++)
            {
                if (tiles.at(i).at(j).IsMine())
                {
                    tiles.at(i).at(j).RightClick(true);
                }
            }
        }
        
    }
}

void Board::Reset()
{
    isWon = false;
    isLost = false;
}

void Board::SetLost(bool lost)
{
    isLost = lost;
}

void Board::SetWon(bool won)
{
    isWon = won;
}

void Board::GenerateNewBoard()
{
    // CLEAR BOARD
    for (int i = 0; i < tiles.size() - 1; i++)
    {
        for (int j = 0; j < tiles.at(i).size(); j++)
        {
            Tile& tile = tiles.at(i).at(j);
            tile.SetMine(false);
            tile.SetNum(false);
            tile.SetNumMines(0);
            if (this->IsHidden())
            {
                tile.SetHidden(true);
            }
            else if (!this->IsHidden() && tile.IsMine())
            {
                tile.SetHidden(false);
            }
        }
    }
    
    int count = 0;
    
    bool completed = false;
    
    for (int i = 0; i < tiles.size() - 1; i++)
    {
        for (int j = 0; j < tiles.at(i).size(); j++)
        {
            Tile& tile = this->FindTile(Random::Int(0, columns - 1), Random::Int(0, rows - 2));
            if (tile.IsMine())
            {
                continue;
            }
            else
            {
                tile.SetMine(true);
                count ++;
                
                if (count == numMines)
                {
                    completed = true;
                    break;
                }
            }
        }
        
        if (completed)
        {
            break;
        }
    }
}

int Board::GetNumMines()
{
    int count = 0;
    
    for (int i = 0; i < tiles.size() - 1; i++)
    {
        for (int j = 0; j < tiles.at(i).size(); j++)
        {
            if(tiles.at(i).at(j).IsMine())
            {
                count ++;
            }
        }
    }
    
    return count;
}

int Board::GetFlags()
{
    int count = 0;
    
    for (int i = 0; i < tiles.size() - 1; i++)
    {
        for (int j = 0; j < tiles.at(i).size(); j++)
        {
            if(tiles.at(i).at(j).IsRightClicked())
            {
                count ++;
            }
        }
    }
    
    return count;
}


