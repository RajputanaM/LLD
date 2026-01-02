
#include<bits/stdc++.h>
using namespace std;

enum class Direction
{
    UP,
    DOWN,
    IDLE
};

class Elevator{
    int id;
    Direction direction;
    int currentFloor;
    set<int> upList;
    set<int, greater<int>> downList;

    public:
    Elevator(int id){
        this->id = id;
        currentFloor = 0;
        direction = Direction::IDLE;
    }


    public:
        int getId() {
            return id;
        }
        bool isIdle(){
            return direction == Direction::IDLE;
        }
        int getCurrentFloor(){
            return currentFloor;
        }
        Direction getDirection(){
            return direction;
        }

        void addFloor(int floor){
            if(floor>currentFloor){
                upList.insert(floor);
            }
            else
                downList.insert(floor);
        }

        void move(){

            if(direction==Direction::IDLE){
                if(upList.empty())
                    direction = Direction::IDLE;
                else if (downList.empty())
                    direction = Direction::IDLE;
                else
                    return;
            }


            if(direction==Direction::UP){
                currentFloor++;
                cout << "lift "<<id<<" is going go the " << currentFloor << endl;
                if(upList.find(currentFloor)!=upList.end()){
                    upList.erase(currentFloor);
                }
                if(upList.size()==0 and downList.size()){
                    direction = Direction::DOWN;
                }
            }
            else{
                currentFloor--;
                cout << "lift "<<id<<" is going go the " << currentFloor << endl;
                if(downList.count(currentFloor)){
                    downList.erase(currentFloor);
                }
                if(downList.size()==0 and upList.size()){
                    direction = Direction::UP;
                }
            }
        }
};

class Controller{
    vector<Elevator *> elevators;

    Controller(int n){
        for (int i = 0; i < n;i++){
            elevators.push_back(new Elevator(i));
        }
    }

    // will write rest of the code tomorrow.
};
