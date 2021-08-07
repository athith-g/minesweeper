#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "board.hpp"

using namespace std;


int main()
{
    
    ifstream file("boards/config.cfg");
    
    int columns = 25;
    int rows = 25;
    int mines = 50;
    
    if (file.is_open())
    {
        file >> columns;
        file >> rows;
        file >> mines;
    }
    else
    {
        cout << "FILE WAS UNABLE TO BE OPENED (PATH: boards/config.cfg)" << endl;
        cout << "DEFAULT VALUES USED (25 x 25 minefield with 50 mines)" << endl;
    }
    
    Board board = Board(columns, rows, mines);
    
    sf::RenderWindow window(sf::VideoMode(board.GetWidth(), board.GetHeight()), "Minesweeper");
    
    // SET UP TILES
    // Tile coordinates
    int tile_x = 0;
    int tile_y = 0;
    
    for (int i = 0; i <= rows; i++)
    {
        tile_x = 0;
        
        vector<Tile> tiles;
        
        for (int j = 0; j <= columns; j++)
        {
            tiles.push_back(Tile(tile_x, tile_y));
            tile_x++;
        }
        
        board.AddRow(tiles);
        tile_y++;
    }
    
    bool gameOver = false;
    bool justLost = false;
    
    board.GenerateNewBoard();
    board.SetMines();
    
    while (window.isOpen())
    {
        window.clear();
        
        // Pixel coordinates
        int x = 0;
        int y = 0;
        
        sf::Sprite sprite;
        sf::Sprite sprite2;
        
        for (int i = 0; i < board.GetTiles().size() - 1; i++)
        {
            x = 0;
            
            for (int j = 0; j < board.GetTiles().at(i).size(); j++)
            {
                if (board.GetTiles().at(i).at(j).IsHidden())
                {
                    if (board.GetTiles().at(i).at(j).IsRightClicked())
                    {
                        sprite.setTexture(board.GetTexture("hidden"));
                        sprite.setPosition(x, y);
                        window.draw(sprite);
                        sprite.setTexture(board.GetTexture("flag"));
                        window.draw(sprite);
                    }
                    else
                    {
                        sprite.setTexture(board.GetTexture("hidden"));
                        sprite.setPosition(x, y);
                        window.draw(sprite);
                    }

                }
                else
                {
                    if (board.GetTiles().at(i).at(j).IsMine())
                    {
                        sprite.setTexture(board.GetTexture("revealed"));
                        sprite.setPosition(x, y);
                        window.draw(sprite);
                        sprite.setTexture(board.GetTexture("mine"));
                        window.draw(sprite);
                    }
                    else if (board.GetTiles().at(i).at(j).IsNum())
                    {
                        sprite.setTexture(board.GetTexture("revealed"));
                        sprite.setPosition(x, y);
                        window.draw(sprite);
                        sprite.setTexture(board.GetTexture(to_string(board.GetTiles().at(i).at(j).GetNumMines())));
                        window.draw(sprite);
                    }
                    else
                    {
                        sprite.setTexture(board.GetTexture("revealed"));
                        sprite.setPosition(x, y);
                        window.draw(sprite);
                    }

                }
                
                x += 32;
            }
            
            y+= 32;
        }
        

        string getDigit = "d";
        
        // SCORE
        int theScore = board.GetNumMines();
        int numFlags = board.GetFlags();
        int remainingMines = theScore - numFlags;
        
        if (remainingMines < 0)
        {
            getDigit += "-";
            remainingMines *= -1;
        }
        else
        {
            getDigit += to_string(remainingMines/100);
        }
        
        sf::Sprite score;
        score.setTexture(board.GetDigitTexture(getDigit));
        score.setPosition(16, y);
        window.draw(score);
        
        getDigit = "d";
        getDigit += to_string((remainingMines % 100)/ 10);
        score.setTexture(board.GetDigitTexture(getDigit));
        score.setPosition(37, y);
        window.draw(score);
        
        getDigit = "d";
        getDigit += to_string((remainingMines % 100) % 10);
        score.setTexture(board.GetDigitTexture(getDigit));
        score.setPosition(58, y);
        window.draw(score);
        
    

    
        // SET UP FACE
        float new_x;
        new_x = 32 * columns/2;
        sf::Sprite face;
        if (!gameOver)
        {
            if (!board.IsWon())
            {
                face.setTexture(board.GetTexture("happy"));
            }
            else
            {
                face.setTexture(board.GetTexture("win"));
            }

        }
        else
        {
            face.setTexture(board.GetTexture("lose"));
        }
        face.setPosition(new_x,y);
        window.draw(face);
        
        // SET UP TEST BUTTONS
        new_x += 128;
        sf::Sprite test;
        test.setTexture(board.GetTexture("debug"));
        test.setPosition(new_x,y);
        window.draw(test);
        
        new_x += 64;
        test.setTexture(board.GetTexture("test1"));
        test.setPosition(new_x,y);
        window.draw(test);
        
        new_x += 64;
        test.setTexture(board.GetTexture("test2"));
        test.setPosition(new_x,y);
        window.draw(test);
        
        new_x += 64;
        test.setTexture(board.GetTexture("test3"));
        test.setPosition(new_x,y);
        window.draw(test);

        window.display();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if ((event.mouseButton.y/32) < rows)
                    {
                        Tile& tile = board.FindTile(event.mouseButton.x / 32, event.mouseButton.y / 32);
                        if (!tile.IsRightClicked() && !board.IsWon() && !board.IsLost() && !(tile.IsNum() && !tile.IsHidden()))
                        {
                            tile.RightClick(true);
                        }
                        else
                        {
                            tile.RightClick(false);
                        }
                    }
                }
                else
                {
                    if ((event.mouseButton.y/32) < rows && !board.IsWon() && !board.IsLost())
                    {
                        Tile& tile = board.FindTile(event.mouseButton.x / 32, event.mouseButton.y / 32);
                        
                        if(!tile.IsRightClicked())
                        {
                            tile.SetHidden(false);
                            if (!tile.IsNum() && !tile.IsMine())
                            {
                                board.StartCascade(board.FindTile(event.mouseButton.x / 32, event.mouseButton.y / 32));

                            }
                            else if (tile.IsMine())
                            {
                                board.SetState("show");
                                board.SetLost(true);
                                gameOver = true;
                                justLost = true;
                            }
                        }
                        
                        board.UpdateStatus();
                    }
                    else
                    {
                        // DEBUG BUTTON
                        if (event.mouseButton.x > (((float) (32 * columns) / 2) + 128) && event.mouseButton.x < (((float) (32 * columns) / 2) + 192) && !board.IsWon() && !board.IsLost())
                        {
                            if (board.IsHidden())
                            {
                                board.SetState("show");
                            }
                            else
                            {
                                board.SetState("hide");
                            }
                        }
                        
                        // SMILEY FACE BUTTON
                        else if (event.mouseButton.x > ((float) (32 * columns) / 2) && event.mouseButton.x < (((float) (32 * columns) / 2) + 64) && (event.mouseButton.y/32) >= rows)
                        {
                            numFlags = 0;
                            board.Reset();
                            board.GenerateNewBoard();
                            board.SetMines();
                            
                            if (board.IsHidden())
                            {
                                board.SetState("hide");
                            }
                            else if (justLost)
                            {
                                board.SetState("hide");
                                justLost = false;
                            }
                            else
                            {
                                board.SetState("hide");
                                board.SetState("show");
                            }

                            
                            gameOver = false;
                        }
                        
                        // TESTBOARD1 BUTTON
                        else if (event.mouseButton.x > (((float) (32 * columns) / 2) + 192) && event.mouseButton.x < (((float) (32 * columns) / 2) + 256) && (event.mouseButton.y/32) >= rows)
                        {
                            if (board.IsLost() || board.IsWon())
                            {
                                board.SetState("hide");
                                
                                if (board.IsLost())
                                {
                                    board.SetLost(false);
                                    gameOver = false;
                                }
                                
                                if (board.IsWon())
                                {
                                    board.SetWon(false);
                                }
                            }
                            
                            numFlags = 0;
                            tile_x = 0;
                            tile_y = 0;
                            
                            string line;
                            ifstream boardState("boards/testboard1.brd");
                            
                            while (getline(boardState, line, '\n'))
                            {
                                tile_x = 0;
                                
                                for (char c: line)
                                {
                                    if (c == '1')
                                    {
                                        board.FindTile(tile_x, tile_y).SetMine(true);
                                        board.FindTile(tile_x, tile_y).SetNum(false);
                                    }
                                    else
                                    {
                                        board.FindTile(tile_x, tile_y).SetMine(false);
                                        board.FindTile(tile_x, tile_y).SetNum(false);
                                    }
                                    
                                    if (!board.IsHidden() && board.FindTile(tile_x, tile_y).IsMine())
                                    {
                                        board.FindTile(tile_x, tile_y).SetHidden(false);
                                    }
                                    else if (!board.IsHidden() && !board.FindTile(tile_x, tile_y).IsMine())
                                    {
                                        board.FindTile(tile_x, tile_y).SetHidden(true);
                                    }
                                    else if (board.IsHidden() && !board.FindTile(tile_x, tile_y).IsMine())
                                    {
                                        board.FindTile(tile_x, tile_y).SetHidden(true);
                                    }
                                    
                                    board.FindTile(tile_x, tile_y).RightClick(false);
                                    tile_x++;
                                }
                                
                                tile_y++;
                            }
                            
                            board.SetMines();
                            
                        }
                        
                        // TESTBOARD2 BUTTON
                        else if (event.mouseButton.x > (((float) (32 * columns) / 2) + 256) && event.mouseButton.x < (((float) (32 * columns) / 2) + 320)  && (event.mouseButton.y/32) >= rows)
                        {
                            if (board.IsLost() || board.IsWon())
                            {
                                board.SetState("hide");
                                
                                if (board.IsLost())
                                {
                                    board.SetLost(false);
                                    gameOver = false;
                                }
                                
                                if (board.IsWon())
                                {
                                    board.SetWon(false);
                                }
                            }
                            
                            numFlags = 0;
                            tile_x = 0;
                            tile_y = 0;
                            
                            string line;
                            ifstream boardState("boards/testboard2.brd");
                            
                            while (getline(boardState, line, '\n'))
                            {
                                tile_x = 0;
                                
                                for (char c: line)
                                {
                                    if (c == '1')
                                    {
                                        board.FindTile(tile_x, tile_y).SetMine(true);
                                        board.FindTile(tile_x, tile_y).SetNum(false);
                                    }
                                    else
                                    {
                                        board.FindTile(tile_x, tile_y).SetMine(false);
                                        board.FindTile(tile_x, tile_y).SetNum(false);
                                    }
                                    
                                    if (!board.IsHidden() && board.FindTile(tile_x, tile_y).IsMine())
                                    {
                                        board.FindTile(tile_x, tile_y).SetHidden(false);
                                    }
                                    else if (!board.IsHidden() && !board.FindTile(tile_x, tile_y).IsMine())
                                    {
                                        board.FindTile(tile_x, tile_y).SetHidden(true);
                                    }
                                    
                                    board.FindTile(tile_x, tile_y).RightClick(false);
                                    tile_x++;
                                }
                                
                                tile_y++;
                            }
                            
                            board.SetMines();
                        }
                        
                        //TESTBOARD3 BUTTON
                        else if (event.mouseButton.x > (((float) (32 * columns) / 2) + 320) && event.mouseButton.x < (((float) (32 * columns) / 2) + 384)  && (event.mouseButton.y/32) >= rows)
                        {
                            if (board.IsLost() || board.IsWon())
                            {
                                board.SetState("hide");
                                
                                if (board.IsLost())
                                {
                                    board.SetLost(false);
                                    gameOver = false;
                                }
                                
                                if (board.IsWon())
                                {
                                    board.SetWon(false);
                                }
                            }
                            
                            numFlags = 0;
                            tile_x = 0;
                            tile_y = 0;
                            
                            string line;
                            ifstream boardState("boards/testboard3.brd");
                            
                            while (getline(boardState, line, '\n'))
                            {
                                tile_x = 0;
                                
                                for (char c: line)
                                {
                                    if (c == '1')
                                    {
                                        board.FindTile(tile_x, tile_y).SetMine(true);
                                        board.FindTile(tile_x, tile_y).SetNum(false);
                                    }
                                    else
                                    {
                                        board.FindTile(tile_x, tile_y).SetMine(false);
                                        board.FindTile(tile_x, tile_y).SetNum(false);
                                    }
                                    
                                    if (!board.IsHidden() && board.FindTile(tile_x, tile_y).IsMine())
                                    {
                                        board.FindTile(tile_x, tile_y).SetHidden(false);
                                    }
                                    else if (!board.IsHidden() && !board.FindTile(tile_x, tile_y).IsMine())
                                    {
                                        board.FindTile(tile_x, tile_y).SetHidden(true);
                                    }
                                    
                                    board.FindTile(tile_x, tile_y).RightClick(false);
                                    tile_x++;
                                }
                                tile_y++;
                            }
                            
                            board.SetMines();
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}
