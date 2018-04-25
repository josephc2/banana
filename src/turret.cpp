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
