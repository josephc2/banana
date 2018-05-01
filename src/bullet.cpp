class bullet: public entity
{
public:
  bullet()
  {
    name="bullet";
  }

void update()
  {
   x+=dx;
   y+=dy;
  }
};
