#ifndef CHEST_H
#define CHEST_H

#include <vector>

class Chest {
public:
    Chest();
    Chest(int id, bool opened);

    int getId() const;
    bool isOpened() const;

    void openChest();
    void addPotionId(int potionId);
    std::vector<int> getPotionIds() const;

private:
    int id;
    bool opened;
    std::vector<int> potionIds;
};

#endif