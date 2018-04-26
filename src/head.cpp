class head: public entity{
	public:
		int moveMode = 0;
		head(){
			dx = 2;
			dy = 0;
			name = "head";
		}

		void update(){
			x+=dx;
			y+=dy;
			if(x > 1700){
				isAlive = 0;
			}
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
