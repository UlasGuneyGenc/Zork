#pragma once

class Stats
{
private:
    int health;
    int attack;
    int defence;
public:
    Stats(int h = 0, int a = 0, int d = 0);
    int getHealth() const;
    int getAttack() const;
    int getDefence() const;

    void setHealth(int newHealth);
    void setAttack(int newAttack);
    void setDefence(int newDefence);

    void modifyAll(int h_amount, int a_amount, int d_amount);
    void modifyHealth(int amount);
    void modifyAttack(int amount);
    void modifyDefence(int amount);
};
