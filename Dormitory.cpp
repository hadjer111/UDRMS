#include "Dormitory.h"
#include <iostream>
using namespace std;

Dormitory::Dormitory(const string& n, int c, const string& rn) 
    : name(n), capacity(c), restaurant(rn) {
    if (name.empty()) {
        throw DormitoryException("Dormitory name cannot be empty");
    }
    if (capacity <= 0) {
        throw DormitoryException("Invalid capacity");
    }
}

string Dormitory::getName() const {
    return name;
}

int Dormitory::getCapacity() const {
    return capacity;
}

int Dormitory::getTotalStudents() const {
    int total = 0;
    for (const auto& room : rooms) {
        total += room.getOccupancy();
    }
    return total;
}

Restaurant& Dormitory::getRestaurant() {
    return restaurant;
}

vector<Room>& Dormitory::getRooms() {
    return rooms;
}

void Dormitory::addRoom(const Room& r) {
    if (findRoom(r.getRoomNumber())) {
        throw DuplicateException("Room");
    }
    rooms.push_back(r);
}

bool Dormitory::assignStudent(Student* s, int roomNumber) {
    if (!s) {
        throw DormitoryException("Null student");
    }
    
    Room* room = findRoom(roomNumber);
    if (!room) {
        throw NotFoundException("Room");
    }
    
    return room->addStudent(s);
}

bool Dormitory::removeStudent(const string& id) {
    if (id.empty()) {
        throw DormitoryException("ID cannot be empty");
    }
    for (auto& room : rooms) {
        try {
            return room.removeStudent(id);
        } catch (const NotFoundException&) {
            continue;
        }
    }
    throw NotFoundException("Student");
}

Room* Dormitory::findRoom(int roomNumber) {
    for (auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            return &room;
        }
    }
    return nullptr;
}

void Dormitory::displayInfo() const {
    cout << "Dormitory: " << name << endl;
    cout << " Capacity: " << capacity << endl;
    cout << " Rooms: " << rooms.size() << endl;
    cout << "Restaurant: " << restaurant.getName() << endl;
}

void Dormitory::displayAvailableRooms() const {
    cout << " Available Rooms: " << endl;
    bool available = false;
    for (const auto& room : rooms) {
        if (!room.isFull()) {
            cout << "Room " << room.getRoomNumber() << endl;
            available = true;
        }
    }
    if (!available) {
        cout << " No available rooms\n";
    }
}