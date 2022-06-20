#include <SFML/Window.hpp>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <SFML\Audio.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <list>
#include <string>
#include "map.h"


using namespace std;

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

const int supplyX = 520;
const int supplyY = 280;

bool collide = false;




//地圖邊界條件
GameWorld gameWorld = GameWorld();

bool check(GameWorld gameWorld, int x, int y) {
	int i = 0;
	int j = 0;
	i = x / 40;
	j = y / 40;
	if (gameWorld.tiles[j][i]->isPassable) {
		return true;
	}
	else {
		return false;
	}
}

class Animation
{
public:
	float Frame, speed;
	sf::Sprite sprite;
	vector<sf::IntRect> frames;

	Animation() {}

	Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed)
	{
		Frame = 0;
		speed = Speed;

		for (int i = 0; i < count; i++)
			frames.push_back(sf::IntRect(x + i * w, y, w, h));//自動處理元素大小 

		sprite.setTexture(t);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setTextureRect(frames[0]);
	}


	void update()
	{
		Frame += speed;
		int n = frames.size();
		if (Frame >= n) Frame -= n;
		if (n > 0) sprite.setTextureRect(frames[int(Frame)]);
	}

	bool isEnd()
	{
		return Frame + speed >= frames.size();
	}

};

class Entity //隕石跟子彈都會用到這個// 
{
public:
	float x, y, dx, dy, R, angle;
	bool life; //隕石跟子彈的生命都是1//當打到東西就會消失//可能可以設定打到牆壁子
	//彈生命歸零，這樣應該能解決蠻多問題的 
	std::string name;
	Animation anim;

	Entity()
	{
		life = 1;
	}

	void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1)
	{
		anim = a;
		x = X; y = Y;
		angle = Angle;
		R = radius;
	}

	virtual void update() {};

	void draw(sf::RenderWindow& app)//子彈跟隕石的圖形建構// 
	{
		anim.sprite.setPosition(x, y);
		anim.sprite.setRotation(angle + 90);
		app.draw(anim.sprite);


		sf::CircleShape circle(R);

		circle.setFillColor(sf::Color(255, 0, 0, 170));
		circle.setPosition(x, y);
		circle.setOrigin(R, R);
		app.draw(circle);

	}

	virtual ~Entity() {};
};


class bullet : public Entity//子彈的class *這裡需要更改!!// 
{
public:
	bullet()
	{
		name = "bullet";
	}

	void  update()
	{
		// 下面是方向跟發射如何前進// 
		dx = cos(angle * DEGTORAD) * 4; //這裡需要調整，現在是360度，需要改成90度一個方向// 
		dy = sin(angle * DEGTORAD) * 4; //應該可以跟本來人物轉向的程式改成同一種即可// 
		x += dx;
		y += dy;
		
		if (x > W || x<0 || y>H || y < 0) life = 0; //子彈抵達邊界的時候生命歸零，消失// 
		if (check(gameWorld, x, y) == false) //子彈碰到牆消失
			life = 0;

	}

};


//創立角色的原形///

class player
{
	//長相//血量//位置//
protected:
	string name; //名字
	sf::Texture texture; //材質
	
	float speed;//速度
	bool live;
	
	//新增
	sf::Texture t5;//子彈材質包載入 
	Animation* sBullet;//子彈動畫/
	//Animation* sExplosion; //爆炸動畫

public:
	sf::Sprite object;
	player();
	//創建player這個腳色
	void move(int i); //移動角色位置
	bool getLive(int liveSpan);//判斷角色是否還活者，如果死了會回傳False
	int getX();
	int getY();
	float getSpeed();
	int power;//攻擊力
	int liveSpan; //血量需要被題取因此設為global
	
	int myliveSpan;  //角色的血量(不變)
	//新增
	list<Entity*> entities;
	void attack(); //功擊


	


};

list<Entity*> entities;
//爆炸動畫

void explotionAnimation(sf::RenderWindow& window, player player)
{
	sf::Texture t3;//子彈材質包載入 
	t3.loadFromFile("type_C.png");
	Animation sExplosion(t3, 0, 0, 200, 200, 48, 0.5);
	Entity* e = new Entity();
	e->settings(sExplosion,player.getX(), player.getY());
	entities.push_back(e);

	
	    
}







//輕巧形玩家，速度2快，攻擊力10較低
player::player()
{
	name = "fishOverDoor"; //角色姓名
	texture.loadFromFile("plane.png"); //輸入材質
	liveSpan = 100;//血量為100;
	myliveSpan = 100; //紀錄角色原本的血量
	sf::Sprite sprite(texture); //建立一個物件(這樣能成功輸入嗎?)
	object = sprite;
	speed = 2; //速度
	power = 10; //攻擊力為5
	live = true; //存活狀態
	object.setPosition(sf::Vector2f(400.f, 260.f)); //腳色初始位置
	object.setScale(0.04, 0.04);
	//fire = false;//未開火
	//新增子彈
	t5.loadFromFile("fire_blue.png");
	//t3.loadFromFile("type_A.png");
	sBullet = new Animation(t5, 0, 0, 32, 64, 16, 0.8);
	//sExplosion= new Animation(t3, 0, 0, 256, 256, 48, 0.5);

}

bool player::getLive(int liveSpan)
{
	if (liveSpan <= 0)
		return false;
	return true;

}


void player::attack() 
{
	
	sf::Vector2f pos = object.getPosition();
	bullet* b = new bullet();//產生子彈// 
	b->settings(*sBullet, pos.x, pos.y, object.getRotation()-90, 10); //位置可能要橋一下
	entities.push_back(b);
	//fire = true;


}

int player::getX()
{
	sf::Vector2f pos = object.getPosition(); //已經研究出如何被地圖卡住
	return pos.x;
}
int player::getY()
{
	sf::Vector2f pos = object.getPosition(); //已經研究出如何被地圖卡住
	return pos.y;
}
float player::getSpeed()
{
	return speed;

}
void player::move(int i) //數字代表(1 左 2 右 3 上 4 下)
{
	sf::Vector2f pos = object.getPosition(); //已經研究出如何被地圖卡住
	cout << "x" << pos.x << "  " << "y" << pos.y << '\n';
	object.setOrigin(object.getLocalBounds().height / 2, object.getLocalBounds().width / 2);

	if (i == 1)
	{
		object.move(-speed, 0);
		object.setRotation(270.0f);

	}
	else if (i == 2)
	{
		object.move(speed, 0);
		object.setRotation(90.0f);
	}
	else if (i == 3)
	{
		object.move(0, -speed);
		object.setRotation(360.0f);
	}



	else if (i == 4)
	{

		object.move(0, speed);
		object.setRotation(180.0f);
	}
	else if (i == 5)
		object.move(0, 0);


}


//玩家一及玩家二的移動方式
void keyboardInputOne(player& player1,GameWorld& gameWorld)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{ 
		cout << "位置" << player1.getX() -player1.getSpeed() << " " << player1.getY()<<'\n';
		if (check(gameWorld, player1.getX()-player1.getSpeed(),player1.getY()) )
			player1.move(1);
    }
			
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (check(gameWorld, player1.getX()+player1.getSpeed(), player1.getY()))
			player1.move(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (check(gameWorld, player1.getX(), player1.getY()-player1.getSpeed()))
			player1.move(3);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (check(gameWorld, player1.getX(), player1.getY()+player1.getSpeed()))
			player1.move(4);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player1.attack();
		Sleep(3);
		
	}

		
	


}

void keyboardInputTwo(player& player1, GameWorld& gameWorld)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (check(gameWorld, player1.getX() - player1.getSpeed(), player1.getY()))
		     player1.move(1);
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (check(gameWorld, player1.getX() + player1.getSpeed(), player1.getY()))
		    player1.move(2);
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (check(gameWorld, player1.getX(), player1.getY() - player1.getSpeed()))
		    player1.move(3);
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (check(gameWorld, player1.getX(), player1.getY() + player1.getSpeed()))
		      player1.move(4);
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		player1.attack();
	}
		
}

////不同角色的創建////

//防禦型玩家，血量比較高，但速度比較慢，攻擊力比較高
class defensivePlayer : public player
{
public:

	defensivePlayer();

};

defensivePlayer::defensivePlayer()
{
	name = "經森都要拿A+"; //角色姓名
	texture.loadFromFile("player1.png"); //輸入材質
	liveSpan = 200;//血量為100;
	myliveSpan = 200;
	speed = 0.5;
	power = 20; //攻擊力為30
	sf::Sprite sprite(texture); //建立一個物件(這樣能成功輸入嗎?)
	object = sprite;
	object.setPosition(sf::Vector2f(300.f, 260.f)); //腳色初始位置
	object.setScale(0.04, 0.04);

}


//判斷子彈是否打到人
bool isCollide(Entity* a, player& b)
{
	return (b.getX() - a->x) * (b.getX() - a->x) +
		(b.getY() - a->y) * (b.getY() - a->y) <
		(a->R + 40) * (a->R + 40);
}


//判斷打中的處理

void collideProcess(player& attack, player& beAttacked, int& hit)
{

	for (auto a : attack.entities)
	{
		if (isCollide(a, beAttacked)) //檢查子彈是否有撞擊到人物
		{
			a->life = false; //如果有的話子彈消失
			if (hit == 0)
			{
				beAttacked.liveSpan -= attack.power;
				collide = true;
				hit = 1;
			}
			cout << "生命值" << beAttacked.liveSpan;
			break;
		}
		else //如果沒有的話代表還沒擊中
		{
			hit = 0;
			collide = false;
		}
			
		cout << hit << '\n';
	}

}

bool supplybound(int x, int y, player& player)
{
	if (player.getX() >= x and player.getX() <= x + 30)
	{
		//cout << "good";
		if (player.getY() >= y and player.getY() <= y + 30)
		{
			cout << "good";
			return true;
		}
			
	}
		
	return false;

}
//補血調整
void supplycheck(player& player1, player& player2, bool& light1,bool& light2)
{
	if (light1 == false)
	{
		if (supplybound(supplyX, supplyY, player1))
		{
			cout << "good";
			player1.liveSpan < player1.myliveSpan ? player1.liveSpan += 10 : player1.myliveSpan;
			light1 = true;
		}
	}
	if (light2 == false)
	{
		if (supplybound(supplyX, supplyY, player2))
		{
			cout << "good";
			player2.liveSpan < player2.myliveSpan ? player2.liveSpan += 10 : player2.myliveSpan;
			light2 = true;
		}
	}
		
	
	if (light1 == true )
	{
		if (supplybound(supplyX, supplyY, player1)==false)
			light1 = false;
		
	}
	else if (light2==true)
	    if (supplybound(supplyX, supplyY, player2) == false)
		    light2 = false;
	
	
}




void displayliveSpan(sf::RenderWindow& window, player player1, player player2)
{
	sf::Font font;
	font.loadFromFile("text.ttf");

	//建立 title 玩家一的血量
	sf::Text title;
	string player1Title = "Player1 LiveSpan";

	title.setString(player1Title);
	title.setFont(font);
	title.setFillColor(sf::Color::Red);
	title.setCharacterSize(20); //文字大小
	title.setOrigin((title.getGlobalBounds().width / 2), (title.getGlobalBounds().height / 2));
	title.setPosition(1180, 50);

	//玩家一原本的血量及現在的血量比
	sf::Text text;
	string currentlife = to_string(player1.liveSpan)+" / " +to_string(player1.myliveSpan);
	text.setString(currentlife);
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setOrigin((text.getGlobalBounds().width / 2), (text.getGlobalBounds().height / 2));
	text.setPosition(1180, 100);

	//title 玩家二的血量
	sf::Text title2;
	
	string player2Title = "Player2 LiveSpan";

	title2.setString(player2Title);
	title2.setFont(font);
	title2.setFillColor(sf::Color::Red);
	title2.setCharacterSize(20); //文字大小
	title2.setOrigin((title2.getGlobalBounds().width / 2), (title2.getGlobalBounds().height / 2));
	title2.setPosition(1180, 150);
	
	
	sf::Text text2;
	string currentlife2 = to_string(player2.liveSpan) + " / " + to_string(player2.myliveSpan);
	text2.setString(currentlife2);
	text2.setFont(font);
	text2.setFillColor(sf::Color::Red);
	text2.setOrigin((text2.getGlobalBounds().width / 2), (text2.getGlobalBounds().height / 2));
	text2.setPosition(1180, 200);

	window.draw(title);
	window.draw(text);
	window.draw(title2);
	window.draw(text2);
}



