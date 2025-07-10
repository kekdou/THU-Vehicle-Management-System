#include"car.h"

Car::Car(string car_number, string car_type, string car_color, string car_year): User("default", "default", "default", 0){
    this->car_number = car_number;
    this->car_type = car_type;
    this->car_color = car_color;
    this->car_year = car_year;
}

void Car::attachUser(User user) {
    this->setName(user.getName());
    this->setPassword(user.getPassword());
    this->setAccount(user.getAccount());
    this->setPermission(user.getPermission());
}

string Car::getCarNumber()const{
    return car_number;
}

string Car::getCarType()const{
    return car_type;
}

string Car::getCarColor()const{
    return car_color;
}

string Car::getCarYear()const{
    return car_year;
}

void Car::setCarNumber(string number) {
    this->car_number = number;
}

void Car::setCarType(string type) {
    this->car_type = type;
}

void Car::setCarColor(string color) {
    this->car_color = color;
}

void Car::setCarYear(string year) {
    this->car_year = year;
}

ostream& operator<<(ostream& os, const Car& car){
    os<<"车牌号："<<car.getCarNumber()<<endl;
    os<<"车型："<<car.getCarType()<<endl;
    os<<"颜色："<<car.getCarColor()<<endl;
    os<<"年份："<<car.getCarYear()<<endl;
    return os;
}