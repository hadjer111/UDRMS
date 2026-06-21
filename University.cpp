#include "University.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <sys/stat.h>

using namespace std;

University::University(const string& n) : name(n) {
    if (name.empty()) {
        throw DormitoryException("University name cannot be empty");
    }
}

void University::addDormitory(unique_ptr<Dormitory> dorm) {
    if (!dorm) {
        throw DormitoryException("Null dormitory");
    }
    if (findDormitory(dorm->getName())) {
        throw DuplicateException("Dormitory");
    }
    dormitories.push_back(move(dorm));
}

void University::addStudent(unique_ptr<Student> student) {
    if (!student) {
        throw DormitoryException("Null student");
    }
    if (findStudent(student->getId())) {
        throw DuplicateException("Student");
    }
    students.push_back(move(student));
}

void University::removeStudent(const string& id) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if ((*it)->getId() == id) {
            students.erase(it);
            return;
        }
    }
    throw NotFoundException("Student");
}

Student* University::findStudent(const string& id) {
    if (id.empty()) {
        throw DormitoryException("ID cannot be empty");
    }
    for (auto& s : students) {
        if (s->getId() == id) {
            return s.get();
        }
    }
    return nullptr;
}

Dormitory* University::findDormitory(const string& n) {
    if (n.empty()) {
        throw DormitoryException("Name cannot be empty");
    }
    for (auto& d : dormitories) {
        if (d->getName() == n) {
            return d.get();
        }
    }
    return nullptr;
}

bool University::assignStudentToDorm(const string& studentId, const string& dormName, int roomNumber) {
    Student* s = findStudent(studentId);
    Dormitory* d = findDormitory(dormName);
    
    if (!s) {
        throw NotFoundException("Student");
    }
    if (!d) {
        throw NotFoundException("Dormitory");
    }
    
    return d->assignStudent(s, roomNumber);
}

void University::displayAll() const {
    cout << "University: " << name << endl;
    cout << "Students: " << students.size() << endl;
    for (const auto& d : dormitories) {
        d->displayInfo();
    }
}

void University::displayStudents() const {
    for (const auto& s : students) {
        s->displayInfo();
    }
}

vector<unique_ptr<Dormitory>>& University::getDormitories() {
    return dormitories;
}

vector<unique_ptr<Student>>& University::getStudents() {
    return students;
}

void University::saveData() const {
    saveData("data/");
}

void University::saveData(const string& filepath) const {
    #ifdef _WIN32
        _mkdir(filepath.c_str());
    #else
        mkdir(filepath.c_str(), 0777);
    #endif
    
    ofstream studentFile(filepath + "students.txt");
    if (!studentFile.is_open()) {
        throw DormitoryException("Cannot open students file for writing");
    }
    
    for (const auto& s : students) {
        studentFile << s->getId() << "|"
                    << s->getFullName() << "|"
                    << s->getAcademicYear() << "|"
                    << s->getDormitoryName() << "|"
                    << s->getRoomNumber() << "|"
                    << s->isAccommodated() << "\n";
    }
    studentFile.close();
    cout << "Students saved successfully!\n";
    
    ofstream dormFile(filepath + "dormitories.txt");
    if (!dormFile.is_open()) {
        throw DormitoryException("Cannot open dormitories file for writing");
    }
    
    for (const auto& d : dormitories) {
        dormFile << d->getName() << "|"
                 << d->getCapacity() << "|"
                 << d->getRestaurant().getName() << "\n";
        
        for (const auto& room : d->getRooms()) {
            dormFile << "ROOM|"
                     << room.getRoomNumber() << "|"
                     << room.getCapacity() << "\n";
        }
    }
    dormFile.close();
    cout << "Dormitories saved successfully!\n";
}

void University::loadData() {
    loadData("data/");
}

void University::loadData(const string& filepath) {
    students.clear();
    dormitories.clear();
    
    ifstream studentFile(filepath + "students.txt");
    if (studentFile.is_open()) {
        string line;
        while (getline(studentFile, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string id, name, dormName, roomStr, yearStr, accommodatedStr;
            
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, yearStr, '|');
            getline(ss, dormName, '|');
            getline(ss, roomStr, '|');
            getline(ss, accommodatedStr, '|');
            
            int year = stoi(yearStr);
            int roomNumber = stoi(roomStr);
            bool accommodated = (accommodatedStr == "1");
            
            try {
                unique_ptr<Student> s(new Student(id, name, year));
                if (accommodated && dormName != " ") {
                    s->assignAccommodation(dormName, roomNumber);
                }
                addStudent(move(s));
            } catch (const exception& e) {
                cout << "Error loading student " << id << ": " << e.what() << "\n";
            }
        }
        studentFile.close();
        cout << "Students loaded successfully!\n";
    } else {
        cout << "No student data file found. Starting fresh.\n";
    }
    
    ifstream dormFile(filepath + "dormitories.txt");
    if (dormFile.is_open()) {
        string line;
        while (getline(dormFile, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string type;
            getline(ss, type, '|');
            
            if (type == "ROOM") {
                continue;
            }
            
            string name, restName, capStr;
            getline(ss, name, '|');
            getline(ss, capStr, '|');
            getline(ss, restName, '|');
            
            int capacity = stoi(capStr);
            
            try {
                unique_ptr<Dormitory> d(new Dormitory(name, capacity, restName));
                addDormitory(move(d));
            } catch (const exception& e) {
                cout << "Error loading dormitory " << name << ": " << e.what() << "\n";
            }
        }
        dormFile.close();
        cout << "Dormitories loaded successfully!\n";
    } else {
        cout << "No dormitory data file found. Starting fresh.\n";
    }
}