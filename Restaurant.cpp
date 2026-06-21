#include "Restaurant.h"
#include <iostream>
using namespace std;

Restaurant::Restaurant() : name(" "), breakfast(" "), lunch(" "), dinner(" "), mealServedToday(0) {}

Restaurant::Restaurant(const string& n) : name(n), breakfast(" "), lunch(" "), dinner(" "), mealServedToday(0) {
    if (name.empty()) {
        throw DormitoryException("Restaurant name cannot be empty");
    }
}

void Restaurant::setName(const string& n) {
    if (n.empty()) {
        throw DormitoryException("Name cannot be empty");
    }
    name = n;
}

void Restaurant::setMenu(const string& b, const string& l, const string& d) {
    if (b.empty() || l.empty() || d.empty()) {
        throw DormitoryException("All meals must be set");
    }
    breakfast = b;
    lunch = l;
    dinner = d;
}

string Restaurant::getName() const {
    return name;
}

string Restaurant::getBreakfast() const {
    return breakfast;
}

string Restaurant::getLunch() const {
    return lunch;
}

string Restaurant::getDinner() const {
    return dinner;
}

void Restaurant::displayMenu() const {
    cout << "=====================\n";
    cout << " Restaurant: " << name << endl;
    cout << "==== MENU====\n";
    cout << " Breakfast: " << (breakfast.empty() ? "Not set" : breakfast) << endl;
    cout << " Lunch: " << (lunch.empty() ? "Not set" : lunch) << endl;
    cout << " Dinner: " << (dinner.empty() ? "Not set" : dinner) << endl;
    cout << " Meals served: " << mealServedToday << endl;
    cout << "=====================\n";
}

void Restaurant::serveMeal() {
    if (breakfast.empty() || lunch.empty() || dinner.empty()) {
        throw DormitoryException("Menu not fully set");
    }
    mealServedToday++;
}

int Restaurant::getMealServedToday() const {
    return mealServedToday;
}

void Restaurant::resetMealServed() {
    mealServedToday = 0;
}