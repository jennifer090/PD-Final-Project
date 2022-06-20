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




//�a����ɱ���
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
			frames.push_back(sf::IntRect(x + i * w, y, w, h));//�۰ʳB�z�����j�p 

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

class Entity //�k�۸�l�u���|�Ψ�o��// 
{
public:
	float x, y, dx, dy, R, angle;
	bool life; //�k�۸�l�u���ͩR���O1//����F��N�|����//�i��i�H�]�w��������l
	//�u�ͩR�k�s�A�o�����ӯ�ѨM�Z�h���D�� 
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

	void draw(sf::RenderWindow& app)//�l�u��k�۪��ϧΫغc// 
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


class bullet : public Entity//�l�u��class *�o�̻ݭn���!!// 
{
public:
	bullet()
	{
		name = "bullet";
	}

	void  update()
	{
		// �U���O��V��o�g�p��e�i// 
		dx = cos(angle * DEGTORAD) * 4; //�o�̻ݭn�վ�A�{�b�O360�סA�ݭn�令90�פ@�Ӥ�V// 
		dy = sin(angle * DEGTORAD) * 4; //���ӥi�H�򥻨ӤH����V���{���令�P�@�اY�i// 
		x += dx;
		y += dy;
		
		if (x > W || x<0 || y>H || y < 0) life = 0; //�l�u��F��ɪ��ɭԥͩR�k�s�A����// 
		if (check(gameWorld, x, y) == false) //�l�u�I�������
			life = 0;

	}

};


//�Хߨ��⪺���///

class player
{
	//����//��q//��m//
protected:
	string name; //�W�r
	sf::Texture texture; //����
	
	float speed;//�t��
	bool live;
	
	//�s�W
	sf::Texture t5;//�l�u����]���J 
	Animation* sBullet;//�l�u�ʵe/
	//Animation* sExplosion; //�z���ʵe

public:
	sf::Sprite object;
	player();
	//�Ы�player�o�Ӹ}��
	void move(int i); //���ʨ����m
	bool getLive(int liveSpan);//�P�_����O�_�٬��̡A�p�G���F�|�^��False
	int getX();
	int getY();
	float getSpeed();
	int power;//�����O
	int liveSpan; //��q�ݭn�Q�D���]���]��global
	
	int myliveSpan;  //���⪺��q(����)
	//�s�W
	list<Entity*> entities;
	void attack(); //�\��


	


};

list<Entity*> entities;
//�z���ʵe

void explotionAnimation(sf::RenderWindow& window, player player)
{
	sf::Texture t3;//�l�u����]���J 
	t3.loadFromFile("type_C.png");
	Animation sExplosion(t3, 0, 0, 200, 200, 48, 0.5);
	Entity* e = new Entity();
	e->settings(sExplosion,player.getX(), player.getY());
	entities.push_back(e);

	
	    
}







//�����Ϊ��a�A�t��2�֡A�����O10���C
player::player()
{
	name = "fishOverDoor"; //����m�W
	texture.loadFromFile("plane.png"); //��J����
	liveSpan = 100;//��q��100;
	myliveSpan = 100; //��������쥻����q
	sf::Sprite sprite(texture); //�إߤ@�Ӫ���(�o�˯ন�\��J��?)
	object = sprite;
	speed = 2; //�t��
	power = 10; //�����O��5
	live = true; //�s�����A
	object.setPosition(sf::Vector2f(400.f, 260.f)); //�}���l��m
	object.setScale(0.04, 0.04);
	//fire = false;//���}��
	//�s�W�l�u
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
	bullet* b = new bullet();//���ͤl�u// 
	b->settings(*sBullet, pos.x, pos.y, object.getRotation()-90, 10); //��m�i��n���@�U
	entities.push_back(b);
	//fire = true;


}

int player::getX()
{
	sf::Vector2f pos = object.getPosition(); //�w�g��s�X�p��Q�a�ϥd��
	return pos.x;
}
int player::getY()
{
	sf::Vector2f pos = object.getPosition(); //�w�g��s�X�p��Q�a�ϥd��
	return pos.y;
}
float player::getSpeed()
{
	return speed;

}
void player::move(int i) //�Ʀr�N��(1 �� 2 �k 3 �W 4 �U)
{
	sf::Vector2f pos = object.getPosition(); //�w�g��s�X�p��Q�a�ϥd��
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


//���a�@�Ϊ��a�G�����ʤ覡
void keyboardInputOne(player& player1,GameWorld& gameWorld)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{ 
		cout << "��m" << player1.getX() -player1.getSpeed() << " " << player1.getY()<<'\n';
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

////���P���⪺�Ы�////

//���m�����a�A��q������A���t�פ���C�A�����O�����
class defensivePlayer : public player
{
public:

	defensivePlayer();

};

defensivePlayer::defensivePlayer()
{
	name = "�g�˳��n��A+"; //����m�W
	texture.loadFromFile("player1.png"); //��J����
	liveSpan = 200;//��q��100;
	myliveSpan = 200;
	speed = 0.5;
	power = 20; //�����O��30
	sf::Sprite sprite(texture); //�إߤ@�Ӫ���(�o�˯ন�\��J��?)
	object = sprite;
	object.setPosition(sf::Vector2f(300.f, 260.f)); //�}���l��m
	object.setScale(0.04, 0.04);

}


//�P�_�l�u�O�_����H
bool isCollide(Entity* a, player& b)
{
	return (b.getX() - a->x) * (b.getX() - a->x) +
		(b.getY() - a->y) * (b.getY() - a->y) <
		(a->R + 40) * (a->R + 40);
}


//�P�_�������B�z

void collideProcess(player& attack, player& beAttacked, int& hit)
{

	for (auto a : attack.entities)
	{
		if (isCollide(a, beAttacked)) //�ˬd�l�u�O�_��������H��
		{
			a->life = false; //�p�G�����ܤl�u����
			if (hit == 0)
			{
				beAttacked.liveSpan -= attack.power;
				collide = true;
				hit = 1;
			}
			cout << "�ͩR��" << beAttacked.liveSpan;
			break;
		}
		else //�p�G�S�����ܥN���٨S����
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
//�ɦ�վ�
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

	//�إ� title ���a�@����q
	sf::Text title;
	string player1Title = "Player1 LiveSpan";

	title.setString(player1Title);
	title.setFont(font);
	title.setFillColor(sf::Color::Red);
	title.setCharacterSize(20); //��r�j�p
	title.setOrigin((title.getGlobalBounds().width / 2), (title.getGlobalBounds().height / 2));
	title.setPosition(1180, 50);

	//���a�@�쥻����q�β{�b����q��
	sf::Text text;
	string currentlife = to_string(player1.liveSpan)+" / " +to_string(player1.myliveSpan);
	text.setString(currentlife);
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setOrigin((text.getGlobalBounds().width / 2), (text.getGlobalBounds().height / 2));
	text.setPosition(1180, 100);

	//title ���a�G����q
	sf::Text title2;
	
	string player2Title = "Player2 LiveSpan";

	title2.setString(player2Title);
	title2.setFont(font);
	title2.setFillColor(sf::Color::Red);
	title2.setCharacterSize(20); //��r�j�p
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



