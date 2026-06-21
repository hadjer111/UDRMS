#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(const string& d, const string& n, int y) 
    : id(d), fullName(n), academicYear(y), dormitoryName(" "), roomNumber(-1), accommodated(false) {
    if (id.empty() || fullName.empty()) {
        throw DormitoryException("ID and Name cannot be empty");
    }
    if (academicYear < 1 || academicYear > 5) {
        throw DormitoryException("Year must be between 1 and 5");
    }
}

void Student::setFullName(const string& name) {
    if (name.empty()) {
        throw DormitoryException("Name cannot be empty");
    }
    fullName = name;
}

void Student::setId(const string& d) {
    if (d.empty()) {
        throw DormitoryException("ID cannot be empty");
    }
    id = d;
}

void Student::setAcademicYear(int year) {
    if (year < 1 || year > 5) {
        throw DormitoryException("Year must be between 1 and 5");
    }
    academicYear = year;
}

string Student::getId() const {
    return id;
}

string Student::getFullName() const {
    return fullName;
}

int Student::getAcademicYear() const {
    return academicYear;
}

string Student::getDormitoryName() const {
    return dormitoryName;
}

int Student::getRoomNumber() const {
    return roomNumber;
}

bool Student::isAccommodated() const {
    return accommodated;
}

void Student::assignAccommodation(const string& dormitoryName, int roomNumber) {
    if (accommodated) {
        throw DormitoryException("Student already has a room");
    }
    if (roomNumber <= 0) {
        throw DormitoryException("Invalid room number");
    }
    this->dormitoryName = dormitoryName;
    this->roomNumber = roomNumber;
    accommodated = true;
}

void Student::removeAccommodation() {
    if (!accommodated) {
        throw DormitoryException("Student not accommodated");
    }
    dormitoryName = " ";
    roomNumber = -1;
    accommodated = false;
}

void Student::displayInfo() const {
    cout << "================================\n";
    cout << "ID: " << id << "\n";
    cout << "Name: " << fullName << "\n";
    cout << "Year: " << academicYear << "\n";
    cout << "================================\n";
    if (accommodated) {
        cout << "Dormitory: " << dormitoryName << '\n';
        cout << "Room: " << roomNumber << '\n';
    } else {
        cout << "Status: Not Assigned\n";
    }
}