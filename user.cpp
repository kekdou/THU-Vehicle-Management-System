#include"user.h"
#include<iostream>
#include<string>

User::User(string name, string password, string account, int permission) {
    this->name = name;
    this->password = password;
    this->account = account;
    this->permission = permission;
}

string User::getName()const{
    return name;
}

string User::getPassword()const{
    return password;
}

string User::getAccount()const{
    return account;
}

int User::getPermission()const{
    return permission;
}

void User::setName(string name) {
    this->name = name;
}

void User::setPassword(string password) {
    this->password = password;
}

void User::setAccount(string account) {
    this->account = account;
}

void User::setPermission(int permission) {
    this->permission = permission;
}

ostream& operator<<(ostream& os, const User& user){
    os<<"账号："<<user.getAccount()<<endl;
    os<<"昵称："<<user.getName()<<endl;
    if(user.permission==0){
        os<<"权限"<<"普通用户"<<endl;
    }else{
        os<<"权限"<<"管理员"<<endl;
    }
    return os;
}