#ifndef DORMITORY_H
#define DORMITORY_H

#include <iostream>
#include <vector>
#include "Restaurant.h"
#include "Room.h"
#include "Student.h"
#include "DormitoryException.h"

using namespace std;

class Dormitory {
private:
    string name;
    int capacity;
    Restaurant restaurant;
    vector<Room> rooms;
    
public:
    Dormitory(const string& name, int capacity, const string& restaurantName);
    
    string getName() const;
    int getCapacity() const;
    int getTotalStudents() const;
    Restaurant& getRestaurant();
    vector<Room>& getRooms();
    
    void addRoom(const Room& r);
    bool assignStudent(Student* s, int roomNumber);
    bool removeStudent(const string& id);
    Room* findRoom(int roomNumber);
    
    void displayInfo() const;
    void displayAvailableRooms() const;
};

#endif