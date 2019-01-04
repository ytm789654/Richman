#include <iostream>
#include <vector>
#include "node.h"
#include "player.h"
#include "GameMap.h"

int main()
{
	GameMap *TestMap = new GameMap();
	TestMap->InitMapFromFile("testmap.mp");
	TestMap->DumpMap();
	delete TestMap;
	char pause;
	cin >> pause;
	return 0;
}