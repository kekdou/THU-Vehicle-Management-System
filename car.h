#ifndef CAR_H
#define CAR_H
#include"user.h"

using namespace std;

class Car:public User{
    private:
        string car_number; //车牌号
        string car_type;   //车型
        string car_color;  //颜色
        string car_year;   //年份
    public:
        Car(string car_number="default", string car_type="default", string car_color="default", string car_year="default");
        void attachUser(User user);
        string getCarNumber()const;
        string getCarType()const;
        string getCarColor()const;
        string getCarYear()const;
        void setCarNumber(string number);
        void setCarType(string type);
        void setCarColor(string color) ;
        void setCarYear(string year);
        friend ostream& operator<<(ostream& os,const Car& car);
};
#endif