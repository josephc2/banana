#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#define MAX_X 1920
#define MAX_Y 1080

class animation{
	public:
		float Frame;
		float speed;
		sf::Sprite sprite;
		std::vector<sf::IntRect> frames;

		animation(){}
		animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed){
			Frame = 0;
			speed = Speed;

			for (int i=0;i<count;i++)
				frames.push_back(sf::IntRect(x+i*w, y, w, h));

			sprite.setTexture(t);
			//sprite.setSmooth(true);
			sprite.setOrigin(w/2,h/2);
			sprite.setTextureRect(frames[0]);
		}


		void update(){
			Frame += speed;
			int n = frames.size();
			if (Frame >= n) Frame -= n;
			if (n>0) sprite.setTextureRect( frames[int(Frame)] );
		}

		bool isEnd(){
			return Frame+speed>=frames.size();
		}
};

class entity{
	public:
		float x;
		float y;
		float dx;
		float dy;
		float R;
		bool isAlive;
		std::string name;
		animation anim;

		entity(){
			isAlive = 1;
		}

		void settings(animation &a,int X,int Y,int radius){
			anim = a;
			x=X;
			y=Y;
			R = radius;
		}

		virtual void update(){};

		void draw(sf::RenderWindow &app){
			anim.sprite.setPosition(x,y);
			app.draw(anim.sprite);

			sf::CircleShape circle(R);
			circle.setPosition(x,y);
			circle.setOrigin(R,R);
			//std::cout << "X: " << x << "	Y: " << y <<std::endl;
			//std::cout << "dX: " << dx << "	dY: " << dy <<std::endl;
		}

		virtual ~entity(){};
};

class head: public entity{
	public:
		int moveMode = 0;
		bool isOutofMap = 0;
		head(){
			dx = 2;
			dy = 0;
			name = "head";
		}

		void update(){
			x+=dx;
			y+=dy;
			//std::cout << "moveMode is " << moveMode << std::endl;
			//first straight path, go up
			if(moveMode == 0){
				if(x > 500){
					dx = 0;
					dy = -2;
					moveMode = 1;
				}
			}
			if(moveMode == 1){
				if(y < 350){
					dx = 2;
					dy = 0;
					moveMode = 2;
				}
			}
			if(moveMode == 2){
				if(x > 875){
					dx = 0;
					dy = 2;
					moveMode = 3;
				}
			}
			if(moveMode == 3){
				if(y > 760){
					dx = 2;
					dy = 0;
					moveMode = 4;
				}
			}
			if(moveMode == 4){
				if(x > 1400){
					dx = 0;
					dy = -2;
					moveMode = 5;
				}
			}
			if(moveMode == 5){
				if(y < 550){
					dx = 2;
					dy = 0;
				}
			}
		}
};

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
