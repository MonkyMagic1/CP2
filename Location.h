#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>

class Location {
public:
    Location();
    Location(int id, const std::string& name, const std::string& description, bool open);

    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    bool isOpen() const;

    void openLocation();
    void addConnection(int locationId);
    std::vector<int> getConnections() const;

    void addArtLine(const std::string& line);
    std::vector<std::string> getArt() const;

    void addChestId(int chestId);
    std::vector<int> getChestIds() const;

private:
    int id;
    std::string name;
    std::string description;
    bool open;
    std::vector<int> connections;
    std::vector<std::string> art;
    std::vector<int> chestIds;
};

#endif