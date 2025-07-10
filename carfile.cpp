#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include"carfile.h"
//文档按行存储车辆信息，每行格式为：账号 车牌号 车型 颜色 年份
CarFile::CarFile(Car car){
    this->setCarNumber(car.getCarNumber());
    this->setCarType(car.getCarType());
    this->setCarColor(car.getCarColor());
    this->setCarYear(car.getCarYear());
    this->attachUser(car);
}

int CarFile::store(){
    try{
        ifstream fin("car.txt", ios::in);
        if (!fin.is_open()){
            throw runtime_error("录入失败");
        }
        string line;
        string cur_number;
        fin.seekg(0, ios::beg);
        while (getline(fin, line)){
            size_t pos=line.find(' ');
            if(pos != string::npos){
                cur_number=line.substr(pos, line.find(' ', pos + 1) - pos);
                if (cur_number == this->getCarNumber()&& this->getCarNumber()!="default") {
                    cout<<"车辆信息已被录入！"<<endl;
                    return -1; 
                }
            }
        }
        fin.close();
        ofstream fout("car.txt", ios::app);
        if (!fout.is_open()){
            throw runtime_error("录入失败");
        }
        fout<<this->getAccount()<<" "<<this->getCarNumber()<< " "<<this->getCarType()<<" "<<this->getCarColor()<<" "<<this->getCarYear()<<"\n";
        if(this->getCarNumber()!="default"){
            cout << "车辆信息录入成功！" << endl;
        }
        fout.close(); 
        return 1;
    } catch (const exception& e) {
        cerr << "发生异常: " << e.what() << endl;
        return 0;
    }
}
//通过账号获取车辆信息
void CarFile::getinfo(){
    try{
        ifstream fin("car.txt",ios::in);
        if(!fin.is_open()){
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        bool found=0;
        fin.seekg(0, ios::beg);
        while(getline(fin,line)){
            size_t pos=line.find(' ');
            if(pos!=string::npos){
                cur_account=line.substr(0,pos);
                if(cur_account==this->getAccount()){
                    found=1;
                    size_t pos2=line.find(' ',pos+1);
                    if(pos2!=string::npos){
                        this->setCarNumber(line.substr(pos+1,pos2-pos-1));
                        size_t pos3=line.find(' ',pos2+1);
                        if(pos3!=string::npos){
                            this->setCarType(line.substr(pos2+1,pos3-pos2-1));
                            size_t pos4=line.find(' ',pos3+1);
                            if(pos4!=string::npos){
                                this->setCarColor(line.substr(pos3+1,pos4-pos3-1));
                                this->setCarYear(line.substr(pos4+1));
                            }
                        }
                    }
                    break;
                }
            }
        }
        if(!found){
            this->setCarNumber("default");
            this->setCarType("default");
            this->setCarColor("default");
            this->setCarYear("default");
        }
    }
    catch(const exception& e){
        cerr << "发生异常: " << e.what() << endl;
    }
}

void CarFile::updatenumber(string new_number){
    try{
        ifstream fin("car.txt", ios::in);
        ofstream fout("temp.txt", ios::out);
        if (!fin.is_open() || !fout.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        bool found=0;
        while (getline(fin, line)) {
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                cur_account = line.substr(0, pos);
                if (cur_account == this->getAccount()){
                    found=1;
                    line.replace(pos + 1, line.find(' ', pos + 1) - pos - 1, new_number);
                }
            }
            fout << line << endl;
        }
        if(found){
            cout<<"车牌号修改成功！"<<endl;
        }
        else{
            cout<<"车牌号修改失败！车辆不存在"<<endl;
        }
        fin.close();
        fout.close();
        remove("car.txt");
        rename("temp.txt", "car.txt");
    }catch(const exception& e) {
        cerr << "发生异常: " << e.what() << endl;
    }
}

void CarFile::updatetype(string new_type){
    try{
        ifstream fin("car.txt", ios::in);
        ofstream fout("temp.txt", ios::out);
        if (!fin.is_open() || !fout.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        bool found=0;
        while (getline(fin, line)){
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                cur_account = line.substr(0, pos);
                if (cur_account == this->getAccount()){
                    found=1;
                    size_t pos2 = line.find(' ', pos + 1);
                    if (pos2 != string::npos) {
                        line.replace(pos2 + 1, line.find(' ', pos2 + 1) - pos2 - 1, new_type);
                    }
                }
            }
            fout << line << endl;
        }
        if(found){
            cout<<"车型修改成功！"<<endl;
        }
        else{
            cout<<"车型修改失败！车辆不存在"<<endl;
        }
        fin.close();
        fout.close();
        remove("car.txt");
        rename("temp.txt", "car.txt");
    }catch(const exception& e) {
        cerr << "发生异常: " << e.what() << endl;
    }
}

void CarFile::updatecolor(string new_color){
    try{
        ifstream fin("car.txt", ios::in);
        ofstream fout("temp.txt", ios::out);
        if (!fin.is_open() || !fout.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        bool found=0;
        while (getline(fin, line)) {
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                cur_account = line.substr(0, pos);
                if (cur_account == this->getAccount()){
                    found=1;
                    size_t pos2 = line.find(' ', pos + 1);
                    if (pos2 != string::npos){
                        size_t pos3 = line.find(' ', pos2 + 1);
                        if (pos3 != string::npos){
                            line.replace(pos3 + 1, line.find(' ', pos3 + 1) - pos3 - 1, new_color);
                        }
                    }
                }
            }
            fout << line << endl;
        }
        if(found){
            cout<<"颜色修改成功！"<<endl;
        }
        else{
            cout<<"颜色修改失败！车辆不存在"<<endl;
        }
        fin.close();
        fout.close();
        remove("car.txt");
        rename("temp.txt", "car.txt");
    }catch(const exception& e) {
        cerr << "发生异常: " << e.what() << endl;
    }
}

void CarFile::updateyear(string new_year){
    try{
        ifstream fin("car.txt", ios::in);
        ofstream fout("temp.txt", ios::out);
        if (!fin.is_open() || !fout.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        bool found=0;
        while (getline(fin, line)) {
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                cur_account = line.substr(0, pos);
                if (cur_account == this->getAccount()){
                    found=1;
                    size_t pos2 = line.find(' ', pos + 1);
                    if(pos2 != string::npos){
                        size_t pos3 = line.find(' ', pos2 + 1);
                        if(pos3 != string::npos){
                            size_t pos4 = line.find(' ', pos3 + 1);
                            if(pos4 != string::npos){
                                line.replace(pos4+1, line.length() - pos4 - 1, new_year);
                            }
                        }
                    }
                }
            }
            fout << line << endl;
        }
        if(found){
            cout<<"年份修改成功！"<<endl;
        }
        else{
            cout<<"年份修改失败！车辆不存在"<<endl;
        }
        fin.close();
        fout.close();
        remove("car.txt");
        rename("temp.txt", "car.txt");
    }catch(const exception& e){
        cerr << "发生异常: " << e.what() << endl;
    }
}
//打印所有车辆信息
void CarFile::printinfo(){
    try{
        ifstream fin("car.txt",ios::in);
        if(!fin.is_open()){
            throw runtime_error("文件打开失败");
        }
        string line;
        fin.seekg(0, ios::beg);
        if(this->getPermission()){
            cout << left << setw(15) << "用户";
        }
        cout << left << setw(15) << "车牌号" ;
        cout << left << setw(15) << "车型" ;
        cout << left << setw(15) << "颜色" ;
        cout << left << setw(15) << "年份" << endl;
        while(getline(fin,line)){
            size_t pos=line.find(' ');
            string cur_account;
            if(this->getPermission()){
                cur_account = line.substr(0, pos);
                cout << left << setw(15) << cur_account;
            }
            if(pos!=string::npos){
                size_t pos2=line.find(' ',pos+1);
                if(pos2!=string::npos){
                    string car_number=line.substr(pos+1,pos2-pos-1);
                    size_t pos3=line.find(' ',pos2+1);
                    if(pos3!=string::npos){
                        string car_type=line.substr(pos2+1,pos3-pos2-1);
                        size_t pos4=line.find(' ',pos3+1);
                        if(pos4!=string::npos){
                            string car_color=line.substr(pos3+1,pos4-pos3-1);
                            string car_year=line.substr(pos4+1);
                            cout << left << setw(15) << car_number;
                            cout << left << setw(15) << car_type;
                            cout << left << setw(15) << car_color;
                            cout << left << setw(15) << car_year << endl;
                        }
                    }
                }
            }
        }
        fin.close();
    }catch(const exception& e){
        cerr << "发生异常: " << e.what() << endl;
    }
}
//添加车辆信息，其中账号默认为"default"
void CarFile::addcar(string car_number, string car_type, string car_color, string car_year){
    try{
        string line;
        string cur_number;
        bool found=0;
        ifstream fin("car.txt",ios::in);
        if(!fin.is_open()){
            throw runtime_error("文件打开失败");
        }
        while(getline(fin,line)){
            size_t pos=line.find(" ");
            if(pos!=string::npos){
                size_t pos2=line.find(" ",pos+1);
                if(pos2!=string::npos){
                    cur_number=line.substr(pos+1,pos2-pos-1);
                    if(cur_number==car_number){
                        found=1;
                        cout<<"车辆已存在！"<<endl;
                        break;
                    }
                }
            }
        }
        fin.close();
        if(found){
            return;
        }
    }catch(const exception& e) {
        cerr << "发生异常: " << e.what() << endl;
    }
    try{
        ofstream fout("car.txt", ios::app);
        if (!fout.is_open()){
            throw runtime_error("文件打开失败");
        }
        fout<<endl;
        fout<<"default"<<" "<<car_number<<" "<<car_type<<" "<<car_color<<" "<<car_year;
        cout<<"车辆信息添加成功！"<<endl;
        fout.close();
    }catch(const exception& e){
        cerr << "发生异常: "<<e.what()<<endl;
    }
}
//删除车辆信息，根据车牌号进行删除
void CarFile::deletecar(string car_number){
    try{
        ifstream fin("car.txt", ios::in);
        ofstream fout("temp.txt", ios::out);
        if (!fin.is_open() || !fout.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        bool found = false;
        while (getline(fin, line)){
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                string cur_number = line.substr(pos + 1, line.find(' ', pos + 1) - pos - 1);
                if (cur_number == car_number) {
                    found = true;
                    continue;
                }
            }
            fout << line << endl;
        }
        fin.close();
        fout.close();
        if (found) {
            remove("car.txt");
            rename("temp.txt", "car.txt");
            cout << "车辆信息删除成功！" << endl;
        }else{
            remove("temp.txt");
            cout << "未找到指定车牌号的车辆信息！" << endl;
        }
    }catch(const exception& e) {
        cerr << "发生异常: " << e.what() << endl;
    }
}

void CarFile::searchcar(string car_number,string car_type, string car_color, string car_year){
    try{
        ifstream fin("car.txt", ios::in);
        if (!fin.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        bool found = false;
        fin.seekg(0, ios::beg);
        cout << "----------------------------查询结果---------------------------" << endl;
        if(this->getPermission()){
            cout << left << setw(15) << "用户";
        }
        cout << left << setw(15) << "车牌号";
	    cout << left << setw(15) << "车型";
	    cout << left << setw(15) << "颜色";
	    cout << left << setw(15) << "年份" << endl;
        while(getline(fin,line)){
            size_t pos = line.find(' ');
            if (pos != string::npos){
                string cur_account = line.substr(0, pos);
                size_t pos2 = line.find(' ', pos + 1);
                if (pos2 != string::npos){
                    string cur_number = line.substr(pos + 1, pos2 - pos - 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    if(pos3 != string::npos){
                        string cur_type = line.substr(pos2 + 1, pos3 - pos2 - 1);
                        size_t pos4 = line.find(' ', pos3 + 1);
                        if(pos4 != string::npos){
                            string cur_color = line.substr(pos3 + 1, pos4 - pos3 - 1);
                            string cur_year = line.substr(pos4 + 1);
                            bool match = true;
                            if(!car_number.empty() && cur_number != car_number){
                                match = false;
                            }
                            if(!car_type.empty() && cur_type != car_type){
                                match = false;
                            }
                            if(!car_color.empty() && cur_color != car_color){
                                match = false;
                            }
                            if(!car_year.empty() && cur_year != car_year){
                                match = false;
                            }
                            if(match){
                                found = true;
                                if(this->getPermission()){
                                    cout << left << setw(15) << cur_account;
                                }
                                cout << left << setw(15) << cur_number;
                                cout << left << setw(15) << cur_type;
                                cout << left << setw(15) << cur_color;
                                cout << left << setw(15) << cur_year << endl;
                            }
                        }
                    }
                }
            }
        }
        if(!found){
            cout<< "未找到匹配的车辆信息！"<<endl;
        }
        fin.close();
    }catch (const exception& e){
        cerr<<"发生异常: "<<e.what()<<endl;
    }
}