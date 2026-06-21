#ifndef DORMITORY_EXCEPTION_H
#define DORMITORY_EXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class DormitoryException : public exception {
private:
    string message;
public:
    DormitoryException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class NotFoundException : public DormitoryException {
public:
    NotFoundException(const string& item) 
        : DormitoryException(item + " not found") {}
};

class FullException : public DormitoryException {
public:
    FullException(const string& item) 
        : DormitoryException(item + " is full") {}
};

class DuplicateException : public DormitoryException {
public:
    DuplicateException(const string& item) 
        : DormitoryException(item + " already exists") {}
};

#endif