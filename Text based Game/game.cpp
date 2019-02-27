#include <iostream>

using namespace std;

int main()
{
	int healthincrement = 10;
	int playerHealth{ 30 };
	int playerStrength{ 8 };
	int monsterHealth{ 20 };
	int monsterStrength{ 11 };
	char input;
	cout << "A monster aproaches..." << endl;
	do
	{
		if (monsterHealth < healthincrement / 2)
			cout << "The monster barely alive..." << endl;
		else if (monsterHealth < healthincrement)
			cout << "The monster is weakening..." << endl;
		else
			cout << "The monster stands ready..." << endl;

		cout << "Health: " << playerHealth << endl;
		cout << "\tSelect action..." << endl << endl<<" (a)ttack  (h)eal :";
		cin >> input;
		switch (input)
		{
		case 'a':
		case 'A':
			cout << "You deal " << playerStrength << " points of damage to the monster" << endl;
			monsterHealth -= playerStrength;
			break;
		case 'h':
		case 'H':
			cout << "You restore " << 2 * playerHealth << " points of your health" << endl;
			playerHealth += 2 * playerStrength;
			break;
		default:
			cout << "You fumble in the heat of battle and miss the chance to attack" << endl;
			break;
		}
		if (monsterHealth > 0)
		{
			cout << "The monster lashes out, dealing " << monsterStrength << " points of damage to you." << endl;
			playerHealth -= monsterStrength;
		}
			
		else
			cout << "The monster breaths it's last, falling before you." << endl;
	} while (monsterHealth > 0 && playerHealth > 0);

	if (playerHealth > 0)
		cout << "You won!" << endl << endl;
	else
		cout << "You fell, never to rise." << endl << endl;
	system("PAUSE");

}