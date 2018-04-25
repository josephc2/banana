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
