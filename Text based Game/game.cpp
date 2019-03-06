#include <iostream>
#include <fstream>
#include <random>

#include "Object.h"
#include "battle.h"

using namespace std;


const int maxMonsters = 100;
const int healthIncrement = 10;

void loadMonsters(Object monsters[maxMonsters], int & numMonsters);
bool isGameOver(Object player, int numMonsters);
void gameOver(Object player, int numMonsters);




int main()
{

	Object player;
	Object monsters[maxMonsters];
	int numMonsters = 4;
	int monster;
	int tempInt;
	char tempChar;
	double mAttChnc = 0.75;
	int hpBase = 100;
	int strBase= hpBase / 4;
	bool cont = true;
	loadMonsters(monsters, numMonsters);
	random_device seed;
	default_random_engine e(seed());
	bernoulli_distribution attChnce(mAttChnc);
	uniform_int_distribution<int> hpRand(1, hpBase);
	uniform_int_distribution<int> strRand(1, strBase);
	player.health = hpRand(e);
	player.strength = strRand(e);
	cout << "A ";
	do
	{
		cout << "group of monsters aproach..." << endl;
		do
		{
			tempChar = fight(player, monsters, numMonsters);
			switch (tempChar)
			{
			case 'A':
				tempChar = selectTarget(numMonsters);
				tempInt = attack(player, monsters[tempChar - 'A']);
				cout << "Dealt " << tempInt << " damage to Monster " << tempChar << endl;
				break;
			case 'H':
				tempInt = heal(player);
				cout << "You recover " << tempInt << " points of health." << endl;
				break;
			default:
				cout << "You fumble in the heat of battle and miss the chance to attack." << endl;
				break;
			}
			for (int i = 0; i < numMonsters; i++)
			{
				if (attChnce(e))
				{
					tempInt = attack(monsters[i], player);
					cout << "Monster " << (char)('A' + i) << " dealt " << tempInt << " damage to you." << endl;
				}
				else
					cout << "Monster " << (char)('A' + i) << " dealt " << tempInt << " damage to you." << endl;
			}
			bringOutYourDead(monsters, numMonsters);
		} while (isGameOver(player, numMonsters));
		gameOver(player, numMonsters);
		cout << "Forge on?" << endl << "(y)es/(n)o... ";
		cin >> tempChar;
		tempChar = 'N';//toupper(tempChar);
		if (tempChar == 'N')
		{
			cont = false;
			cout << "\nYour battles won, you return home triumphant and settle down to a peaceful life... you hope." << endl << endl;
		}
		else
			cout << "Another ";
	} while (cont);

	system("PAUSE");

}

void loadMonsters(Object monsters[maxMonsters], int & numMonsters)
{
	ifstream fin;
	fin.open("monsterstats.txt");
	for (int i = 0; i < numMonsters; i++)
	{
		fin >> monsters[i].health;
		monsters[i].health = monsters[i].health*healthIncrement;
		monsters[i].strength = monsters[i].health / 6;
	}
	fin.close();
}
bool isGameOver(Object player, int numMonsters)
{
	if (player.health <= 0||numMonsters==0)
		return false;
	return true;
}

void gameOver(Object player, int numMonsters)
{
	if (player.health <= 0)
		cout << "You fell, never to rise." << endl << endl;
	if(numMonsters == 0)
		cout << "You won, but the thrill is short as you step over the bodies of your \nenemies and on towards your next fight..." << endl << endl;
}