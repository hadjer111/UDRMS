#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include "Student.h"
#include "DormitoryException.h"

using namespace std;

class Room {
private:
    int roomNumber;
    int capacity;
    vector<Student*> students;
    
public:
    Room(int number, int capacity);
    int getRoomNumber() const;
    int getCapacity() const;
    bool isFull() const;
    bool isEmpty() const;
    int getOccupancy() const;
    bool hasStudent(const string& id) const;
    bool addStudent(Student* student);
    bool removeStudent(const string& id);
    void displayRoom() const;
    Student* findStudent(const string& id) const;
};

#endif