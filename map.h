#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

//定義磚塊特質

class GameTile {
public:
	bool isPassable;
	bool isExit;
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;
	//四個變數分別為: x,y,可否穿越,可否結束遊戲 
	GameTile(std::string, float, float, bool, bool);
	bool setUpSprite(std::string);
};

GameTile::GameTile(std::string textureName, float x, float y, bool passable, bool exit) {
	if (!setUpSprite(textureName)) {
		return;
	}
	//傳入地圖上每格地形的x,y值 
	pos = sf::Vector2f(x, y);
	sprite.setPosition(pos);
	//此地可否穿越 
	isPassable = passable;
	//此地是否使遊戲結束(例如門，本遊戲全部設為無法使遊戲結束) 
	isExit = exit;
}
bool GameTile::setUpSprite(std::string textureName) {
	if (!texture.loadFromFile(textureName)) {
		return false;
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	//單位地形的大小 
	sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
	return true;
}




class GameWorld {
	sf::Vector2i exitPos;
	sf::Vector2i playerPos;
	std::vector<sf::Vector2i>enemyPositions;
	void setUpInitialState();
	void setUpEnemyPositions();
	void setUpTiles();

public:
	std::vector< std::vector<GameTile*> > tiles;
	int gridLength;
	int gridWidth;
	GameWorld();
	//回傳是否在障礙物上 
	//bool check(GameWorld gameWorld, int x, int y);
};

GameWorld::GameWorld() {
    //分割的地圖塊數，地圖只能為正方形 
    gridLength = 17;
    gridWidth = 27;
    //設定地圖 
    setUpInitialState();
}

void GameWorld::setUpInitialState() {
    //exitPos = sf::Vector2i(1,0);
    //playerPos = sf :: Vector2i(gridLength-1, gridLength-1);
    //setUpEnemyPositions(); 

    //地圖設定 
    setUpTiles();
}

//void GameWorld::setUpEnemyPositions(){
    //enemyPositions.clear();
    //enemyPositions.push_back(sf::Vector2i(0,2));
    //enemyPositions.push_back(sf::Vector2i(6,0));
    //enemyPositions.push_back(sf::Vector2i(2,7));

//}

void GameWorld::setUpTiles() {
    tiles.clear();
    //組成地圖 
    std::vector<GameTile*> firstRow;
    firstRow.push_back(new GameTile("wall.jpg", 0, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 40, 0, false, true));
    firstRow.push_back(new GameTile("wall.jpg", 80, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 120, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 160, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 200, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 240, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 280, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 320, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 360, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 400, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 440, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 480, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 520, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 560, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 600, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 640, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 680, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 720, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 760, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 800, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 840, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 880, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 920, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 960, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 1000, 0, false, false));
    firstRow.push_back(new GameTile("wall.jpg", 1040, 0, false, false));

    tiles.push_back(firstRow);
    std::vector<GameTile*> secondRow;
    secondRow.push_back(new GameTile("wall.jpg", 0, 40, false, false));
    secondRow.push_back(new GameTile("ground.jpg", 40, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 80, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 120, 40, true, false));
    secondRow.push_back(new GameTile("wall.jpg", 160, 40, false, false));
    secondRow.push_back(new GameTile("ground.jpg", 200, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 240, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 280, 40, true, false));
    secondRow.push_back(new GameTile("wall.jpg", 320, 40, false, false));
    secondRow.push_back(new GameTile("ground.jpg", 360, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 400, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 440, 40, true, false));
    secondRow.push_back(new GameTile("wall.jpg", 480, 40, false, false));
    secondRow.push_back(new GameTile("ground.jpg", 520, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 560, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 600, 40, true, false));
    secondRow.push_back(new GameTile("wall.jpg", 640, 40, false, false));
    secondRow.push_back(new GameTile("ground.jpg", 680, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 720, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 760, 40, true, false));
    secondRow.push_back(new GameTile("wall.jpg", 800, 40, false, false));
    secondRow.push_back(new GameTile("ground.jpg", 840, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 880, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 920, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 960, 40, true, false));
    secondRow.push_back(new GameTile("ground.jpg", 1000, 40, true, false));
    secondRow.push_back(new GameTile("wall.jpg", 1040, 40, false, false));
    tiles.push_back(secondRow);

    std::vector<GameTile*> thirdRow;
    thirdRow.push_back(new GameTile("wall.jpg", 0, 80, false, false));
    thirdRow.push_back(new GameTile("ground.jpg", 40, 80, false, false));
    thirdRow.push_back(new GameTile("wall.jpg", 80, 80, false, false));
    thirdRow.push_back(new GameTile("ground.jpg", 120, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 160, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 200, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 240, 80, true, false));
    thirdRow.push_back(new GameTile("wall.jpg", 280, 80, false, false));
    thirdRow.push_back(new GameTile("wall.jpg", 320, 80, false, false));
    thirdRow.push_back(new GameTile("ground.jpg", 360, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 400, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 440, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 480, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 520, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 560, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 600, 80, true, false));
    thirdRow.push_back(new GameTile("wall.jpg", 640, 80, false, false));
    thirdRow.push_back(new GameTile("wall.jpg", 680, 80, false, false));
    thirdRow.push_back(new GameTile("ground.jpg", 720, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 760, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 800, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 840, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 880, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 920, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 960, 80, true, false));
    thirdRow.push_back(new GameTile("ground.jpg", 1000, 80, true, false));
    thirdRow.push_back(new GameTile("wall.jpg", 1040, 80, false, false));
    tiles.push_back(thirdRow);

    std::vector<GameTile*> fourthRow;
    fourthRow.push_back(new GameTile("wall.jpg", 0, 120, false, false));
    fourthRow.push_back(new GameTile("ground.jpg", 40, 120, false, false)); 
    fourthRow.push_back(new GameTile("wall.jpg", 80, 120, false, false));
    fourthRow.push_back(new GameTile("ground.jpg", 120, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 160, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 200, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 240, 120, true, false));
    fourthRow.push_back(new GameTile("wall.jpg", 280, 120, false, false));
    fourthRow.push_back(new GameTile("wall.jpg", 320, 120, false, false));
    fourthRow.push_back(new GameTile("ground.jpg", 360, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 400, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 440, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 480, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 520, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 560, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 600, 120, true, false));
    fourthRow.push_back(new GameTile("wall.jpg", 640, 120, false, false));
    fourthRow.push_back(new GameTile("wall.jpg", 680, 120, false, false));
    fourthRow.push_back(new GameTile("ground.jpg", 720, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 760, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 800, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 840, 120, true, false));
    fourthRow.push_back(new GameTile("wall.jpg", 880, 120, false, false));
    fourthRow.push_back(new GameTile("ground.jpg", 920, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 960, 120, true, false));
    fourthRow.push_back(new GameTile("ground.jpg", 1000, 120, true, false));
    fourthRow.push_back(new GameTile("wall.jpg", 1040, 120, false, false));
    tiles.push_back(fourthRow);

    std::vector<GameTile*> fifthRow;
    fifthRow.push_back(new GameTile("wall.jpg", 0, 160, false, false));
    fifthRow.push_back(new GameTile("ground.jpg", 40, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 80, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 120, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 160, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 200, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 240, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 280, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 320, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 360, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 400, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 440, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 480, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 520, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 560, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 600, 160, true, false));
    fifthRow.push_back(new GameTile("wall.jpg", 640, 160, false, false));
    fifthRow.push_back(new GameTile("wall.jpg", 680, 160, false, false));
    fifthRow.push_back(new GameTile("ground.jpg", 720, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 760, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 800, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 840, 160, true, false));
    fifthRow.push_back(new GameTile("wall.jpg", 880, 160, false, false));
    fifthRow.push_back(new GameTile("ground.jpg", 920, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 960, 160, true, false));
    fifthRow.push_back(new GameTile("ground.jpg", 1000, 160, true, false));
    fifthRow.push_back(new GameTile("wall.jpg", 1040, 160, false, false));
    tiles.push_back(fifthRow);

    std::vector<GameTile*> sixthRow;
    sixthRow.push_back(new GameTile("wall.jpg", 0, 200, false, false));
    sixthRow.push_back(new GameTile("ground.jpg", 40, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 80, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 120, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 160, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 200, 200, true, false));
    sixthRow.push_back(new GameTile("wall.jpg", 240, 200, false, false));
    sixthRow.push_back(new GameTile("ground.jpg", 280, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 320, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 360, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 400, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 440, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 480, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 520, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 560, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 600, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 640, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 680, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 720, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 760, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 800, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 840, 200, true, false));
    sixthRow.push_back(new GameTile("wall.jpg", 880, 200, false, false));
    sixthRow.push_back(new GameTile("ground.jpg", 920, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 960, 200, true, false));
    sixthRow.push_back(new GameTile("ground.jpg", 1000, 200, true, false));
    sixthRow.push_back(new GameTile("wall.jpg", 1040, 200, false, false));
    tiles.push_back(sixthRow);

    std::vector<GameTile*> seventhRow;
    seventhRow.push_back(new GameTile("wall.jpg", 0, 240, false, false));
    seventhRow.push_back(new GameTile("ground.jpg", 40, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 80, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 120, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 160, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 200, 240, true, false));
    seventhRow.push_back(new GameTile("wall.jpg", 240, 240, false, false));
    seventhRow.push_back(new GameTile("ground.jpg", 280, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 320, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 360, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 400, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 440, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 480, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 520, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 560, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 600, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 640, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 680, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 720, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 760, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 800, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 840, 240, true, false));
    seventhRow.push_back(new GameTile("wall.jpg", 880, 240, false, false));
    seventhRow.push_back(new GameTile("ground.jpg", 920, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 960, 240, true, false));
    seventhRow.push_back(new GameTile("ground.jpg", 1000, 240, true, false));
    seventhRow.push_back(new GameTile("wall.jpg", 1040, 240, false, false));
    tiles.push_back(seventhRow);

    std::vector<GameTile*> eigthRow;
    eigthRow.push_back(new GameTile("wall.jpg", 0, 280, false, false));
    eigthRow.push_back(new GameTile("ground.jpg", 40, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 80, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 120, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 160, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 200, 280, true, false));
    eigthRow.push_back(new GameTile("wall.jpg", 240, 280, false, false));
    eigthRow.push_back(new GameTile("ground.jpg", 280, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 320, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 360, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 400, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 440, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 480, 280, true, false));
    eigthRow.push_back(new GameTile("supply.png", 520, 280, true, false));//這裡補血
    eigthRow.push_back(new GameTile("ground.jpg", 560, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 600, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 640, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 680, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 720, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 760, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 800, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 840, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 880, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 920, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 960, 280, true, false));
    eigthRow.push_back(new GameTile("ground.jpg", 1000, 280, true, false));
    eigthRow.push_back(new GameTile("wall.jpg", 1040, 280, false, false));
    tiles.push_back(eigthRow);

    std::vector<GameTile*> ninethRow;
    ninethRow.push_back(new GameTile("wall.jpg", 0, 320, false, false));
    ninethRow.push_back(new GameTile("ground.jpg", 40, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 80, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 120, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 160, 320, true, false));
    ninethRow.push_back(new GameTile("wall.jpg", 200, 320, false, false));
    ninethRow.push_back(new GameTile("ground.jpg", 240, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 280, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 320, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 360, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 400, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 440, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 480, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 520, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 560, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 600, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 640, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 680, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 720, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 760, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 800, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 840, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 880, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 920, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 960, 320, true, false));
    ninethRow.push_back(new GameTile("ground.jpg", 1000, 320, true, false));
    ninethRow.push_back(new GameTile("wall.jpg", 1040, 320, false, false));
    tiles.push_back(ninethRow);

    std::vector<GameTile*> tenthRow;
    tenthRow.push_back(new GameTile("wall.jpg", 0, 360, false, false));
    tenthRow.push_back(new GameTile("ground.jpg", 40, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 80, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 120, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 160, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 200, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 240, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 280, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 320, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 360, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 400, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 440, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 480, 360, true, false));
    tenthRow.push_back(new GameTile("wall.jpg", 520, 360, false, false));
    tenthRow.push_back(new GameTile("wall.jpg", 560, 360, false, false));
    tenthRow.push_back(new GameTile("ground.jpg", 600, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 640, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 680, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 720, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 760, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 800, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 840, 360, true, false));
    tenthRow.push_back(new GameTile("ground.jpg", 880, 360, true, false));
    tenthRow.push_back(new GameTile("wall.jpg", 920, 360, false, false));
    tenthRow.push_back(new GameTile("wall.jpg", 960, 360, false, false));
    tenthRow.push_back(new GameTile("ground.jpg", 1000, 360, true, false));
    tenthRow.push_back(new GameTile("wall.jpg", 1040, 360, false, false));
    tiles.push_back(tenthRow);

    std::vector<GameTile*> eleventhRow;
    eleventhRow.push_back(new GameTile("wall.jpg", 0, 400, false, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 40, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 80, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 120, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 160, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 200, 400, true, false));
    eleventhRow.push_back(new GameTile("wall.jpg", 240, 400, false, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 280, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 320, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 360, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 400, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 440, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 480, 400, true, false));
    eleventhRow.push_back(new GameTile("wall.jpg", 520, 400, false, false));
    eleventhRow.push_back(new GameTile("wall.jpg", 560, 400, false, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 600, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 640, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 680, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 720, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 760, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 800, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 840, 400, true, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 880, 400, true, false));
    eleventhRow.push_back(new GameTile("wall.jpg", 920, 400, false, false));
    eleventhRow.push_back(new GameTile("wall.jpg", 960, 400, false, false));
    eleventhRow.push_back(new GameTile("ground.jpg", 1000, 400, true, false));
    eleventhRow.push_back(new GameTile("wall.jpg", 1040, 400, false, false));
    tiles.push_back(eleventhRow);

    std::vector<GameTile*> twelvethRow;
    twelvethRow.push_back(new GameTile("wall.jpg", 0, 440, false, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 40, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 80, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 120, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 160, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 200, 440, true, false));
    twelvethRow.push_back(new GameTile("wall.jpg", 240, 440, false, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 280, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 320, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 360, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 400, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 440, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 480, 440, true, false));
    twelvethRow.push_back(new GameTile("wall.jpg", 520, 440, false, false));
    twelvethRow.push_back(new GameTile("wall.jpg", 560, 440, false, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 600, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 640, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 680, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 720, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 760, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 800, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 840, 440, true, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 880, 440, true, false));
    twelvethRow.push_back(new GameTile("wall.jpg", 920, 440, false, false));
    twelvethRow.push_back(new GameTile("wall.jpg", 960, 440, false, false));
    twelvethRow.push_back(new GameTile("ground.jpg", 1000, 440, true, false));
    twelvethRow.push_back(new GameTile("wall.jpg", 1040, 440, false, false));
    tiles.push_back(twelvethRow);

    std::vector<GameTile*> thirteenthRow;
    thirteenthRow.push_back(new GameTile("wall.jpg", 0, 480, false, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 40, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 80, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 120, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 160, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 200, 480, true, false));
    thirteenthRow.push_back(new GameTile("wall.jpg", 240, 480, false, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 280, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 320, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 360, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 400, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 440, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 480, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 520, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 560, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 600, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 640, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 680, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 720, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 760, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 800, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 840, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 880, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 920, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 960, 480, true, false));
    thirteenthRow.push_back(new GameTile("ground.jpg", 1000, 480, true, false));
    thirteenthRow.push_back(new GameTile("wall.jpg", 1040, 480, false, false));
    tiles.push_back(thirteenthRow);

    std::vector<GameTile*> fourteenthRow;
    fourteenthRow.push_back(new GameTile("wall.jpg", 0, 520, false, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 40, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 80, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 120, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 160, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 200, 520, true, false));
    fourteenthRow.push_back(new GameTile("wall.jpg", 240, 520, false, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 280, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 320, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 360, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 400, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 440, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 480, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 520, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 560, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 600, 520, true, false)); 
    fourteenthRow.push_back(new GameTile("ground.jpg", 640, 520, true, false));
    fourteenthRow.push_back(new GameTile("wall.jpg", 680, 520, false, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 720, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 760, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 800, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 840, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 880, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 920, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 960, 520, true, false));
    fourteenthRow.push_back(new GameTile("ground.jpg", 1000, 520, true, false));
    fourteenthRow.push_back(new GameTile("wall.jpg", 1040, 520, false, false));
    tiles.push_back(fourteenthRow);

    std::vector<GameTile*> fifteenthRow;
    fifteenthRow.push_back(new GameTile("wall.jpg", 0, 560, false, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 40, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 80, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 120, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 160, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 200, 560, true, false));
    fifteenthRow.push_back(new GameTile("wall.jpg", 240, 560, false, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 280, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 320, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 360, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 400, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 440, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 480, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 520, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 560, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 600, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 640, 560, true, false));
    fifteenthRow.push_back(new GameTile("wall.jpg", 680, 560, false, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 720, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 760, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 800, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 840, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 880, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 920, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 960, 560, true, false));
    fifteenthRow.push_back(new GameTile("ground.jpg", 1000, 560, true, false));
    fifteenthRow.push_back(new GameTile("wall.jpg", 1040, 560, false, false));
    tiles.push_back(fifteenthRow);

    std::vector<GameTile*> sixteenthRow;
    sixteenthRow.push_back(new GameTile("wall.jpg", 0, 600, false, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 40, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 80, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 120, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 160, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 200, 600, true, false));
    sixteenthRow.push_back(new GameTile("wall.jpg", 240, 600, false, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 280, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 320, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 360, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 400, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 440, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 480, 600, true, false));
    sixteenthRow.push_back(new GameTile("wall.jpg", 520, 600, false, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 560, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 600, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 640, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 680, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 720, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 760, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 800, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 840, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 880, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 920, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 960, 600, true, false));
    sixteenthRow.push_back(new GameTile("ground.jpg", 1000, 600, true, false));
    sixteenthRow.push_back(new GameTile("wall.jpg", 1040, 600, false, false));
    tiles.push_back(sixteenthRow);

    std::vector<GameTile*> seventeenthRow;
    seventeenthRow.push_back(new GameTile("wall.jpg", 0, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 40, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 80, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 120, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 160, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 200, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 240, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 280, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 320, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 360, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 400, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 440, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 480, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 520, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 560, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 600, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 640, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 680, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 720, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 760, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 800, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 840, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 880, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 920, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 960, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 1000, 640, false, false));
    seventeenthRow.push_back(new GameTile("wall.jpg", 1040, 640, false, false));
    tiles.push_back(seventeenthRow);


}