#pragma once
#include <string>
#include <vector>
#include "tile.hpp"
#include "Random.hpp"
#include <SFML/Graphics.hpp>
using namespace std;


class Board
{
private:
    int width;
    int height;
    int numTiles;
    int numMines;
    int rows;
    int columns;
    vector<vector<Tile>> tiles;
    map<string, sf::Texture> textures;
    map<string, sf::Texture> digits;
    Tile notFound;
    bool hidden;
    bool isWon;
    bool isLost;
    
public:
    Board();
    Board(int columns, int rows, int mines);
    int GetWidth();
    int GetHeight();
    sf::Texture& GetTexture(string texture);
    sf::Texture& GetDigitTexture(string digit);
    Tile& FindTile(int x, int y);
    void AddRow(vector<Tile> tiles);
    vector<vector<Tile>>& GetTiles();
    void SetState(string state);
    void SetMines();
    void StartCascade(Tile& tile);
    bool IsHidden();
    bool IsWon();
    bool IsLost();
    void Reset();
    void UpdateStatus();
    void SetLost(bool lost);
    void SetWon(bool won);
    void GenerateNewBoard();
    int GetNumMines();
    int GetFlags();
};
