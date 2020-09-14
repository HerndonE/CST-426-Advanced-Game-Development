//
//  main.cpp
//  StrategyPattern
//
//  Created by Krzysztof Pietroszek on 2017-09-07.
//  Copyright © 2017 Krzysztof Pietroszek. All rights reserved.
//

#include <iostream>
using namespace std;


// this is an abstract class, in Java you would use interface instead
class NavigationStrategy
{
public:
    virtual void find_path() const = 0;
    virtual ~NavigationStrategy() {};
};

// this is a concrete navigation strategy (algorithm)
class AStar: public NavigationStrategy
{
public:
    AStar(){}
    virtual void find_path() const {
        cout << "Finding path using A*\n";
    }
    ~AStar() {}
};

// this is another concrete navigation strategy (algorithm)
class CollaborativeDiffusion: public NavigationStrategy {
public:
    CollaborativeDiffusion() {};
    virtual void find_path() const {
        // here we would have quicksort implementation
        cout << "Finding path using Collaborative Diffusion\n";
    }

};


// We use the strategy pattern in Monster class. This class would be larger, would have more data in real game.
// Here we only focus on the navigation problem for the monster
class Monster
{
protected:

    NavigationStrategy* m_navigate;


public:

    void find_path() const {
        m_navigate->find_path();
    }
    
    void set_navigation_strategy(NavigationStrategy* s){
        m_navigate= s;
    }

};

// when creating this monster, we will choose
class WalkingMonster : public Monster{

public:
    WalkingMonster() {
        m_navigate = new AStar();
    }
    
    ~WalkingMonster() {
        delete m_navigate;
    }
};

// when creating this monster, we will choose CollaborativeDiffusion strategy
class MazeMonster : public Monster{
public:
    MazeMonster()  {
        m_navigate = new CollaborativeDiffusion();
    }
    ~MazeMonster() {
        delete m_navigate;
    }
    
};


int main(int argc, char *argv[])
{
    
    WalkingMonster* walking_monster = new WalkingMonster();
    walking_monster->find_path();
    
    MazeMonster* maze_monster = new MazeMonster();
    maze_monster->find_path();
    

    delete walking_monster;
    delete maze_monster;
    
    return 0;
}