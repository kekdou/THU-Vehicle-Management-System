#include"userfile.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
//文档按行存储用户信息，每行格式为：账号 密码 姓名 权限
//权限：0-普通用户，1-管理员
//构造函数，将User对象的属性赋值给UserFile对象
UserFile::UserFile(User user){
    this->setName(user.getName());
    this->setPassword(user.getPassword());
    this->setAccount(user.getAccount());
    this->setPermission(user.getPermission());
}
//将每一个注册过的用户信息储存到文件
//若账号已存在，则返回-1
//若注册成功，则返回1
//若文件打开失败，则返回0
int UserFile::store(){
    try{
        ifstream fin("user.txt", ios::in);
        if (!fin.is_open()) {
            throw runtime_error("注册失败\n");
        }
        string line;
        string cur_account;
        fin.seekg(0,ios::beg);
        while(getline(fin, line)){
            size_t pos=line.find(' ');     //找到第一个空格的位置
            if(pos != string::npos){         //如果找到了空格
                cur_account = line.substr(0, pos);        //提取账号
                if(cur_account == this->getAccount()){
                    cout<<"账号已被注册！"<<endl;
                    return -1; 
                }
            }
        }
        fin.close();
    } catch (const exception& e){
        cerr << "发生异常: " << e.what() << endl;
        return 0; // 返回0表示文件打开失败
    }
    try{
        ofstream fout("user.txt", ios::app);
        if (!fout.is_open()) {
            throw runtime_error("注册失败\n");
        }
        fout<<this->getAccount()<<" "<<this->getPassword()<<" "<<this->getName()<<" "<<this->getPermission()<<"\n";
        fout.close();
        cout<<"注册成功！"<<endl;
        return 1;
    }catch(const exception& e){
        cerr << "发生异常: " << e.what() << endl;
        return 0; // 返回0表示文件打开失败
    }
}
//检查用户登录
//若账号不存在，则返回-1
//若账号存在但密码错误，则返回0
//若账号存在且密码正确，则返回1
int UserFile::verification(){
    try{
        ifstream fin("user.txt", ios::in);
        if (!fin.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        string cur_password;
        fin.seekg(0, ios::beg);
        while(getline(fin, line)){
            size_t pos = line.find(' ');     //找到第一个空格的位置
            if(pos != string::npos){         //如果找到了空格
                cur_account = line.substr(0, pos);        //提取账号
                if(cur_account == this->getAccount()){
                    size_t pos2 = line.find(' ', pos + 1); //找到第二个空格的位置
                    if(pos2 != string::npos){ //如果找到了第二个空格
                        cur_password = line.substr(pos + 1, pos2 - pos - 1); //提取密码
                        if(cur_password == this->getPassword()){
                            return 1; //密码正确
                        } else {
                            return 0; //密码错误
                        }
                    }
                }
            }
        }
        fin.close();
        return -1;
    } catch (const exception& e) {
        cerr<<"发生异常: "<<e.what()<<endl;
        return -1; // 返回-1表示文件打开失败
    }
}
//绑定用户信息
//从文件中读取用户信息，并设置到UserFile对象中
//通过账号查找对应的用户信息
void UserFile::getinfo(){
    try{
        ifstream fin("user.txt", ios::in);
        if (!fin.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        string cur_password;
        string cur_name;
        int cur_permission;
        fin.seekg(0, ios::beg);
        while(getline(fin, line)){
            size_t pos=line.find(' ');
            if(pos!=string::npos){
                cur_account=line.substr(0,pos);
                if(cur_account==this->getAccount()){
                    size_t pos2=line.find(' ',pos+1);
                    if(pos2!=string::npos){
                        cur_password=line.substr(pos+1,pos2-pos-1);;
                        size_t pos3=line.find(' ',pos2+1);
                        if(pos3!=string::npos){
                            cur_name=line.substr(pos2+1,pos3-pos2-1);
                            cur_permission=stoi(line.substr(pos3+1));
                        }
                    }
                    this->setPassword(cur_password);
                    this->setName(cur_name);
                    this->setPermission(cur_permission);
                    fin.close();
                    break;
                }
            }
        } 
    }catch(const exception& e){
        cerr << "发生异常: " << e.what() << endl;
    }
}
//更新用户密码
void UserFile::updatepassword(string new_password){
    try{
        ifstream fin("user.txt", ios::in);
        ofstream fout("temp.txt", ios::out);
        if (!fin.is_open() || !fout.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        while (getline(fin, line)) {
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                cur_account = line.substr(0, pos);
                if (cur_account == this->getAccount()) {
                    size_t pos2 = line.find(' ', pos + 1);
                    if (pos2 != string::npos) {
                        line.replace(pos + 1, pos2 - pos - 1, new_password);
                    }
                }
            }
            fout << line << endl;
        }
        fin.close();
        fout.close();
        remove("user.txt");
        rename("temp.txt", "user.txt");
    }catch(const exception& e){
        cerr << "发生异常: " << e.what() << endl;
    }
}
//更新用户名
void UserFile::updatename(string new_name){
    try {
        ifstream fin("user.txt", ios::in);
        ofstream fout("temp.txt", ios::out);
        if (!fin.is_open() || !fout.is_open()){
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        while (getline(fin, line)){
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                cur_account = line.substr(0, pos);
                if (cur_account == this->getAccount()) {
                    size_t pos2 = line.find(' ', pos + 1);
                    if (pos2 != string::npos) {
                        size_t pos3 = line.find(' ', pos2 + 1);
                        if (pos3 != string::npos) {
                            line.replace(pos2 + 1, pos3 - pos2 - 1, new_name);
                        }
                    }
                }
            }
            fout << line << endl;
        }
        fin.close();
        fout.close();
        remove("user.txt");
        rename("temp.txt", "user.txt");
    }catch(const exception& e){
        cerr << "发生异常: " << e.what() << endl;
    }
}
//更新用户权限
//先不写
void UserFile::updatepermission(int new_permission){
    try{
        ifstream fin("user.txt",ios::in);
        ofstream fout("temp.txt", ios::out);
        if (!fin.is_open() || !fout.is_open()){
            throw runtime_error("文件打开失败");
        }
        string line;
        string cur_account;
        while (getline(fin, line)){
            size_t pos = line.find(' ');
            if (pos != string::npos) {
                cur_account = line.substr(0, pos);
                if (cur_account == this->getAccount()) {
                    size_t pos2 = line.find(' ', pos + 1);
                    if (pos2 != string::npos) {
                        size_t pos3 = line.find(' ', pos2 + 1);
                        if (pos3 != string::npos) {
                            line.replace(pos3 + 1, line.length() - pos3 - 1, to_string(new_permission));
                        }
                    }
                }
            }
            fout << line << endl;
        }
        fin.close();
        fout.close();
        remove("user.txt");
        rename("temp.txt", "user.txt");
    }catch(const exception& e){
        cerr << "发生异常: " << e.what() << endl;
    }
}

void UserFile::printinfo(){
    try{
        ifstream fin("user.txt",ios::in);
        if(!fin.is_open()){
            throw runtime_error("文件打开失败");
        }
        string line;
        fin.seekg(0, ios::beg);
        cout<<left<<setw(15)<<"账号";
        cout<<left<<setw(15)<<"密码" ;
        cout<<left<<setw(15)<<"昵称" ;
        cout<<left<<setw(15)<<"权限" <<endl;
        while(getline(fin,line)){
            size_t pos=line.find(' ');
            string cur_account;
            cur_account = line.substr(0, pos);
            if(pos!=string::npos){
                size_t pos2=line.find(' ',pos+1);
                if(pos2!=string::npos){
                    string cur_password=line.substr(pos+1,pos2-pos-1);
                    size_t pos3=line.find(' ',pos2+1);
                    if(pos3!=string::npos){
                        string cur_name=line.substr(pos2+1,pos3-pos2-1);
                        string cur_permission=line.substr(pos3+1, line.length() - pos3 - 1);
                        cout<<left<<setw(15)<<cur_account;
                        cout<<left<<setw(15)<<cur_password;
                        cout<<left<<setw(15)<<cur_name;
                        if(cur_permission=="0"){
                            cout<<left<<setw(15)<<"普通用户"<<endl;
                        } 
                        else{
                            cout<<left<<setw(15)<<"管理员"<<endl;
                        }
                    }
                }
            }
        }
        fin.close();
    }catch(const exception& e){
        cerr<<"发生异常: "<<e.what()<<endl;
    }
}

void UserFile::searchuser(string account,string name){
    try{
        ifstream fin("user.txt", ios::in);
        if (!fin.is_open()) {
            throw runtime_error("文件打开失败");
        }
        string line;
        bool found = false;
        fin.seekg(0, ios::beg);
        cout << "----------------------------查询结果---------------------------" << endl;
        cout << left << setw(15) << "账号";
        cout << left << setw(15) << "密码";
        cout << left << setw(15) << "昵称";
        cout << left << setw(15) << "权限" << endl;
        while(getline(fin,line)){
            size_t pos = line.find(' ');
            if (pos != string::npos){
                string cur_account = line.substr(0, pos);
                size_t pos2 = line.find(' ', pos + 1);
                if (pos2 != string::npos){
                    string cur_password = line.substr(pos + 1, pos2 - pos - 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    if(pos3 != string::npos){
                        string cur_name = line.substr(pos2 + 1, pos3 - pos2 - 1);
                        string cur_permission = line.substr(pos3+1);
                        bool match = true;
                        if(!account.empty() &&cur_account!=account){
                            match = false;
                        }
                        if(!name.empty()&&cur_name!=name){
                            match = false;
                        }
                        if(match){
                            found = true;
                            cout<<left<<setw(15)<<cur_account;
                            cout<<left<<setw(15)<<cur_password;
                            cout<<left<<setw(15)<<cur_name;
                            if(cur_permission=="0"){
                                cout<<left<<setw(15)<<"普通用户"<<endl;
                            } 
                            else{
                                cout<<left<<setw(15)<<"管理员"<<endl;
                            } 
                        }
                    }
                }
            }
        }
        if(!found){
            cout<<"未找到匹配的用户信息！"<<endl;
        }
        fin.close();
    }catch (const exception& e){
        cerr<<"发生异常: "<<e.what()<<endl;
    }
}