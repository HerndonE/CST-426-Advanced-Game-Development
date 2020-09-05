
class DragonMesh{
public: 
   string scaleColor, eyes, breath;

  void printDragonDesc(){ 
    cout << "Dragon scale color: " << scaleColor << "\nDragon eyes: " << eyes << "\nDragon breath: " << breath;
  }

};

class FireDragonMesh : public DragonMesh{ 
  public:
    *FireDragonMesh(){
    scaleColor = "Red and orange scales ";
    eyes = "Red eyes "; 
    breath = "Fire breath ";
  }
};
    
class iceDragonMesh : public DragonMesh{ 
  public:
    *iceDragonMesh(){
       scaleColor = "Blue and white scales ";
       eyes = "Blue eyes "; 
       breath = "Ice breath ";
     
  }
};
class lighteningDragonMesh : public DragonMesh{ 
  public:
    *lighteningDragonMesh(){
       scaleColor = "Yellow and white scales ";
       eyes = "Yellow eyes "; 
       breath = "Lightening breath ";

  }
};

class Dragon{

  DragonMesh* mesh ;
  int id; 
  int xp;
  double HP; 
  string loot;
  string size;


}