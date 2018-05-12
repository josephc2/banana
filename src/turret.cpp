class turret: public entity{
	private:
		bool isShoot = false;
	public:
		turret(){
      dx = 0;
      dy = 0;
			name = "turret";
		}

		void update(){
			//count++;
			//std::cout << "count " << this->count << std::endl;
		}

		void turretShoot(animation *sBullet, int bulletShoot, entity *b){
			if (bulletShoot == 0){
				b->settings(*sBullet, this->x, this->y, -2, 0, 20);
				isShoot = false;
			}
		}
};
