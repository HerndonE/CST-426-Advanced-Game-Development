

// Dragon::getDragonMemento{

// }

class Memento{}

class DragonMemento : Memento {
  int id;
  int currentHP;
  int currentXP;
  string[] currentLoot;
  int size;
};


class Dragon {
  void loadDragon(DragonMemento* dragonMemento);
  DragonMemento* getDragonMemento;
};