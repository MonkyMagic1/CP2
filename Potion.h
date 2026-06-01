#ifndef POTION_H
#define POTION_H

#include <string>

class Potion {
public:
    Potion();
    Potion(int id, const std::string& name, int healAmount);

    int getId() const;
    std::string getName() const;
    int getHealAmount() const;

private:
    int id;
    std::string name;
    int healAmount;

};

#endif