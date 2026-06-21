#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "DormitoryException.h"

using namespace std;

class Student {
public:
    Student(const string& id, const string& fullName, int academicYear);
    
    string getId() const;
    string getFullName() const;
    int getAcademicYear() const;
    string getDormitoryName() const;
    int getRoomNumber() const;
    bool isAccommodated() const;
    
    virtual void displayInfo() const;
    
    void setFullName(const string& name);
    void setId(const string& id);
    void setAcademicYear(int year);
    void assignAccommodation(const string& dormitoryName, int roomNumber);
    void removeAccommodation();
    
private:
    string id;
    string fullName;
    int academicYear;
    string dormitoryName;
    int roomNumber;
    bool accommodated;
};

#endif