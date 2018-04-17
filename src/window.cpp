#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Banana Defense", sf::Style::Close | sf::Style::Titlebar);

	sf::Texture t1, t2, t3;
	t1.loadFromFile("images/Turret.png");
	t2.loadFromFile("images/map.png");
	t3.loadFromFile("images/manloloyo_head.png");

	sf::Sprite sTurret(t1), sBackground(t2), sHead(t3);

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

			if(event.type == sf::Event::Resized)
					printf("New window width: %i New window height: %i \n", event.size.width, event.size.height);

			if(event.type == sf::Event::TextEntered){
					if (event.text.unicode < 128)
						printf("%c", event.text.unicode);
			}
			if (isMove) sTurret.setPosition(pos.x-dx, pos.y-dy);
		}
		// draw
		window.clear();
		window.draw(sBackground);
		window.draw(sTurret);
		window.draw(sHead);
		window.display();
	}
	return 0;
}
