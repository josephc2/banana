class turret: public entity{
	public:
		turret(){
			dx = 0;
			dy = 0;
			name = "Turret";
		}

		void update(){
			x+=dx;
			y+=dy;
		}
};
class Bullet: public entity{
	public:
		int firing = 0;
		int count  = 0;
		Bullet(){
			dx = 0;
			dy = 0;
			name = "bullet";
		}
		void update(){
			x+=dx;
			y+=dy;
			if(count == 10){
				dx = 0;
				dy = -20;
				count = 0;
				//firing = 1;
			}
			else {
				count++;
				dx = 0;
				dy = 0;
			}
		}
};
class BulletUp: public Bullet{
	public:
		BulletUp(){
			dx = 0;
			dy = 0;
			name = "bulletUp";
		}
		void update(){
			x+=dx;
			y+=dy;
			if(count == 10){
				dx = 0;
				dy = 20;
				count = 0;
				//firing = 1;
			}
			else {
				count++;
				dx = 0;
				dy = 0;
			}
		}
};
