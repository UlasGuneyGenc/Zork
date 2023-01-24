#include "Stats.h"

Stats::Stats(int h, int a, int d)
    : health(h), attack(a), defence(d)
{
}

int Stats::getHealth() const
{
    return health;
}

int Stats::getAttack() const
{
    return attack;
}

int Stats::getDefence() const
{
    return defence;
}

void Stats::setHealth(int newHealth)
{
    health = newHealth;
}

void Stats::setAttack(int newAttack)
{
    attack = newAttack;
}

void Stats::setDefence(int newDefence)
{
    defence = newDefence;
}

void Stats::setAllNew(int h_amount, int a_amount, int d_amount)
{
    health = h_amount;
    attack = a_amount;
    defence = d_amount;
}

void Stats::modifyHealth(int amount)
{
    health += amount;
}

void Stats::modifyAttack(int amount)
{
    attack += amount;
}

void Stats::modifyDefence(int amount)
{
    defence += amount;
}

void Stats::modifyAll(int h_amount, int a_amount, int d_amount)
{
    health += h_amount;
    attack += a_amount;
    defence += d_amount;
}