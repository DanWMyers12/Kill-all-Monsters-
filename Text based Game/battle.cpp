#include <iostream>
#include <random>
#include "Object.h"
#include "battle.h"

using namespace std;
random_device seed;
default_random_engine e(seed());

char fight(Object player, const Object monsters[], int numMonsters)
{
	char input;
	char mon = 'A';
	cout << endl << endl;
	for (int i = 0; i < numMonsters; i++)
	{
		cout << "Monster " << mon++ << " Health: " << monsters[i].health << endl;
	}
	cout << "Health: " << player.health << endl;
	cout << "\tSelect action..." << endl << endl << " (a)ttack  (h)eal :";
	cin >> input;
	return toupper(input);
}
char selectTarget(int numMonsters)
{
	char mon = 'A';
	char input;
	bool valid = true;
	do
	{
		cout << endl << "Which enemy will you attack?" << endl;
		for (int i = 0; i < numMonsters; i++)
		{
			cout << " (" << mon++ << ")";
		}
		cout << ": ";
		cin >> input;
		input = toupper(input);
		if (input - 'A' >= numMonsters)
		{
			cout << "I'm sorry, there is no such monster..."<<endl;
			mon = 'A';
			valid = false;
		}
		else
			return input;
	} while (!valid);
}
int attack(Object attacker, Object & defender)
{
	normal_distribution<double> attDev((double)attacker.strength, (double)attacker.strength / 2);
	int dam = (int)attDev(e);
	if (dam <= 0)
		dam = 1;
	defender.health -= dam;
	return dam;
}
int heal(Object & player)
{
	normal_distribution<double> hdev((double)player.strength*2, (double)player.strength / 4);
	int heals = (int)hdev(e);
	player.health += heals;
	return heals;
}
void bringOutYourDead(Object monsters[], int & numMonsters)
{
	int deadOne = -1;
	for (int i = 0; i < numMonsters; i++)
	{
		if (monsters[i].health <= 0)
		{
			deadOne = i;
			numMonsters--;
			cout << "Monster " << (char)('A' + deadOne) << " falls." << endl;
		}


		switch (deadOne)
		{
		case 0:
			monsters[0] = monsters[1];
		case 1:
			monsters[1] = monsters[2];
		case 2:
			monsters[2] = monsters[3];
		default:
			deadOne = -1;
			break;
		}
	}
}