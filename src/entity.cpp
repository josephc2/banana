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
