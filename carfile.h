#ifndef CARFILE_H
#define CARFILE_H
#include"car.h"

class CarFile:public Car{
    public:
        CarFile(Car car);
        int store();
        void getinfo();
        void updatenumber(string new_number);
        void updatetype(string new_type);
        void updatecolor(string new_color);
        void updateyear(string new_year);
        void printinfo();
        void addcar(string car_number, string car_type, string car_color, string car_year);
        void deletecar(string car_number);
        void searchcar(string car_number="default", string car_type="defult", string car_color="default", string car_year="default");
};
#endif