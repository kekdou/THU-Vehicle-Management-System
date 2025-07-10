#ifndef USER_H
#define USER_H
#include<string>
#include<iostream>

using namespace std;

class User{
    private:
        string name;
        string password;
        string account;
        int permission;
    public:
        User(string name="default",string password="",string account="",int permission=0);
        string getName()const;
        string getPassword()const;
        string getAccount()const;
        int getPermission()const;
        void setName(string name);
        void setPassword(string password);
        void setAccount(string account);
        void setPermission(int permission);
        friend ostream& operator<<(ostream& os,const User& user);
};
#endif