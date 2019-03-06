#pragma once
#ifndef BATTLE_H
#define BATTLE_H

#include "Object.h"


char fight(Object player, const Object monsters[], int numMonsters);
char selectTarget(int numMonsters);
int attack(Object attacker, Object & defender);
int heal(Object & player);
void bringOutYourDead(Object monsters[], int & numMonsters);

#endif