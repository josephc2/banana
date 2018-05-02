#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "animation.cpp"
#include "entity.cpp"
#include "head.cpp"
#include "turret.cpp"

#define MAX_X 1920
#define MAX_Y 1080

bool isCollide(entity *a,entity *b){
	return (b->x - a->x)*(b->x - a->x)+
		(b->y - a->y)*(b->y - a->y)<
		(a->R + b->R)*(a->R + b->R);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(MAX_X, MAX_Y), "Banana Defense", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	sf::Texture t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
	sf::Font font;
	font.loadFromFile("font/big_noodle_titling.ttf");

	// for bank systems
	sf::Text text("100", font);
	text.setCharacterSize(100);
	text.setColor(sf::Color::White);
	text.setPosition(1700,820);

	// for life system
	sf::Text live("10", font);
	live.setCharacterSize(100);
	live.setColor(sf::Color::White);
	live.setPosition(1350,850);

	t0.loadFromFile("images/Turret.png");
	t1.loadFromFile("images/Turret.png");
	t2.loadFromFile("images/map.png");
	t3.loadFromFile("images/manloloyo.png");
	t4.loadFromFile("images/title.jpg");
	t5.loadFromFile("images/banner.png");
	t6.loadFromFile("images/tep.png");
	t7.loadFromFile("images/banana-hi.png");
	t8.loadFromFile("images/bullet.png");
	t9.loadFromFile("images/bullet.png");

	sf::Sprite sTurret(t1), sTurretBackup(t0), sBackground(t2), sTitle(t4), sBanner(t5), sBanana(t7);
	sTurret.setPosition(1650, 250);
	sTurretBackup.setPosition(1650, 250);
	sBanner.setPosition(525,500);
	sBanana.setPosition(1350,860);


	animation sHead(t3, 0, 0, MAX_X/4, MAX_Y/4, 10000, 0.00001);
	animation sBossHead(t6, 0, 0, MAX_X/4, MAX_Y/4, 10000, 0.00001);
	animation sTurretPlaced(t1, 0, 0, MAX_X/4, MAX_Y/4, 10000, 0.00001);
	animation sBulletshoot(t8, 0, 0, MAX_X/4, MAX_Y/4, 10000, 0.00001);

	std::list<entity*> entities;
	bool gameStart=false;
	bool gamePause=true;
	bool isMove=false;
	bool fire=false;
	float dx=0, dy=0;
	int count = 0;
	int numHeads = 0;
	int waveMode = 0;
	int liveCheck = 0;
	int lifeleft = 10;
	int bank = 500;
	int counter = 0;
	int numBullet = 0;
	int turretPlace = 0;
	int interate = 0;
	//float locX[100], locY[100];
	float locX=0, locY=0;

	// run the program as long as the window is open
	while (window.isOpen()){
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)){
			if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Space){
					if(!gameStart)
						gameStart = true;
					else
						gamePause = false;
				}
			}
			if(event.type == sf::Event::Closed)
				window.close();

			if(event.type == sf::Event::MouseButtonPressed){
				// printf("Button was pressed\n");
				if(event.key.code == sf::Mouse::Left)
					if(sTurret.getGlobalBounds().contains(pos.x, pos.y)){
						isMove=true;
						dx=pos.x - sTurret.getPosition().x;
						dy=pos.y - sTurret.getPosition().y;
					}
			}

			if(event.type == sf::Event::MouseButtonReleased){
				// printf("Button was released\n");
				if(event.key.code == sf::Mouse::Left)
					isMove=false;
				// std::cout << "Turret x position: " << sTurret.getPosition().x << std::endl;
				// std::cout << "Turret y position: " << sTurret.getPosition().y << std::endl;
				if(bank >= 100){
					turret *t = new turret();
					t->settings(sTurretPlaced, sTurret.getPosition().x + 240, sTurret.getPosition().y + 135, 100);
					entities.push_back(t);
					bank-=100;
					sTurret.setPosition(1650, 250);
				}
				//sTurret.setPosition(1650, 250);
			}

			if (isMove){
				sTurret.setPosition(pos.x-dx, pos.y-dy);

						locX=  sTurret.getPosition().x;
						locY =  sTurret.getPosition().y;

					//interate =0;

				std::cout <<"Count" <<std::endl;
			}
		}

		// draw loading screen
		if(!gameStart){
			window.clear();
			window.draw(sTitle);
			window.display();
		}
		// actual game
		if(gameStart){

			if(counter < 100){
				if(fire = true){
					//top bullet
					Bullet *b = new Bullet();
						b->settings(sBulletshoot, locX+ 100, locY - 80, 10);
						entities.push_back(b);
					std::cout << "Placed Turret" <<std::endl;
					//bottom bullet
					BulletUp *b1 = new BulletUp();

						b1->settings(sBulletshoot, locX + 100, locY+ 80, 10);
						entities.push_back(b1);

					std::cout << "Placed" <<std::endl;
					fire = false;
					counter = 0;
				}
				counter++;
			}
			else
				fire = true;


			// wave 0
			if(waveMode == 0 && !gamePause){
				if(numHeads < 5){
					if(count % 75 == 0){
						head *h = new head();
						h->settings(sHead, 5, 650, 100);
						entities.push_back(h);
						numHeads++;
					}
					count++;
				}
			}
			// wave 1
			if(waveMode == 1 && !gamePause){
				if(numHeads < 10){
					if(count % 75 == 0){
						head *h = new head();
						if(numHeads % 6 == 0)
							h->settings(sBossHead, 5, 650, 100);
						else
							h->settings(sHead, 5, 650, 100);
						entities.push_back(h);
						numHeads++;
					}
					count++;
				}
			}
			// wave 2
			if(waveMode == 2 && !gamePause){
				if(numHeads < 20){
					if(count % 75 == 0){
						head *h = new head();
						h->settings(sHead, 5, 650, 100);
						entities.push_back(h);
						numHeads++;
					}
					count++;
				}
			}
			for(auto i=entities.begin();i!=entities.end();){
				entity *e = *i;
				e->update();
				e->anim.update();
				if (e->isAlive==false) {
					i=entities.erase(i);
					delete e;
					lifeleft--;
					// ##############################################
					// remember to remove this for full game
					bank += 100;
					// #############################################
					std::cout << "You have " << lifeleft << "lives left" << std::endl;
				}
				else i++;
			}
			// draw
			window.clear();
			window.draw(sBackground);
			window.draw(sTurret);
			window.draw(sTurretBackup);
			window.draw(sBanana);


			// update money in the bank
			text.setString(std::to_string(bank));
			window.draw(text);

			// update number of lives left
			live.setString(std::to_string(lifeleft));
			window.draw(live);

			if(gamePause)
				window.draw(sBanner);
			for(auto i:entities)
				i->draw(window);
			window.display();

			if(!gamePause){
				// head count
				liveCheck = 0;
				for(auto i:entities){
					if(i->name == "head")
						liveCheck++;
				}
				//std::cout << "Live check " << liveCheck << std::endl;
				if(liveCheck == 0){
					std::cout << "Wave" << waveMode << "cleared" << std::endl;
					liveCheck = 0;
					count = 0;
					numHeads = 0;
					waveMode++;
					gamePause=true;
				}
				if(lifeleft == 0){
					std::cout << "You lose!" << std::endl;
					window.close();
				}
			}
		}
	}
	return 0;
}
