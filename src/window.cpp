#include <SFML/Graphics.hpp> 

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Close | sf::Style::Titlebar);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					printf("New window width: %i New window height: %i \n", event.size.width, event.size.height);	
				case sf::Event::TextEntered:
					if (event.text.unicode < 128){
						printf("%c", event.text.unicode);
					}			
			}
		}
	}
	return 0;
}

