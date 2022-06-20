
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <iostream>
#include <cstring>
#include <SFML\Audio.hpp>
#include "Header.h"
#include "map.h"
#define MAX_NUMBER_OF_ITEMS 3
#define MAX_NUMBER_OF_ROLES 4
using namespace sf;
using namespace std;
const int wide = 1280;
const int length = 720;
int hit1 = 0;
int hit2 = 0;
bool light1 = false, light2 = false;
int menuselection = 0; // which button is pressed in Menu. Play = 1; Options = 2; Exit = -1; value = 0  when users in the Menu interface.
int player1selection = 0;
int player2selection = 0;

//---------------------------------------------------------------------------------------------------------------------------------
/*
class Animation
{
   public:
   float Frame, speed;
   Sprite sprite;
   std::vector<IntRect> frames;

   Animation(){}

   Animation (Texture &t, int x, int y, int w, int h, int count, float Speed)
   {
	 Frame = 0;
	 speed = Speed;

	 for (int i=0;i<count;i++)
	  frames.push_back( IntRect(x+i*w, y, w, h)  );//¦Û°Ê³B²z¤¸¯À¤j¤p

	 sprite.setTexture(t);
	 sprite.setOrigin(w/2,h/2);
	 sprite.setTextureRect(frames[0]);
   }


   void update()
   {
	 Frame += speed;
	 int n = frames.size();
	 if (Frame >= n) Frame -= n;
	 if (n>0) sprite.setTextureRect( frames[int(Frame)] );
   }

   bool isEnd()
   {
	 return Frame+speed>=frames.size();
   }

};

class Entity //¹k¥Û¸ò¤l¼u³£·|¥Î¨ì³o­Ó//
{
   public:
   float x,y,dx,dy,R,angle;
   bool life; //¹k¥Û¸ò¤l¼uªº¥Í©R³£¬O1//·í¥´¨ìªF¦è´N·|®ø¥¢//¥i¯à¥i¥H³]©w¥´¨ìÀð¾À¤l
   //¼u¥Í©RÂk¹s¡A³o¼ËÀ³¸Ó¯à¸Ñ¨MÆZ¦h°ÝÃDªº
   std::string name;
   Animation anim;

   Entity()
   {
	 life=1;
   }

   void settings(Animation &a,int X,int Y,float Angle=0,int radius=1)
   {
	 anim = a;
	 x=X; y=Y;
	 angle = Angle;
	 R = radius;
   }

   virtual void update(){};

   void draw(RenderWindow &app)//¤l¼u¸ò¹k¥Ûªº¹Ï§Î«Øºc//
   {
	 anim.sprite.setPosition(x,y);
	 anim.sprite.setRotation(angle+90);
	 app.draw(anim.sprite);

	 CircleShape circle(R);
	 circle.setFillColor(Color(255,0,0,170));
	 circle.setPosition(x,y);
	 circle.setOrigin(R,R);
	 //app.draw(circle);
   }

   virtual ~Entity(){};
};
*/

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Font titleFont;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	//sf::Text title;
};

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Freedom-10eM.ttf"))
	{
		std::cout << "font error!";
	}
	/*
	if (!titleFont.loadFromFile("Yacimiento ExtraBold Ex.ttf"))
	{
		std::cout << "title font error!";
	}

	title.setFont(titleFont);
	title.setColor(sf::Color(170,170,170));
	//title.setOutlineThickness(8);
	//title.setOutlineColor(sf::Color::Black);
	title.setString("WORLD\nOF\nTANKS ");
	title.setCharacterSize(100);
	title.setPosition(sf::Vector2f(width / 10, height / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 100));
	*/

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setCharacterSize(100);
	menu[0].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 1 + 300));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Help");
	menu[1].setCharacterSize(100);
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.5 + 300));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(100);
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_NUMBER_OF_ITEMS + 1) * 2 + 300));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	//window.draw(title);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}



//---------------------------------------------------------------------------------------------------------------------------------


class Rolemenu
{
public:
	Rolemenu(float width, float height);
	~Rolemenu();

	void draw(sf::RenderWindow& window);
	void Player1MoveUp();
	void Player1MoveDown();
	void Player2MoveUp();
	void Player2MoveDown();
	int GetPressedItem1() { return selectedItemIndex1; }
	int GetPressedItem2() { return selectedItemIndex2; }


private:
	int selectedItemIndex1;
	int selectedItemIndex2;
	sf::Texture title1;
	sf::Sprite stitle1;
	sf::Texture title2;
	sf::Sprite stitle2;
	sf::Texture role1[MAX_NUMBER_OF_ROLES];
	sf::Sprite srole1[MAX_NUMBER_OF_ROLES];
	sf::Texture role2[MAX_NUMBER_OF_ROLES];
	sf::Sprite srole2[MAX_NUMBER_OF_ROLES];
	sf::Texture bkg; // background
	sf::Sprite sbkg;
	//sf::Text rolemenu[MAX_NUMBER_OF_ROLES];
	//sf::Text title;
};

Rolemenu::Rolemenu(float width, float height)
{
	if (!bkg.loadFromFile("tank.jpg", sf::IntRect(0, 0, 750, 1001)) ||
		!role1[0].loadFromFile("1.png") ||
		!role1[1].loadFromFile("1.png") ||
		!role1[2].loadFromFile("1.png") ||
		!role1[3].loadFromFile("1.png") ||
		!role2[0].loadFromFile("1.png") ||
		!role2[1].loadFromFile("1.png") ||
		!role2[2].loadFromFile("1.png") ||
		!role2[3].loadFromFile("1.png") ||
		!title1.loadFromFile("player1.png") ||
		!title2.loadFromFile("player2.png")) {
		std::cout << "file error!";
	}
	/*
	sbackground.setTexture(background);
	stitle.setTexture(title);
	stitle.setScale(0.73,0.73);
	//Set a position for a character.
	stitle.setPosition( 200 , 500 );
	//Set origin position of character so that after our character won't drift when we make it turn right or left.
	stitle.setOrigin( stitle.getLocalBounds().height / 2 , stitle.getLocalBounds().width / 2 );
	*/
	sbkg.setTexture(bkg);
	stitle1.setTexture(title1);
	stitle2.setTexture(title2);
	for (int i = 0; i < MAX_NUMBER_OF_ROLES; i++) {
		srole1[i].setTexture(role1[i]);
		srole2[i].setTexture(role2[i]);
	}
	stitle1.setPosition(sf::Vector2f(width / 8, height / (MAX_NUMBER_OF_ROLES + 1) * 1 - 100));
	stitle2.setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ROLES + 1) * 1 - 100));
	stitle1.setScale(0.3, 0.3);
	stitle2.setScale(0.3, 0.3);
	srole1[0].setPosition(sf::Vector2f(width / 8, height / (MAX_NUMBER_OF_ROLES + 1) * 1 - 50));
	srole1[1].setPosition(sf::Vector2f(width / 8, height / (MAX_NUMBER_OF_ROLES + 1) * 1.8 - 50));
	srole1[2].setPosition(sf::Vector2f(width / 8, height / (MAX_NUMBER_OF_ROLES + 1) * 2.6 - 50));
	srole1[3].setPosition(sf::Vector2f(width / 8, height / (MAX_NUMBER_OF_ROLES + 1) * 3.4 - 50));
	srole2[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ROLES + 1) * 1 - 50));
	srole2[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ROLES + 1) * 1.8 - 50));
	srole2[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ROLES + 1) * 2.6 - 50));
	srole2[3].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ROLES + 1) * 3.4 - 50));

	selectedItemIndex1 = 0;
	selectedItemIndex2 = 0;
	srole1[selectedItemIndex1].setColor(sf::Color::Red);
	srole2[selectedItemIndex2].setColor(sf::Color::Red);
}


Rolemenu::~Rolemenu()
{
}

void Rolemenu::draw(sf::RenderWindow& window)
{
	window.draw(sbkg);
	window.draw(stitle1);
	window.draw(stitle2);
	for (int i = 0; i < MAX_NUMBER_OF_ROLES; i++)
	{
		window.draw(srole1[i]);
		window.draw(srole2[i]);
	}
}

void Rolemenu::Player1MoveUp()
{
	if (selectedItemIndex1 - 1 >= 0)
	{
		srole1[selectedItemIndex1].setColor(sf::Color::White);
		selectedItemIndex1--;
		srole1[selectedItemIndex1].setColor(sf::Color::Red);
	}
}

void Rolemenu::Player1MoveDown()
{
	if (selectedItemIndex1 + 1 < MAX_NUMBER_OF_ROLES)
	{
		srole1[selectedItemIndex1].setColor(sf::Color::White);
		selectedItemIndex1++;
		srole1[selectedItemIndex1].setColor(sf::Color::Red);
	}
}

void Rolemenu::Player2MoveUp()
{
	if (selectedItemIndex2 - 1 >= 0)
	{
		srole2[selectedItemIndex2].setColor(sf::Color::White);
		selectedItemIndex2--;
		srole2[selectedItemIndex2].setColor(sf::Color::Red);
	}
}

void Rolemenu::Player2MoveDown()
{
	if (selectedItemIndex2 + 1 < MAX_NUMBER_OF_ROLES)
	{
		srole2[selectedItemIndex2].setColor(sf::Color::White);
		selectedItemIndex2++;
		srole2[selectedItemIndex2].setColor(sf::Color::Red);
	}
}



//---------------------------------------------------------------------------------------------------------------------------------
void menuGo() {
	//sf::RenderWindow window(sf::VideoMode(750,1001,32), "MENU");
	sf::Texture background, title;
	//Make sure that the image we'd like to use is in the dir.
	if (!background.loadFromFile("tank.jpg", sf::IntRect(0, 0, 750, 1001)) ||
		!title.loadFromFile("pngwing.com.png")) {
		std::cout << "file error!";
	}
	sf::Sprite sbackground, stitle;
	//choose a image as a background.
	sbackground.setTexture(background);
	stitle.setTexture(title);
	stitle.setScale(0.73, 0.73);
	//Set a position for a character.
	stitle.setPosition(200, 500);
	//Set origin position of character so that after our character won't drift when we make it turn right or left.
	stitle.setOrigin(stitle.getLocalBounds().height / 2, stitle.getLocalBounds().width / 2);



	sf::RenderWindow window(sf::VideoMode(750, 1001, 32), "MENU");

	int lateralMVMT = 0;
	int verticalMVMT = 0;
	int lateralMVMT2 = 0;
	int verticalMVMT2 = 0;
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						window.close();
						menuselection = 1;
						break;
					case 1:
						window.close();
						menuselection = 2;
						break;
					case 2:
						window.close();
						menuselection = -1;
						break;
					}

					break;
				}

				break;
				window.clear();
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();

		window.draw(sbackground);
		window.draw(stitle);
		menu.draw(window);
		window.display();
	}
}

void helpGo() {
	//sf::RenderWindow window(sf::VideoMode(750,1001,32), "MENU");
	sf::Texture background, help;
	//Make sure that the image we'd like to use is in the dir.
	if (!background.loadFromFile("tank.jpg", sf::IntRect(0, 0, 750, 1001)) ||
		!help.loadFromFile("help.png")) {
		std::cout << "file error!";
	}
	sf::Sprite sbackground, shelp;
	//choose a image as a background.
	sbackground.setTexture(background);
	shelp.setTexture(help);
	//help.setScale(0.73,0.73);
	//Set a position for a character.
	shelp.setPosition(50, 50);
	//Set origin position of character so that after our character won't drift when we make it turn right or left.
	//stitle.setOrigin( stitle.getLocalBounds().height / 2 , stitle.getLocalBounds().width / 2 );
	sf::RenderWindow window(sf::VideoMode(750, 1001, 32), "HELP");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					window.close();
					menuGo();
					break;

				case sf::Keyboard::Return:
					window.close();
					menuGo();
					break;
				}

				break;
				window.clear();
			case sf::Event::Closed:
				window.close();
				break;

			}
		}

		window.clear();

		window.draw(sbackground);
		window.draw(shelp);
		window.display();
	}
}




void rolemenuGo() {
	sf::RenderWindow window(sf::VideoMode(750, 1001, 32), "ROLEMENU");

	Rolemenu rolemenu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					rolemenu.Player2MoveUp();
					break;

				case sf::Keyboard::Down:
					rolemenu.Player2MoveDown();
					break;

				case sf::Keyboard::W:
					rolemenu.Player1MoveUp();
					break;

				case sf::Keyboard::S:
					rolemenu.Player1MoveDown();
					break;

				case sf::Keyboard::Space:
					switch (rolemenu.GetPressedItem1())
					{
					case 0:
						window.close();
						player1selection = 1;
						break;
					case 1:
						window.close();
						player1selection = 2;
						break;
					case 2:
						window.close();
						player1selection = 3;
						break;
					case 3:
						window.close();
						player1selection = 4;
						break;
					}

					break;
				case sf::Keyboard::Return:
					switch (rolemenu.GetPressedItem2())
					{
					case 0:
						window.close();
						player2selection = 1;
						break;
					case 1:
						window.close();
						player2selection = 2;
						break;
					case 2:
						window.close();
						player2selection = 3;
						break;
					case 3:
						window.close();
						player2selection = 4;
						break;
					}

					break;
				}

				break;
				window.clear();
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();

		//window.draw(sbackground);
		//window.draw(stitle);
		rolemenu.draw(window);
		window.display();
	}
}
//-------------------------------------------------------------------------------------------------------------	



//This function is for control the character.
void keyBoardControl(sf::Sprite& slegend, sf::Sprite& slegend2, sf::RenderWindow& window) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//Make sprite move with one pixel, positive and negative stands for two different direction.
		slegend.move(-1, 0);
		//At the same time, make the sprite face to the right way. Same as below.
		slegend.setRotation(270.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		slegend.move(1, 0);
		slegend.setRotation(90.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		slegend.move(0, -1);
		slegend.setRotation(360.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		slegend.move(0, 1);
		slegend.setRotation(180.0f);
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		lateralMVMT2 = -1;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		lateralMVMT2 = 1;
	} else {
		lateralMVMT2 = 0;
	} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		verticalMVMT2 = -1;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		verticalMVMT2 = 1;
	} else {
		verticalMVMT2 = 0;
	}*/

	//Draw the image we have converted to sprite.
	window.draw(slegend);
	window.draw(slegend2);
	//Make sprite move after the keyboard event.
	window.display();
}
/*
void play(){
			//Texture and Sprite SOP
  sf::Texture background, legend, legend2;
  //Make sure that the image we'd like to use is in the dir.
   if(
	 !background.loadFromFile("2.png", sf::IntRect(0, 0, 710,599)) ||
	 !legend.loadFromFile("1.png") || !legend2.loadFromFile("1.png")
  ) {
	 std::cout << "file error!";
  }
   //Make the sprite for all of the image.
  sf::Sprite sbackground, slegend, slegend2;
   //choose a image as a background.
  sbackground.setTexture(background);
   //Two characters has converted to sprite.
   slegend.setTexture(legend);
   slegend2.setTexture(legend2);
   //Set a position for a character.
   slegend.setPosition( 400 , 320 );
   //Set origin position of character so that after our character won't drift when we make it turn right or left.
   slegend.setOrigin( slegend.getLocalBounds().height / 2 , slegend.getLocalBounds().width / 2 );

   //Create a  Window with a specific scale. And the scale has to follow the size of background image.
   sf::RenderWindow window(sf::VideoMode(710, 599,32), "abc");

   //Keep running this program as long as we haven't shut down the window.
   while (window.isOpen())
   {
	   //Check every event like keyboard input or sth start from the loop.
	   sf::Event event;

	   //Detect the window close or not. Without this command the process will breakdown.
	   while (window.pollEvent(event))
	   {
		   if (event.type == sf::Event::Closed)
			   window.close();
	   }

	   //Draw the background before we draw the character.
	   window.draw(sbackground);
	   //call the function which will control the movement of character.
	   keyBoardControl(slegend, slegend2, window);
   }

}
*/







void play()
{
	//è¦??»ºç«?
	sf::RenderWindow window(sf::VideoMode(wide, length), "test");

	//?³æ?å»ºç?
	sf::Music music;
	float volume = 50;
	music.openFromFile("blackpink.ogg");  //å¾?æ¡?????å¼?å°?ç¨????®é?ä¸??«å?music.ogg??æ¡?
	music.setVolume(volume);  //å°?¨­å®volumeï¼?????0
	music.setLoop(true);  //ä½¿music?æ¨ä»¥é?è¤?¾ï????¯è¨­?ºfalse
	music.play();



	player player1;
	defensivePlayer player2;


	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		keyboardInputOne(player1, gameWorld);
		keyboardInputTwo(player2, gameWorld);


		//?¤å?å­??¯å???°è??²ï???è©±è????
		collideProcess(player1, player2, hit1);
		collideProcess(player2, player1, hit2);

		//if (collide == true)
		//{
		 //explotionAnimation(window, player2);
		 //for (auto e : entities)
		  //if (e->anim.isEnd()) e->life = 0;
		 //for (auto i = entities.begin(); i != entities.end();)
		 //{
		  //Entity* e = *i;

		  //e->update();
		  //e->anim.update();

		  //if (e->life == false) { i = entities.erase(i); delete e; }
		  //else i++;
		 //}
		 //for (auto i : entities) i->draw(window);
			  //window.display();
		 //collide = false;
		//}

		//æª¢æ?¯å?ººè¡€?0å¦??©±å°±é??²ç???
		if (player1.liveSpan <= 0 or player2.liveSpan <= 0)
		{
			//void ByByPage();

			window.close();
		}

		//è£?æ©
		supplycheck(player1, player2, light1, light2);

		///draw////









		for (auto i = player1.entities.begin(); i != player1.entities.end();)
		{
			Entity* e = *i;

			e->update();
			e->anim.update();

			//cout << e->x << " " << e->y<<'\n';
			if (e->life == false) { i = player1.entities.erase(i); delete e; }

			else i++;
		}

		for (auto i = player2.entities.begin(); i != player2.entities.end();)
		{
			Entity* e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = player1.entities.erase(i); delete e; }
			else i++;
		}


		sf::Texture texture;
		sf::Sprite sprite;
		sprite.setTexture(texture);

		window.clear();


		//??°å½¢
		for (int i = 0; i < gameWorld.gridLength; i++) {
			for (int j = 0; j < gameWorld.gridWidth; j++) {
				window.draw(gameWorld.tiles[i][j]->sprite);
			}
		}

		displayliveSpan(window, player1, player2);

		//?«åè§
		window.draw(player1.object);
		window.draw(player2.object);

		//?«åå­?
		for (auto i : player1.entities) i->draw(window); //?°å???
		for (auto j : player2.entities) j->draw(window);



		window.display(); //å±¤º?€?°ç?çµ?



	}

}



int main()
{
	menuGo();
	if (menuselection == 1) {
		rolemenuGo();
	}
	if (menuselection == 2) {
		helpGo();
		//endGo();
	}

}


