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

	sf::Texture t0, t1, t2, t3, t4, t5, t6;
	t0.loadFromFile("images/Turret.png");
	t1.loadFromFile("images/Turret.png");
	t2.loadFromFile("images/map.png");
	t3.loadFromFile("images/manloloyo.png");
	t4.loadFromFile("images/title.jpg");
	t5.loadFromFile("images/banner.png");
	t6.loadFromFile("images/tep.png");

	sf::Sprite sTurret(t1), sTurretBackup(t0), sBackground(t2), sTitle(t4), sBanner(t5);
	sTurret.setPosition(1650, 250);
	sTurretBackup.setPosition(1650, 250);
	sBanner.setPosition(700,500);

	animation sHead(t3, 0, 0, MAX_X/4, MAX_Y/4, 10000, 0.00001);
	animation sBossHead(t6, 0, 0, MAX_X/4, MAX_Y/4, 10000, 0.00001);
	animation sTurretPlaced(t1, 0, 0, MAX_X/4, MAX_Y/4, 10000, 0.00001);

	std::list<entity*> entities;
	bool gameStart=false;
	bool gamePause=true;
	bool isMove=false;
	float dx=0, dy=0;
	int count = 0;
	int numHeads = 0;
	int waveMode = 0;
	int liveCheck = 0;

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
					turret *t = new turret();
					t->settings(sTurretPlaced, sTurret.getPosition().x + 240, sTurret.getPosition().y + 135, 100);
					entities.push_back(t);
					sTurret.setPosition(1650, 250);
			}
			if (isMove) sTurret.setPosition(pos.x-dx, pos.y-dy);
		}
		// draw loading screen
		if(!gameStart){
			window.clear();
			window.draw(sTitle);
			window.display();
		}
		// actual game
		if(gameStart){
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
				}
				else i++;
			}
			// draw
			window.clear();
			window.draw(sBackground);
			window.draw(sTurret);
			window.draw(sTurretBackup);
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
			}
		}
	}
	return 0;
}
