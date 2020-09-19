/*Quick Psuedocode
player {
  player loadPlayer (playerMemento* characterMemento);
  playerMemento* getplayerMemento;
}

player::getplayerMemento{

Memento{}

playerMemento : Memento {
  int score;
  int level;
  int posx;
  int posy;
  int lives;

}
*/

class playerMemento{
  public: 
  int score;
  int level;
  int posx;
  int posy;
  int lives;
  playerMemento(iint score, int level, int posx, int posy,
  int lives){
    this->id = id;
    this->level = level;
    this->posx = posx;
	this->posy = posy;
	this->lives = lives;
  }
};

void loadPlayer(playerMemento *memento, Player &player){
  if(memento->id == 01){
    Player *Arnold = new mainCharacter(memento->size);
    Arnold->score = memento->score;
	Arnold->level = memento->level;
	Arnold->posx = memento->posx;
	Arnold->posy = memento->posy;
	Arnold->lives = memento->lives;
    player = *Arnold;
  }
}