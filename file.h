#ifndef FILE_H
#define FILE_H

#include<iostream>
#include<string>

class File{
    public:
        virtual int store()=0;
        virtual void getinfo()=0;
        virtual void printinfo()=0;
        virtual ~File(){};
};
#endif