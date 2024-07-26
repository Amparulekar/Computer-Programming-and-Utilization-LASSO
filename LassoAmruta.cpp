#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>

using namespace simplecpp;

class MovingObject : public Sprite {
  vector<Sprite*> parts;
  double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
  }
 public:
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)
    : Sprite() {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
   double angle_rad = angle_deg*PI/180.0;
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}

//coin.h
#ifndef __COIN_H__
#define __COIN_H__



class Coin : public MovingObject {

  int coin_type;
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  Circle coin_circle;

 public:
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta, int type) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
 {

    coin_type = type;
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();

  }

  void initCoin();
  void resetCoin();

  int getCoinType () {return coin_type; }

}; // End class Coin

// AMRUTA has written This Class: The class BrownBomb Reresents a Bomb wich is a new moving object
// If the User Catches it accidently, the User is Penalized with negative Score
// Base Class is Moving Object Shape is kept as Circle Only

class BrownBomb : public MovingObject {
  double bomb_start_x;
  double bomb_start_y;
  double release_speed;
  double release_angle_deg;
  double bomb_ax;
  double bomb_ay;

  Circle bomb_circle;


 public:
 BrownBomb(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
 {
    release_speed = speed;
    release_angle_deg = angle_deg;
    bomb_ax = argax;
    bomb_ay = argay;
    initCoin();

  }

  void initCoin();
  void resetCoin();

}; // End class BrownBomb

// AMRUTA has written This Class: The class TextBox Reresents a Text wich is a new moving object
// There atre three Text Boxes instanciated with letters "C" , "A", "T" respectively.
// When the useer catches any of the Text Box, the user is awarded score points
// If the User is able to catch Text boxes in a sequential manner to form word "CAT", higher points are awarded to the user.
// The Strings formed by the Text Characters is displayed on the Dash Board
// BAse class is Moving Object

class TextBox : public MovingObject {
  double text_start_x;
  double text_start_y;
  double release_speed;
  double release_angle_deg;
  double text_ax;
  double text_ay;

  Text text_circle;
  int charNum; // Data which represents the Character enclosed in the Text Box


 public:
 TextBox(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta, int charNumber) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
 {
    release_speed = speed;
    release_angle_deg = angle_deg;
    text_ax = argax;
    text_ay = argay;

    charNum = charNumber;
    initCoin();

  }

  void initCoin();
  void resetCoin();

  void setCharNum (int number); // Data Member is kept to differentiate between "C"/"A"/"T"
  int getCharNum ();            // Return the data member which reveals the character associated with Text Box

}; // End class TextBox
#endif

//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90

#define LASSO_G 30
#define COIN_G 30


#define LASSO_SIZE 10
#define LASSO_RADIUS 40
#define COIN_SIZE 7

// AMRUTA : Change Size of the BOMB and TextBox

#define BROWN_BOMB_SIZE 10

#define TEXT_BOX_SIZE_FORA "A"
#define TEXT_BOX_SIZE_FORC "C"
#define TEXT_BOX_SIZE_FORT "T"


class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  float maxPerformanceIndex; // Indicates the Hightest Performance achieved by the user in the Session
  char word [256]; // String Reserved to collect the Characters Yanked So far & displayed in Dashboard


  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Coin *the_coin;

  BrownBomb *the_brown_bomb; // Pointer to Bombs caught
  TextBox * the_text_box;    // Pointer to Text Boxes caught

  int num_coins; // Total Number Of Coins caught

  //AMRUTA added these data members
  int num_brown_bombs;  // Total Number of Bombs caught
  int num_text_boxes;   // Total Number of Text Boxes caught
  int num_cats;         // Total Number of Times the User caught string "CAT" by catching each character "C"/"A"/"T"

  void initLasso();

 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);

  void check_for_coin(Coin *coin);
  void check_for_bomb(BrownBomb *bomb);
  void check_for_text(TextBox *text);


  int getNumCoins() { return num_coins; }
  int getNumBrownCoins() { return num_brown_bombs; }
  int getNumTextBoxes() { return num_text_boxes;}
  int getNumCats () {return num_cats;}
  void setNumCats (int number) {num_cats = number;}

  float getMaxPerformanceIndex () {return maxPerformanceIndex;}
  void  setMaxPerformanceIndex (float index){ maxPerformanceIndex = index;}

  char* getWord () {return word;}
  void setWordEmpty () { word [0] = '\0';}
  void displayHelp ();

}; // End class Lasso

#endif

//coin.h

void Coin::initCoin()

{
  if (coin_type == 1)

  {coin_start_x = (PLAY_X_START+WINDOW_X)/1.5;
  } // X Co-ordinate of Red Coin

  if (coin_type ==2)

    {coin_start_x = (PLAY_X_START+WINDOW_X)/1.7;
    } // X Co-ordinate of YELLOW (Gold) Coin

  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);

  if (coin_type == 1)coin_circle.setColor(COLOR("red")); // Red Coin

  if (coin_type == 2)coin_circle.setColor(COLOR("yellow")); // Yello Coin

  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void BrownBomb::initCoin()
{
  bomb_start_x = (PLAY_X_START+WINDOW_X)/2.0; // X Co-ordinate of Bomb
  bomb_start_y = PLAY_Y_HEIGHT;
  bomb_circle.reset(bomb_start_x, bomb_start_y, BROWN_BOMB_SIZE);
  bomb_circle.setColor(COLOR("black")); // Colour of Bomb
  bomb_circle.setFill(true);
  addPart(&bomb_circle);
}

void TextBox::initCoin() {

  if (charNum == 1)text_start_x = (PLAY_X_START+WINDOW_X)/2.2; // First Text Box

  if (charNum == 2)text_start_x = (PLAY_X_START+WINDOW_X)/2.75; // Second Text Box

  if (charNum == 3)text_start_x = (PLAY_X_START+WINDOW_X)/3.3;  // Third Text Box

  text_start_y = PLAY_Y_HEIGHT;

  if (charNum == 1)text_circle.reset(text_start_x, text_start_y,  TEXT_BOX_SIZE_FORA);
  if (charNum == 2)text_circle.reset(text_start_x, text_start_y,  TEXT_BOX_SIZE_FORC);
  if (charNum == 3)text_circle.reset(text_start_x, text_start_y,  TEXT_BOX_SIZE_FORT);

  text_circle.setColor(COLOR("black"));
  text_circle.setFill(true);
  addPart(&text_circle);
}

int  TextBox :: getCharNum (){ return charNum;}
void TextBox :: setCharNum (int number){ charNum = number;}

void Coin::resetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void BrownBomb::resetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  bomb_ax = 0;
  bomb_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(bomb_start_x, bomb_start_y, coin_speed, coin_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
}

void TextBox::resetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  text_ax = 0;
  text_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(text_start_x, text_start_y, coin_speed, coin_angle_deg, text_ax, text_ay, paused, rtheta);
}
//lasso.cpp


void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("blue"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("green"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;

  the_coin = NULL; // Initialization
  the_brown_bomb = NULL; //Initialization
  the_text_box = NULL; //Initialization

  num_coins = 0; // Set Number of coins to zero
  num_brown_bombs = 0; // Set Number of bombs to zero
  num_text_boxes = 0; // Set Number of Text boxes to zero
  num_cats = 0; // Set number of words "CAT" fetched to zero

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("blue"));

  lasso_band.setColor(COLOR("green"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {


  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;

  if(the_coin != NULL)
  {
    num_coins++;
    if (the_coin->getCoinType() == 2)num_coins++ ;  // If the Coin is Yello (Gold) increase the score twice or equivalent to 2 Red coins

    the_coin->resetCoin();
    the_coin = NULL; // This was the missing Line in the Original Code was BUG
    }

    if(the_brown_bomb != NULL) {
    num_brown_bombs++;
    the_brown_bomb->resetCoin();
    the_brown_bomb = NULL;
  }

    if(the_text_box != NULL) {
    num_text_boxes++;

    if (the_text_box->getCharNum()== 1)
    {

        word[num_text_boxes - 1]= 'A';
        word[num_text_boxes] = '\0';
    }
  if (the_text_box->getCharNum()== 2)
    {

        word[num_text_boxes - 1]= 'C';
        word[num_text_boxes] = '\0';
    }

      if (the_text_box->getCharNum()== 3)
    {

        word[num_text_boxes - 1]= 'T';
        word[num_text_boxes] = '\0';
    }

// Since the user has fetched more than 3 characters so far in the Game, check
// Whether the last 3 characters fetched forms a string as "CAT"

    if (num_text_boxes >= 3)
    {

    if (word[num_text_boxes -1] == 'T' && word[num_text_boxes -2] == 'A' && word [num_text_boxes -3]== 'C')
         {
            num_cats++;

         }
    }
    the_text_box->resetCoin();
    the_text_box = NULL;
    }
} // End Lasso::yank()

void Lasso::loopit() {


  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr) {

//cout<< " Entered check_for_coin()";

  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff)); // Distance Formula

  //cout << " distance = "<< distance << " LASSO_RADIUS = " << LASSO_RADIUS;

  if(distance <= LASSO_RADIUS) {

  //cout<< "Got Coin in function check_for_Coin()";

    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
} // End Lasso::check_for_coin()

void Lasso::check_for_bomb(BrownBomb *coinPtr) {


  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff)); // Distance Formula

  //cout << " distance = "<< distance << " LASSO_RADIUS = " << LASSO_RADIUS;

  if(distance <= LASSO_RADIUS) {

  //cout<< "Got Coin in function check_for_Coin()";

    the_brown_bomb = coinPtr;
    the_brown_bomb->getAttachedTo(this);
  }
} // End Lasso::check_for_coin()

void Lasso :: displayHelp()
{

  cout << " When t is pressed, throw lasso" ; cout << '\n';
  cout << " If lasso within range, make coin or Alphabet or Bomb stick "; cout << '\n';
  cout << " When y is pressed, yank lasso" ; cout << '\n';
  cout << " When l is pressed, loop lasso" ; cout << '\n';
  cout << " When q is pressed, quit" ; cout << '\n';
  cout  << " When h is pressed , Display HELP Screen"; cout << '\n';
}
void Lasso::check_for_text(TextBox *coinPtr) {


  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff)); // Distance Formula

  //cout << " distance = "<< distance << " LASSO_RADIUS = " << LASSO_RADIUS;

  if(distance <= LASSO_RADIUS) {

  //cout<< "Got TextBox in function check_for_text()";

    the_text_box = coinPtr;
    the_text_box->getAttachedTo(this);

  }
} // End Lasso::check_for_text()

main_program {


  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;

  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso.setWordEmpty(); // Set Word String Empty which isused to catch TextBoxes

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);

   char coinScoreStr[256];
  //sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+350, PLAY_Y_HEIGHT+50, coinScoreStr);

  // AMRUTA : Brown Bomb Score String

  char BrownbombScoreStr[256];
  //sprintf(BrownbombScoreStr, "Bombs: %d", lasso.getNumBrownCoins());
  Text BrownbombScore(PLAY_X_START+350, PLAY_Y_HEIGHT+70, BrownbombScoreStr);

    // AMRUTA : Text Box Score String

  //char TextBoxScoreStr[256];
  //sprintf(TextBoxScoreStr, "Texts: %d", lasso.getNumTextBoxes());
  //Text TextBoxScore(PLAY_X_START+50, PLAY_Y_HEIGHT+90, TextBoxScoreStr);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;

  //AMRTUA initiated the cOIN

  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 1); // Instantiate Red Coin

  Coin coin_second(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 2); // Instantiate YELLOW Coin


  // AMRUTA Instantiate the Bomb

  BrownBomb brownbomb (coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

  // AMRUTA Instantiate the Text Boxes

  TextBox textbox1 (coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 1);
  TextBox textbox2 (coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 2);
  TextBox textbox3 (coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, 3);


  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit
  // When h is pressed , Display HELP Screen

  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();

	lasso.check_for_coin(&coin);
	lasso.check_for_coin (&coin_second);
	lasso.check_for_bomb(&brownbomb);
    lasso.check_for_text(&textbox1);
    lasso.check_for_text(&textbox2);
    lasso.check_for_text(&textbox3);


	wait(STEP_TIME*5);
	break;

	case 'h' :
	lasso.displayHelp ();
	break;

      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
	exit(0);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    coin.nextStep(stepTime);
    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }

    coin_second.nextStep(stepTime);
    if(coin_second.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin_second.unpause();
      }
    }

    if(coin_second.getYPos() > PLAY_Y_HEIGHT) {
      coin_second.resetCoin();
      last_coin_jump_end = currTime;
    }

    // AMRUTA has Written Code for brownbomb

    brownbomb.nextStep(stepTime);
    if(brownbomb.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	brownbomb.unpause();
      }
    }

    if(brownbomb.getYPos() > PLAY_Y_HEIGHT) {
      brownbomb.resetCoin();
      last_coin_jump_end = currTime;
    }

    // AMRUTA has Written Code for textbox

    textbox1.nextStep(stepTime);
    if(textbox1.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	textbox1.unpause();
      }
    }

    textbox2.nextStep(stepTime);
    if(textbox2.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	textbox2.unpause();
      }
    }

    textbox3.nextStep(stepTime);
    if(textbox3.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	textbox3.unpause();
      }
    }

    if(textbox1.getYPos() > PLAY_Y_HEIGHT) {
      textbox1.resetCoin();
      last_coin_jump_end = currTime;
    }

    if(textbox2.getYPos() > PLAY_Y_HEIGHT) {
      textbox2.resetCoin();
      last_coin_jump_end = currTime;
    }

     if(textbox3.getYPos() > PLAY_Y_HEIGHT) {
      textbox3.resetCoin();
      last_coin_jump_end = currTime;
    }

    int numberOfCoins = lasso.getNumCoins();
    int numberOfBombs = lasso.getNumBrownCoins();
    int numberOfTextBoxes = lasso.getNumTextBoxes();
    int numberOfCats = lasso.getNumCats();

    int netScore = 2*numberOfCats + numberOfTextBoxes + numberOfCoins - 2 * numberOfBombs;

    float performanceIndex = netScore/(currTime/10); // Performance Index displays Efficiency of the Player
    // As the Time progresses, and if the user does not catch any object, the Performance Index (PI)
    // Starts flling and the same is displyed on the dashboard
    // Also VAriable is kept in Lasso Class to store the highest Performance Index of the session

    float maxperformanceIndex = lasso.getMaxPerformanceIndex();
    if (performanceIndex > maxperformanceIndex)
        {lasso.setMaxPerformanceIndex(performanceIndex);}

    // Display The Dashboard Screen
    sprintf(coinScoreStr, "Coins: %d BLACK Bombs: %d TEXTS : %d WORD = %s", numberOfCoins,numberOfBombs, numberOfTextBoxes, lasso.getWord());
    coinScore.setMessage(coinScoreStr);


    sprintf(BrownbombScoreStr, "SCORE: %d   PerformanceIndex(PI) : %5.3f  HIGHIEST PI : %5.3f  CATS CAUGHT = %d",
    netScore, performanceIndex, lasso.getMaxPerformanceIndex(), lasso.getNumCats() );

    BrownbombScore.setMessage(BrownbombScoreStr);


    stepCount++;
    currTime += stepTime;

    // cout << " CurrTime = " << currTime;
    //cout << " StepCount = " << stepCount;

    wait(stepTime);
  } // End for(;;)

  wait(3);
}// End Main Program
