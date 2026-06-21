#include "Room.h"
#include <iostream>
using namespace std;

Room::Room(int num, int cap) : roomNumber(num), capacity(cap) {
    if (num <= 0) {
        throw DormitoryException("Invalid room number");
    }
    if (cap <= 0) {
        throw DormitoryException("Invalid capacity");
    }
}

int Room::getRoomNumber() const {
    return roomNumber;
}

int Room::getCapacity() const {
    return capacity;
}

bool Room::isFull() const {
    return students.size() >= capacity;
}

bool Room::isEmpty() const {
    return students.empty();
}

int Room::getOccupancy() const {
    return (int)students.size();
}

bool Room::hasStudent(const string& id) const {
    for (auto* s : students) {
        if (s->getId() == id) {
            return true;
        }
    }
    return false;
}

bool Room::addStudent(Student* student) {
    if (!student) {
        throw DormitoryException("Null student");
    }
    if (isFull()) {
        throw FullException("Room");
    }
    students.push_back(student);
    return true;
}

bool Room::removeStudent(const string& id) {
    if (id.empty()) {
        throw DormitoryException("ID cannot be empty");
    }
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i]->getId() == id) {
            students.erase(students.begin() + i);
            return true;
        }
    }
    throw NotFoundException("Student");
}

Student* Room::findStudent(const string& id) const {
    for (auto* s : students) {
        if (s->getId() == id) {
            return s;
        }
    }
    return nullptr;
}

void Room::displayRoom() const {
    cout << "Room " << roomNumber << "/" << capacity << endl;
    if (students.empty()) {
        cout << "  (Empty)\n";
        return;
    }
    for (const auto* s : students) {
        cout << "  " << s->getFullName() << " (" << s->getId() << ")\n";
    }
}