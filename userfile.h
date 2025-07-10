#ifndef USERFILE_H
#define USERFILE_H
#include"user.h"
#include"file.h"

class UserFile:public User,public File{
    public:
        UserFile(User user);
        int store();
        int verification();
        void getinfo();
        void updatepassword(string password);
        void updatename(string name);
        void updatepermission(int permission);
        void printinfo();
        void searchuser(string account="default", string name="default");
};
#endif