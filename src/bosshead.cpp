class bosshead: public head{
private:
  int hits = 2;

public:
  bosshead() : head() {
    dx = 4;
    dy = 0;
    speed = 4;
  }
};
