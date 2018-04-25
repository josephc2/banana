#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "animation.cpp"
#include "entity.cpp"
#include "head.cpp"

#define MAX_X 1920
#define MAX_Y 1080

int main()
{
	sf::RenderWindow window(sf::VideoMode(MAX_X, MAX_Y), "Banana Defense", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	sf::Texture t1, t2, t3;
	t1.loadFromFile("images/Turret.png");
	t2.loadFromFile("images/map.png");
	t3.loadFromFile("images/manloloyo.png");

	sf::Sprite sTurret(t1), sBackground(t2);
	animation sHead(t3, 0, 0, MAX_X/4, MAX_Y/4, 10000, 0.00001);

	std::list<entity*> entities;
	for(int i=0;i<20;i++)
	{
		head *h = new head();
		h->settings(sHead, 5*i, 650, 100);
		entities.push_back(h);
	}

	bool isMove=false;
	float dx=0, dy=0;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();

			if(event.type == sf::Event::MouseButtonPressed){
				printf("Button was pressed\n");
				if(event.key.code == sf::Mouse::Left)
					if(sTurret.getGlobalBounds().contains(pos.x, pos.y)){
						isMove=true;
						dx=pos.x - sTurret.getPosition().x;
						dy=pos.y - sTurret.getPosition().y;
					}
			}

			if(event.type == sf::Event::MouseButtonReleased){
				printf("Button was released\n");
				if(event.key.code == sf::Mouse::Left)
					isMove=false;
			}
			if (isMove) sTurret.setPosition(pos.x-dx, pos.y-dy);
		}
		for(auto i=entities.begin();i!=entities.end();){
			entity *e = *i;

			e->update();
			e->anim.update();

			if (e->isAlive==false) {i=entities.erase(i); delete e;}
			else i++;
		}
		// draw
		window.clear();
		window.draw(sBackground);
		window.draw(sTurret);
		for(auto i:entities)
			i->draw(window);
		window.display();
	}
	return 0;
}
