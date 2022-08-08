#include <iostream>
#include <math.h>
#include "./src/map.cpp"
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main(int argc, char const *argv[])
{
    GameMap map;

    map.readMapFromFile("./src/gameMap/map.txt");
    map.drawMap();

    for (int i = 0; i < 10; i++){
        system("clear");
        map.updateMapState();
        map.drawMap();
        sleep(1);
    }

    return 0;
}
