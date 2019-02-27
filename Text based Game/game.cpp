#include <iostream>
#include <fstream>

using namespace std;


const int maxMonsters = 100;
const int healthIncrement = 10;
struct Object {
	int strength{ 0 };
	int health{ 0 };
};

void loadMonsters(Object monsters[maxMonsters], int & numMonsters);
char fight(Object player, const Object monsters[], int numMonsters);
int selectTarget(int numMonsters);
void attack(Object attacker, Object & defender);
void heal(int healingPoser, Object & player);
void bringOutYourDead(Object monsters[], int & numMonsters);
bool isGameOver(Object player, int numMonsters);
void gameOver(Object player, int numMonsters);




int main()
{

	Object player;
	Object monsters[maxMonsters];
	int numMonsters = 4;
	int monster;
	char input;
	player.health = healthIncrement * 10;
	player.strength = player.health / 4;
	loadMonsters(monsters, numMonsters);

	cout << "A group of monsters aproaches..." << endl;
	do
	{
		switch (fight(player, monsters,numMonsters))
		{
		case 'a':
		case 'A':
			monster = selectTarget(numMonsters);
			cout << "Dealt "<< player.strength << " damage to Monster " << 'A' + monster << endl;
			attack(player, monsters[monster]);
			
			break;
		case 'h':
		case 'H':
			cout << "You recover "<< player.strength * 2<< " points of health." << endl;
			heal(player.strength * 2, player);
			
			break;
		default:
			cout << "You fumble in the heat of battle and miss the chance to attack." << endl;
			break;
		}
		for (int i = 0; i < numMonsters; i++)
		{
			cout << "Monster " << (char)('A' + i) << " dealt " << monsters[i].strength << " damage to you" << endl;
			attack(monsters[i], player);
			
		}
		bringOutYourDead(monsters, numMonsters);
	} while (isGameOver(player,numMonsters));
	gameOver(player, numMonsters);

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
char fight(Object player, const Object monsters[], int numMonsters)
{
	char input;
	char mon = 'A';
	for (int i = 0; i < numMonsters; i++)
	{
		cout << "Monster " << mon++<<" Health: "<<monsters[i].health<<endl;
	}
	cout << "Health: " << player.health << endl;
	cout << "\tSelect action..." << endl << endl<<" (a)ttack  (h)eal :";
	cin >> input;
	return input;
}
int selectTarget(int numMonsters)
{
	char mon = 'A';
	char input;
	bool valid = true;
		do
		{
			cout << "Which enemy will you attack?" << endl;
			for (int i = 0; i < numMonsters; i++)
			{
				cout << " (" << mon++ << ")";
			}
			cout << ": ";
			cin >> input;
			switch (input)
			{
			case 'a':
			case 'A':
				return 0;
				break;
			case 'b':
			case 'B':
				return 1;
				break;
			case 'c':
			case 'C':
				return 2;
				break;
			case 'd':
			case 'D':
				return 3;
				break;
			default:
				cout << "That monster is no available... Please try again." << endl;
				valid = false;
				break;
			}
		} while (!valid);
}
void attack(Object attacker, Object & defender)
{
	defender.health -= attacker.strength;
}
void heal(int healingPower, Object & player)
{
	player.health += healingPower;
}
void bringOutYourDead(Object monsters[], int & numMonsters)
{
	int deadOne=-1;
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
		cout << "You won, but the thirll is short as you step over the bodies of your \nenemies and on towards your next fight..." << endl << endl;
}