#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <fstream>
#include <random>
#include <ctime>
using namespace std;

Board SetBoard(string fileName)
{
    vector<Tile> tiles;
    string filePath = "boards/";
    filePath += fileName;
    filePath += ".brd";

    ifstream boardFile;
    boardFile.open(filePath);

    if (boardFile.is_open()) {

        char nextChar;
        int index = 0;
        while (boardFile.get(nextChar)) {
            int row = index / 25;
            int column = index % 25;

            if (nextChar == '0') {
                tiles.push_back(Tile(row, column, false));
                index++;
            }
            else if (nextChar == '1') {
                tiles.push_back(Tile(row, column, true));
                index++;
            }
        }

        boardFile.close();

        Board board(tiles);
        board.SetNearMines();
        //board.SetTileState(0, "");

        return board;
    }
    else {
        cout << "Could not read file!" << endl;
        return Board();
    }
    
}

Board SetRandomBoard() {
    
    vector<int> randomNums;

    while (true) {
        std::random_device rd;
        std::mt19937 rand(rd());
        std::uniform_real_distribution<> dis(0, 399);

        int randomNum = (int)dis(rand); 
        bool inNumList = false;
        for (int currentNum : randomNums) {
            if (currentNum == randomNum) {
                inNumList = true;
            }
        }
        if (!inNumList) {
            randomNums.push_back(randomNum);
        }

        if (randomNums.size() >= 50) {
            break;
        }
    }

    vector<int> tilePlacement;
    for (int i = 0; i < 400; i++) {
        tilePlacement.push_back(0);
    }

    for (int randomNum : randomNums) {
        tilePlacement[randomNum] = 1;
    }

    int index = 0;
    vector<Tile> newTiles;
    for (int tilePlace : tilePlacement) {
        int row = index / 25;
        int column = index % 25;

        if (tilePlace == 0) {
            newTiles.push_back(Tile(row, column, false));
            index++;
        }
        else if (tilePlace == 1) {
            newTiles.push_back(Tile(row, column, true));
            index++;
        }
    }

    Board board(newTiles);
    board.SetNearMines();
    return board;
}

bool InList(Tile* toSearch, vector<Tile*>& searchList) {
    bool inList = false;
    for (Tile* element : searchList) {
        if (element == toSearch) {
            return true;
        }
    }
    return false;
}

void AddEmptySpace(Tile* tilePtr, vector<Tile*>& revealSpaces, Board board) {
    revealSpaces.push_back(tilePtr);

    vector<Tile*> neighbors = tilePtr->GetNeighbors();
    for (Tile* neighbor : neighbors) {
        if (neighbor->GetNearMines() == 0) {
            if (!InList(neighbor, revealSpaces)) {
                if ((!neighbor->IsRevealed()) && (!neighbor->HasMine()) && (!neighbor->IsFlagged())) {
                    AddEmptySpace(neighbor, revealSpaces, board);
                }
            }
        }
        else {
            revealSpaces.push_back(neighbor);
        }
    }
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    vector<sf::Sprite> hiddenTiles;
    vector<sf::Sprite> revealedTiles;
    vector<sf::Sprite> flags;
    map<int, sf::Sprite> numbers;
    map<int, sf::Sprite> mines;
    map<int, sf::Sprite> digits;

    bool lost = false;
    bool won = false;
    bool reveal = false;
    bool setBoardNow = true;
    bool setTilesNow = true;
    int minesLeft = -1;
    string boardToSet = "random";
    Board gameBoard;
    vector<Tile> nonMines;
    vector<Tile> currentlyRevealed;


    

    sf::Sprite tile_hidden(TextureManager::GetImage("tile_hidden"));
    int tileLength = tile_hidden.getTextureRect().width;
    int tileHeight = tile_hidden.getTextureRect().height;

    sf::Sprite face_happy(TextureManager::GetImage("face_happy"));
    sf::Sprite face_lose(TextureManager::GetImage("face_lose"));
    sf::Sprite face_win(TextureManager::GetImage("face_win"));
    face_happy.setPosition((float)((window.getSize().x / 2) - (face_happy.getTextureRect().width / 2)), (float)(tileHeight * 16));
    face_lose.setPosition((float)((window.getSize().x / 2) - (face_lose.getTextureRect().width / 2)), (float)(tileHeight * 16));
    face_win.setPosition((float)((window.getSize().x / 2) - (face_win.getTextureRect().width / 2)), (float)(tileHeight * 16));

    sf::Sprite debug(TextureManager::GetImage("debug"));
    sf::Sprite test_1(TextureManager::GetImage("test_1"));
    sf::Sprite test_2(TextureManager::GetImage("test_2"));
    sf::Sprite test_3(TextureManager::GetImage("test_3"));

    int testWidth = debug.getTextureRect().width;
    int rightSide = window.getSize().x;
    int sideWidth = ((testWidth * 3) / 2);
    int lastPosition = rightSide - sideWidth - (testWidth / 4);

    debug.setPosition((float)(lastPosition - (3 * testWidth)), (float)(tileHeight * 16));
    test_1.setPosition((float)(lastPosition - (2 * testWidth)), (float)(tileHeight * 16));
    test_2.setPosition((float)(lastPosition - testWidth), (float)(tileHeight * 16));
    test_3.setPosition((float)lastPosition, (float)(tileHeight * 16));

    while (window.isOpen())
    {
        if (setBoardNow) {
            setTilesNow = true;
            won = false;

            if (boardToSet == "random") {
                gameBoard = SetRandomBoard();
            }
            else {
                gameBoard = SetBoard(boardToSet);
            }

            revealedTiles.clear();
            hiddenTiles.clear();
            numbers.clear();
            mines.clear();
            nonMines.clear();
            minesLeft = gameBoard.GetNumMines();

            for (int i = 0; i < 400; i++) {
                Tile currentTile = gameBoard.GetIndexedTile(i);
                sf::Sprite tile_hidden(TextureManager::GetImage("tile_hidden"));
                sf::Sprite tile_revealed(TextureManager::GetImage("tile_revealed"));
                sf::Sprite flag(TextureManager::GetImage("flag"));

                float length = (float)(tileLength * currentTile.GetColumn());
                float height = (float)(tileHeight * currentTile.GetRow());

                tile_hidden.setPosition(length, height);
                tile_revealed.setPosition(length, height);
                flag.setPosition(length, height);

                hiddenTiles.push_back(tile_hidden);
                revealedTiles.push_back(tile_revealed);
                flags.push_back(flag);

                if (currentTile.HasMine()) {
                    sf::Sprite mine(TextureManager::GetImage("mine"));
                    mine.setPosition(length, height);
                    mines[i] = mine;
                }
                
                else {
                    nonMines.push_back(currentTile);
                    int numNeighbors = currentTile.GetNearMines();
                    switch (numNeighbors) {
                    case 1:
                    {
                        sf::Sprite number(TextureManager::GetImage("number_1"));
                        number.setPosition(length, height);
                        numbers[i] = number;
                        break;
                    }
                    case 2:
                    {
                        sf::Sprite number(TextureManager::GetImage("number_2"));
                        number.setPosition(length, height);
                        numbers[i] = number;
                        break;
                    }
                    case 3:
                    {
                        sf::Sprite number(TextureManager::GetImage("number_3"));
                        number.setPosition(length, height);
                        numbers[i] = number;
                        break;
                    }
                    case 4:
                    {
                        sf::Sprite number(TextureManager::GetImage("number_4"));
                        number.setPosition(length, height);
                        numbers[i] = number;
                        break;
                    }
                    case 5:
                    {
                        sf::Sprite number(TextureManager::GetImage("number_5"));
                        number.setPosition(length, height);
                        numbers[i] = number;
                        break;
                    }
                    case 6:
                    {
                        sf::Sprite number(TextureManager::GetImage("number_6"));
                        number.setPosition(length, height);
                        numbers[i] = number;
                        break;
                    }
                    case 7:
                    {
                        sf::Sprite number(TextureManager::GetImage("number_7"));
                        number.setPosition(length, height);
                        numbers[i] = number;
                        break;
                    }
                    case 8:
                    {
                        sf::Sprite number(TextureManager::GetImage("number_8"));
                        number.setPosition(length, height);
                        numbers[i] = number;
                        break;
                    }
                    default: //there are no nearby mines
                        break;
                    }
                }
           
            }
            setBoardNow = false;
        }


        if (setTilesNow || won) {
            vector<int> sepDigits;
            int toSep;
            if (!won) {
                toSep = minesLeft;
            }
            else {
                toSep = 0;
            }
            int nextDigit;
            bool negative = false;
            int length = 0;

            if (toSep < 0) {
                negative = true;
                toSep *= -1;
            }

            for (int i = 0; i < 3; i++) {
                nextDigit = toSep % 10;
                sepDigits.push_back(nextDigit);
                toSep /= 10;
            }
            reverse(sepDigits.begin(), sepDigits.end());

            if (negative) {
                sf::Sprite negative(TextureManager::GetImage("digits"));
                negative.setTextureRect(sf::IntRect(210, 0, 21, 32));
                negative.setPosition((float)length, (float)(16 * tileHeight));
                digits[0] = negative;
                length += 21;
            }

            for (int i = 1; i <= 3; i++) {
                int sepDigit = sepDigits[i - 1];
                switch (sepDigit) {
                case 0:
                {
                    sf::Sprite zero(TextureManager::GetImage("digits"));
                    zero.setTextureRect(sf::IntRect(0, 0, 21, 32));
                    zero.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = zero;
                    break;
                }
                case 1:
                {
                    sf::Sprite one(TextureManager::GetImage("digits"));
                    one.setTextureRect(sf::IntRect(21, 0, 21, 32));
                    one.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = one;
                    break;
                }
                case 2:
                {
                    sf::Sprite two(TextureManager::GetImage("digits"));
                    two.setTextureRect(sf::IntRect(42, 0, 21, 32));
                    two.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = two;
                    break;
                }
                case 3:
                {
                    sf::Sprite three(TextureManager::GetImage("digits"));
                    three.setTextureRect(sf::IntRect(63, 0, 21, 32));
                    three.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = three;
                    break;
                }
                case 4:
                {
                    sf::Sprite four(TextureManager::GetImage("digits"));
                    four.setTextureRect(sf::IntRect(84, 0, 21, 32));
                    four.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = four;
                    break;
                }
                case 5:
                {
                    sf::Sprite five(TextureManager::GetImage("digits"));
                    five.setTextureRect(sf::IntRect(105, 0, 21, 32));
                    five.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = five;
                    break;
                }
                case 6:
                {
                    sf::Sprite six(TextureManager::GetImage("digits"));
                    six.setTextureRect(sf::IntRect(126, 0, 21, 32));
                    six.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = six;
                    break;
                }
                case 7:
                {
                    sf::Sprite seven(TextureManager::GetImage("digits"));
                    seven.setTextureRect(sf::IntRect(147, 0, 21, 32));
                    seven.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = seven;
                    break;
                }
                case 8:
                {
                    sf::Sprite eight(TextureManager::GetImage("digits"));
                    eight.setTextureRect(sf::IntRect(168, 0, 21, 32));
                    eight.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = eight;
                    break;
                }
                case 9:
                {
                    sf::Sprite nine(TextureManager::GetImage("digits"));
                    nine.setTextureRect(sf::IntRect(189, 0, 21, 32));
                    nine.setPosition((float)length, (float)(16 * tileHeight));
                    digits[i] = nine;
                    break;
                }
                }
                length += 21;
            }
            setTilesNow = false;
        }

        vector<Tile> tiles = gameBoard.GetTiles();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto pos = sf::Mouse::getPosition(window);

                    if (face_happy.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y))) {
                        setBoardNow = true;
                        boardToSet = "random";
                        lost = false;
                    }

                    if (test_1.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y))) {
                        setBoardNow = true;
                        boardToSet = "testboard1";
                        lost = false;
                    }

                    if (test_2.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y))) {
                        setBoardNow = true;
                        boardToSet = "testboard2";
                        reveal = false;
                        lost = false;
                    }

                    if (test_3.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y))) {
                        setBoardNow = true;
                        boardToSet = "testboard3";
                        lost = false;
                    }

                    if (debug.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y))) {
                        reveal = !reveal;
                    }

                    if ((!lost) && (!won)) {
                   
                        for (unsigned int i = 0; i < hiddenTiles.size(); i++) {
                            if (hiddenTiles[i].getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y))) {
                                if (!tiles[i].IsFlagged()) {
                                    if (!tiles[i].IsRevealed()) {
                                        gameBoard.Reveal(i, true);
                                    }

                                    Tile tileRef = gameBoard.GetIndexedTile(i);
                                    if (tileRef.HasMine()) {
                                        lost = true;
                                        for (Tile tile : tiles) {
                                            if (tile.HasMine()) {
                                                gameBoard.Reveal(tile.GetIndex());
                                            }
                                        }
                                    }
                                    else if ((!tiles[i].IsRevealed()) && (tileRef.GetNearMines() == 0)) {
                                        vector<Tile*> revealSpaces;
                                        Tile* tile = gameBoard.GetTileRef(i);
                                        AddEmptySpace(tile, revealSpaces, gameBoard);
                                        for (Tile* revealSpace : revealSpaces) {
                                            int index = revealSpace->GetIndex();
                                            Tile currentTile = *revealSpace;
                                            gameBoard.Reveal(index, true);
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    if ((!lost) && (!won)) {
                        auto pos = sf::Mouse::getPosition(window);

                        for (unsigned int i = 0; i < hiddenTiles.size(); i++) {
                            if (hiddenTiles[i].getGlobalBounds().contains((sf::Vector2f((float)pos.x, (float)pos.y)))) {
                                if (!tiles[i].IsFlagged()) {
                                    if (!tiles[i].IsRevealed()) {
                                        gameBoard.Flag(i, true);
                                        minesLeft--;
                                        setTilesNow = true;
                                        break;
                                    }
                                }
                                else {
                                    gameBoard.Flag(i, false);
                                    minesLeft++;
                                    setTilesNow = true;
                                }
                            }
                        }
                    }
                }
            }
            
        }
        window.clear();

        for (sf::Sprite hiddenTile : hiddenTiles) {
            window.draw(hiddenTile);
        }

        if (won) {
            window.draw(face_win);
        }
        else if (!lost) {
            window.draw(face_happy);
        }
        else {
            window.draw(face_lose);
        }
        window.draw(test_1);
        window.draw(test_2);
        window.draw(test_3);
        window.draw(debug);

        currentlyRevealed.clear();

        for (unsigned int i = 0; i < tiles.size(); i++) {

            if (tiles[i].IsRevealed()) {
                window.draw(revealedTiles[i]);
                if (tiles[i].IsFlagged()) {
                    window.draw(flags[i]);
                }

                if (tiles[i].HasMine()) {
                    window.draw(mines[i]);
                }
                else if (tiles[i].GetNeighbors().size() > 0) {
                    window.draw(numbers[i]);
                }
                currentlyRevealed.push_back(tiles[i]);
            }

            if (!lost && (tiles[i].IsFlagged()) || (won && (tiles[i].HasMine()))) { //not supposed to be an else if
                window.draw(flags[i]);
            }
        }

        if (reveal) {
            auto iter = mines.begin();
            for (; iter != mines.end(); ++iter) {
                window.draw(iter->second);
            }
        }
        
        if ((currentlyRevealed.size() == nonMines.size()) && (!lost)) {
            won = true;
        }

        auto iterDigit = digits.begin();
        for (; iterDigit != digits.end(); ++iterDigit) {
            window.draw(iterDigit->second);
        }

        window.display();
        
    }

    TextureManager::Clear();
    
    return 0;
}