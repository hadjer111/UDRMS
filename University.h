#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <vector>
#include <memory>
#include <string>
#include "Dormitory.h"
#include "Student.h"
#include "DormitoryException.h"

using namespace std;

class University {
private:
    string name;
    vector<unique_ptr<Dormitory>> dormitories;
    vector<unique_ptr<Student>> students;
    
public:
    University(const string& name);
    
    void addDormitory(unique_ptr<Dormitory> dorm);
    void addStudent(unique_ptr<Student> student);
    void removeStudent(const string& id);
    
    Student* findStudent(const string& id);
    Dormitory* findDormitory(const string& name);
    
    bool assignStudentToDorm(const string& id, const string& dormName, int roomNum);
    
    void displayAll() const;
    void displayStudents() const;
    
    void saveData() const;
    void loadData();
    void saveData(const string& filepath) const;
    void loadData(const string& filepath);
    
    vector<unique_ptr<Dormitory>>& getDormitories();
    vector<unique_ptr<Student>>& getStudents();
};

#endif