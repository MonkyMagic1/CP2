#include "Location.h"

Location::Location()
{
    id = 0;
    name = "";
    description = "";
    open = false;
}

Location::Location(int id, const std::string& name, const std::string& description, bool open)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->open = open;
}

int Location::getId() const
{
    return id;
}

std::string Location::getName() const
{
    return name;
}

std::string Location::getDescription() const
{
    return description;
}

bool Location::isOpen() const
{
    return open;
}

void Location::openLocation()
{
    open = true;
}

void Location::addConnection(int locationId)
{
    connections.push_back(locationId);
}

std::vector<int> Location::getConnections() const
{
    return connections;
}

void Location::addArtLine(const std::string& line)
{
    art.push_back(line);
}

std::vector<std::string> Location::getArt() const
{
    return art;
}

