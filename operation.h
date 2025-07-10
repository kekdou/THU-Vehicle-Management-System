#ifndef OPERATION_H
#define OPERATION_H
#include"userfile.h"
#include"carfile.h"

using namespace std;

class Operation{
    private:
        void start();
        void login();
        void registerUser();
        void ord_menu(User user);
        void admin_menu(User user);
        void info_menu(User user);
        void car_menu(User user);
        void modify_info_menu(User user);
        void modify_car_menu(User user);
        void info_manage_menu(User user);
        void car_manage_menu(User user);
        void car_manage_menu2(User user);
        void car_manage_menu3(User user);
    public:
        int choice;
        void run();
};
#endif
