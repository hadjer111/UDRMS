#ifndef RESTAURANT_H
#define RESTAUTANT_H

#include <iostream>
#include <string>
#include "DormitoryException.h"

using namespace std;

class Restaurant {
private:
    string name;
    string breakfast;
    string lunch;
    string dinner;
    int mealServedToday;
    
public:
    Restaurant();
    Restaurant(const string& name);
    
    void setName(const string& name);
    void setMenu(const string& breakfast, const string& lunch, const string& dinner);
    
    string getName() const;
    string getBreakfast() const;
    string getLunch() const;
    string getDinner() const;
    void displayMenu() const;
    
    void serveMeal();
    int getMealServedToday() const;
    void resetMealServed();
};

#endif