#include<iostream>
#include"operation.h"

void Operation::start(){
    cout<<"******************车辆管理系统*****************"<<endl;
	cout<< "1.注册账号" << endl;
	cout<< "2.登录账号" << endl;
	cout<< "3.退出" << endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin>>choice;
    if(cin.good()){
        switch(choice){
            case 1:
                this->registerUser();
                break;
            case 2:
                this->login();
                break;
            case 3:
                cout<<"感谢使用车辆管理系统，再见！"<<endl;
                exit(0);
            default:
                cout<<"无效的选择，请重新输入！"<<endl;
                this->start();
        }
    }else{
        cin.clear(); 
        cin.ignore();
        choice = -1;
        cout<<"输入无效，请重新输入！"<<endl;
        this->start();
    }
}

void Operation::registerUser(){
    cout<<"********************账号注册********************"<<endl;
    cout<<"1.开始注册"<<endl;
    cout<<"2.返回上一级"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin>>choice;
    if(choice==1){
        string account,password,name, confirm_password;
        cout<<"********************账号注册********************"<<endl;
        cout<<"请输入账号(输入quit退出注册):";
        cin >> account;
        if(account == "quit"){
            cout<<"注册已取消！"<<endl;
            this->registerUser();
            return;
        }
        while(true){
            cout<<"请输入密码(输入quit退出注册):";
            cin>>password;
            if(password == "quit"){
                cout<<"注册已取消！"<<endl;
                this->registerUser();
                return;
            }
            cout<<"请再次输入密码(输入quit退出注册):";
            cin>>confirm_password;
            if(confirm_password == "quit"){
                cout<<"注册已取消！"<<endl;
                this->registerUser();
                return;
            }
            if(password!=confirm_password){
                cout<<"两次输入的密码不一致，请重新输入！"<<endl;
                continue;
            }
            else{
                break;
            }
        }
        User user("default", password, account, 0);
        UserFile userfile(user);
        int result=userfile.store();
        switch(result){
            case -1:{
                this->registerUser();
                break;
            }
            case 0:{
                this->registerUser();
                break;
            }
            case 1:{
                cout<<"取一个响亮的名字吧！"<<endl;
                while(1){
                    cout<<"请输入您的昵称(输入quit退出注册):";
                    cin>>name;
                    if(cin.good()&&!name.empty()){
                        userfile.setName(name);
                        userfile.updatename(name);
                        int choice2;
                        string car_number="default";
                        string car_type="default";
                        string car_color="default";
                        string car_year="default";
                        while(true){
                            cout<<"****************是否绑定车辆信息****************"<<endl;
                            cout<<"1.是"<<endl;
                            cout<<"2.否"<<endl;
                            cout<<"***********************************************"<<endl;
                            cout<<"请输入您的选择：";
                            cin>>choice2;
                            if(choice2==1){
                                cout<<"请输入车辆信息："<<endl;
                                cout<<"车牌号:";
                                cin>>car_number;
                                cout<<"车型:";
                                cin>>car_type;
                                cout<<"颜色:";
                                cin>>car_color;
                                cout<<"年份:";
                                cin>>car_year;
                            }
                            Car car(car_number, car_type, car_color, car_year);
                            car.attachUser(user);
                            CarFile carfile(car);
                            int result=carfile.store();
                            if(result==1){
                                cout<<"车辆信息绑定成功！"<<endl;
                                this->ord_menu(userfile);
                                return;
                            }
                            else{
                                cout<<"车辆信息绑定失败，请重试！"<<endl;
                            }
                        }
                    }
                    else{
                        cin.clear(); 
                        cin.ignore();
                        cout<<"昵称不能为空，请重新输入！"<<endl;
                    }
                }
                this->start();
                break;
            }
            default:{
                cout<<"注册失败，请重试！"<<endl;
                this->registerUser();
                break;
            }
        }
    }
    else if(choice==2){
        this->start();
    }
    else{
        cout<<"无效的选择，请重新输入！"<<endl;
        this->registerUser();
    }
}

void Operation::login(){
    cout<<"********************账号登录********************"<<endl;
    cout<<"1.开始登录"<<endl;
    cout<<"2.忘记密码"<<endl;
    cout<<"3.返回上一级"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin>>choice;
    if(choice==1){
        string account, password;
        cout<<"********************账号登录********************"<<endl;
        cout<<"请输入账号(输入quit退出登录):";
        cin>>account;
        if(account=="quit"){
            cout<<"登录已取消！"<<endl;
            this->login();
            return;
        }
        cout<<"请输入密码(输入quit退出登录):";
        cin>>password;
        if(password == "quit"){
            cout<<"登录已取消！"<<endl;
            this->login();
            return;
        }
        User user("default", password, account, 0);
        UserFile userfile(user);
        int result = userfile.verification();
        switch(result){
            case -1:{
                cout<<"账号不存在，请先注册！"<<endl;
                this->start();
                break;
            }
            case 0:{
                while(true){
                    cout<<"密码错误，请重新输入！";
                    cout<<"(输入quit退出登录)"<<endl;
                    cout<< "请输入密码：";
                    cin>>password;
                    if(password == "quit"){
                        cout<<"登录已取消！"<<endl;
                        this->login();
                        return;
                    }
                    user.setPassword(password);
                    userfile.setPassword(password);
                    result = userfile.verification();
                    if(result==1){
                        cout<<"登录成功！欢迎使用车辆管理系统！"<<endl;
                        cout<<"******************车辆管理系统*****************"<<endl;
                        userfile.getinfo();
                        if(userfile.getPermission()==0){
                            cout<<"您好！"<<userfile.getName()<<endl;
                            this->ord_menu(userfile);
                            return;
                        }
                        if(userfile.getPermission()==1){
                            cout<<"您好！"<<userfile.getName()<<endl;
                            this->admin_menu(userfile);
                            return;
                        }
                    }
                }
                this->login();
                break;
            }
            case 1:{
                cout<<"登录成功！欢迎使用车辆管理系统！"<<endl;
                userfile.getinfo();
                cout<<"******************车辆管理系统*****************"<<endl;
                if(userfile.getPermission()==0){
                    cout<<"您好！"<<userfile.getName()<<endl;
                    this->ord_menu(userfile);
                    return;
                }
                if(userfile.getPermission()==1){
                    cout<<"您好！"<<userfile.getName()<<endl;
                    this->admin_menu(userfile);
                    return;
                }
                break;
            }
            default:{
                cout<<"登录失败，请重试！"<<endl;
                this->login();
                break;
            }
        }
    }
    else if(choice==2){
        cout<<"********************找回密码********************"<<endl;
        cout<<"请联系管理员查看密码"<<endl;
        cout<<"管理员联系方式："<<endl;
        cout<<"QQ:123456789"<<endl;
        cout<<"微信:123456789"<<endl;
        cout<<"邮箱:123456789@gly.com"<<endl;
        cout<<"电话:123456789"<<endl;
        cout<<"希望能尽快解决您的问题！"<<endl;
        this->start();
        return;
    }
    else if(choice==3){
        this->start();
        return;
    }
    else{
        cout<<"无效的选择，请重新输入！"<<endl;
        this->login();
        return;
    }
}

void Operation::modify_info_menu(User user){
    cout<<"******************修改个人信息******************"<<endl;
    cout<<"1.修改昵称"<<endl;
    cout<<"2.修改密码"<<endl;
    cout<<"3.返回上一级"<<endl;
    cout<<"4.返回主页"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin>>choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                cout<<"********************修改昵称********************"<<endl;
                cout<<"当前昵称："<<user.getName()<<endl;
                while(1){
                    string new_name;
                    cout<<"请输入新的昵称(输入quit退出修改):";
                    cin>>new_name;
                    if(new_name=="quit"){
                        cout<<"修改昵称已取消！"<<endl;
                        this->modify_info_menu(user);
                        return;
                    }
                    if(!new_name.empty()){
                        user.setName(new_name);
                        UserFile userfile(user);
                        userfile.updatename(new_name);
                        cout<<"昵称修改成功！"<<endl;
                        break;
                    }
                    else{
                        cout<<"昵称不能为空，请重新输入！"<<endl;
                    }
                }
                this->modify_info_menu(user);
                break;
            }
            case 2:{
                cout<<"********************修改昵称********************"<<endl;
                string cur_password,new_password, confirm_password;
                while(true){
                    cout<<"请输入原密码(输入quit退出修改):";
                    cin>>cur_password;
                    if(cur_password=="quit"){
                        cout<<"修改密码已取消！"<<endl;
                        this->modify_info_menu(user);
                        return;
                    }
                    UserFile userfile(user);
                    if(cur_password==userfile.getPassword()){
                        break;
                    }
                    else{
                        cout<<"原密码错误，请重新输入！"<<endl;
                        continue;
                    }
                }
                while(true){
                    cout<<"请输入新的密码(输入quit退出):";
                    cin>>new_password;
                    if(new_password=="quit"){
                        cout<<"修改密码已取消！"<<endl;
                        this->modify_info_menu(user);
                        return;
                    }
                    cout<<"请再次输入新的密码(输入quit退出):";
                    cin>>confirm_password;
                    if(confirm_password=="quit"){
                        cout<<"修改密码已取消！"<<endl;
                        this->modify_info_menu(user);
                        return;
                    }
                    if(new_password!=confirm_password){
                        cout<<"两次输入的密码不一致，请重新输入！"<<endl;
                        continue;
                    }
                    else{
                        break;
                    }
                }
                user.setPassword(new_password);
                UserFile userfile(user);
                userfile.updatepassword(new_password);
                cout<<"密码修改成功！"<<endl;
                this->modify_info_menu(user);
                break;
            }
            case 3:{
                this->info_menu(user);
                break;
            }
            case 4:{
                if(user.getPermission()==1){
                    this->admin_menu(user);
                    break;
                }
                else{
                    this->ord_menu(user);
                    break;
                }
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->modify_info_menu(user);
                break;
            }
        }
    }
    else{
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->modify_info_menu(user);
    }
}

void Operation::info_menu(User user){
    cout<<"********************个人信息********************"<<endl;
    cout<<"1.查询个人信息"<<endl;
    cout<<"2.修改个人信息"<<endl;
    cout<<"3.返回上一级"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin >> choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                cout<<"******************查询个人信息******************"<<endl;
                cout<<user;
                this->info_menu(user);
                break;
            }
            case 2:{
                this->modify_info_menu(user);
                break;
            }
            case 3:{
                if(user.getPermission() == 1){
                    this->admin_menu(user);
                    break;
                }
                else{
                    this->ord_menu(user);
                    break;
                }
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->info_menu(user);
                break;
            }
        }
    }
    else{
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->info_menu(user);
    }
}

void Operation::car_menu(User user){
    cout<<"********************车辆信息********************"<<endl;
    cout<<"1.我的车"<<endl;
    cout<<"2.车辆列表"<<endl;
    cout<<"3.车辆查询"<<endl;
    cout<<"4.返回上一级"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin>>choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                cout<<"********************车辆信息********************"<<endl;
                Car car("default", "default", "default", "default");
                car.attachUser(user);
                CarFile carfile(car);
                carfile.getinfo();
                cout<<carfile;
                this->car_menu(user);
                break;
            }
            case 2:{
                cout<<"********************车辆列表********************"<<endl;
                Car car("default", "default", "default", "default");
                car.attachUser(user);
                CarFile carfile(car);
                carfile.printinfo();
                this->car_menu(user);
                break;
            }
            case 3:{
                cout<<"********************车辆查询********************"<<endl;
                string car_number, car_type, car_color, car_year;
                while(1){
                    cout<<"请输入车辆相关信息"<<endl;
                    cout<<"输入请按照 车牌号——车型——颜色——年份 顺序输入(输入enter跳过该关键词):"<<endl;
                    cin.ignore();
                    getline(cin, car_number);
                    getline(cin, car_type);
                    getline(cin, car_color);
                    getline(cin, car_year);
                    Car car("default", "default", "default", "default");
                    car.attachUser(user);
                    CarFile carfile(car);
                    carfile.searchcar(car_number, car_type, car_color, car_year);
                    int choice2;
                    cout<<"******************是否继续查询******************"<<endl;
                    cout<<"1.继续查询"<<endl;
                    cout<<"2.返回上一级"<<endl;
                    cout<<"***********************************************"<<endl;
                    cout<<"请输入您的选择：";
                    cin>>choice2;
                    if(choice2==1){
                        continue;
                    }
                    else{
                        this->car_menu(user);
                        return;
                    }
                }
            }
            case 4:{
                if(user.getPermission() == 1){
                    this->admin_menu(user);
                    break;
                }
                else{
                    this->ord_menu(user);
                    break;
                }
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->car_menu(user);
                break;
            }
        }
    } else {
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->car_menu(user);
    }

}

void Operation::ord_menu(User user){
    cout<<"********************用户菜单********************" << endl;
    cout<<"1.查询个人信息"<<endl;
    cout<<"2.查询车辆信息"<<endl;
    cout<<"3.成为管理员"<<endl;
    cout<<"4.退出登录"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin >> choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                this->info_menu(user);
                break;
            }
            case 2:{
                this->car_menu(user);
                break;
            }
            case 3:{
                cout<<"*****************成为管理员*****************"<<endl;
                while(1){
                    cout<<"请输入管理员密钥(输入quit退出):";
                    string key;
                    cin>>key;
                    if(key=="quit"){
                        cout<<"操作已取消..."<<endl;
                        this->ord_menu(user);
                        return;
                    }
                    if(key=="admin123"){
                        cout<<"密钥正确，正在成为管理员..."<<endl;
                        user.setPermission(1);
                        UserFile userfile(user);
                        userfile.updatepermission(1);
                        cout<<"恭喜您，成为管理员！"<<endl;
                        this->admin_menu(userfile);
                        return;
                    }
                    else{
                        cout<<"密钥错误!"<<endl;
                        continue;
                    }
                }
                break;
            }
            case 4:{
                cout << "感谢使用车辆管理系统，再见！" << endl;
                this->start();
                break;
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->ord_menu(user);
                break;
            }
        }
    }
    else{
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->ord_menu(user);
    }
}

void Operation::info_manage_menu(User user){
    cout<<"******************用户信息管理******************"<<endl;
    cout<<"1.用户列表"<<endl;
    cout<<"2.用户查询"<<endl;
    cout<<"3.返回上一级"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin >> choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                cout<<"********************用户列表********************"<<endl;
                UserFile userfile(user);
                userfile.printinfo();
                this->info_manage_menu(user);
                break;
            }
            case 2:{
                cout<<"********************用户查询********************"<<endl;
                string cur_account, cur_name;
                while(1){
                    cout<<"请输入用户相关信息"<<endl;
                    cout<<"输入请按照 账号——昵称 顺序输入(输入enter跳过该关键词):"<<endl;
                    cin.ignore();
                    getline(cin, cur_account);
                    getline(cin, cur_name);
                    UserFile userfile(user);
                    userfile.searchuser(cur_account, cur_name);
                    int choice2;
                    cout<<"******************是否继续查询******************"<<endl;
                    cout<<"1.继续查询"<<endl;
                    cout<<"2.返回上一级"<<endl;
                    cout<<"***********************************************"<<endl;
                    cout<<"请输入您的选择：";
                    cin>>choice2;
                    if(choice2==1){
                        continue;
                    }
                    else{
                        this->info_manage_menu(user);
                        return;
                    }
                }
                break;
            }
            case 3:{
                this->admin_menu(user);
                break;
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->info_manage_menu(user);
                break;
            }
        }
    }else{
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->info_manage_menu(user);
    }
}

void Operation::car_manage_menu3(User user){
    cout<<"********************修改车辆********************"<<endl;
    cout<<"1.修改车牌号"<<endl;
    cout<<"2.修改车型"<<endl;
    cout<<"3.修改颜色"<<endl;
    cout<<"4.修改年份"<<endl;
    cout<<"5.返回上一级"<<endl;
    cout<<"6.返回主页"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin >> choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                cout<<"*******************修改车牌号*******************"<<endl;
                string new_number,account;
                cout<<"请输入需要修改的用户账号(输入quit退出修改):";
                cin >> account;
                if(account == "quit"){
                    cout << "修改车牌号已取消！"<<endl;
                    this->car_manage_menu3(user);
                    return;
                }
                cout<<"请输入新的车牌号(输入quit退出修改):";
                cin >> new_number;
                if(new_number == "quit"){
                    cout << "修改车牌号已取消！"<<endl;
                    this->car_manage_menu3(user);
                    return;
                }
                Car car("default", "default", "default", "default");
                car.attachUser(User("default", "default", account, 0));
                CarFile carfile(car);
                carfile.updatenumber(new_number);
                this->car_manage_menu3(user);
                break;
            }
            case 2:{
                cout<<"********************修改车型********************"<<endl;
                string new_type,account;
                cout<<"请输入需要修改的用户账号(输入quit退出修改):";
                cin>>account;
                if(account == "quit"){
                    cout << "修改车牌号已取消！"<<endl;
                    this->car_manage_menu3(user);
                    return;
                }
                cout<<"请输入新的车型(输入quit退出修改):";
                cin>>new_type;
                if(new_type == "quit"){
                    cout<<"修改车型已取消！"<<endl;
                    this->car_manage_menu3(user);
                    return;
                }
                Car car("default", "default", "default", "default");
                car.attachUser(User("default", "default", account, 0));
                CarFile carfile(car);
                carfile.updatetype(new_type);
                this->car_manage_menu3(user);
                break;
            }
            case 3:{
                cout<<"********************修改颜色********************"<<endl;
                string new_color,account;
                cout<<"请输入需要修改的用户账号(输入quit退出修改):";
                cin>>account;
                if(account == "quit"){
                    cout << "修改颜色已取消！"<<endl;
                    this->car_manage_menu3(user);
                    return;
                }
                cout<<"请输入新的颜色(输入quit退出修改):";
                cin>>new_color;
                if(new_color == "quit"){
                    cout<<"修改颜色已取消！"<<endl;
                    this->car_manage_menu3(user);
                    return;
                }
                Car car("default", "default", "default", "default");
                car.attachUser(User("default", "default", account, 0));
                CarFile carfile(car);
                carfile.updatecolor(new_color);
                this->car_manage_menu3(user);
                break;
            }
            case 4:{
                cout<<"********************修改年份********************"<<endl;
                string new_year,account;
                cout<<"请输入需要修改的用户账号(输入quit退出修改):";
                cin>>account;
                if(account=="quit"){
                    cout<<"修改年份已取消！"<<endl;
                    this->car_manage_menu3(user);
                    return;
                }
                cout<<"请输入新的年份(输入quit退出修改):";
                cin>>new_year;
                if(new_year=="quit"){
                    cout<<"修改年份已取消！"<<endl;
                    this->car_manage_menu3(user);
                    return;
                }
                Car car("default", "default", "default", "default");
                car.attachUser(User("default", "default", account, 0));
                CarFile carfile(car);
                carfile.updateyear(new_year);
                this->car_manage_menu3(user);
                break;
            }
            case 5:{
                this->car_manage_menu2(user);
                break;
            }
            case 6:{
                this->admin_menu(user);
                break;
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->car_manage_menu3(user);
                break;
            }
        }
    }
    else{
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->car_manage_menu3(user);
    }
}

void Operation::car_manage_menu2(User user){
    cout<<"********************车辆管理********************"<<endl;
    cout<<"1.添加车辆"<<endl;
    cout<<"2.删除车辆"<<endl;
    cout<<"3.修改车辆"<<endl;
    cout<<"4.返回上一级"<<endl;
    cout<<"5.返回主页"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin >> choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                cout<<"********************添加车辆********************"<<endl;
                string car_number, car_type, car_color, car_year;
                cout<<"请输入车辆信息"<<endl;
                cout<<"车牌号(输入quit退出添加):";
                cin >> car_number;
                if(car_number == "quit"){
                    cout << "添加车辆已取消！"<<endl;
                    this->car_manage_menu2(user);
                    return;
                }
                cout<<"车型(输入quit退出添加):";
                cin >> car_type;
                if(car_type == "quit"){
                    cout << "添加车辆已取消！"<<endl;
                    this->car_manage_menu2(user);
                    return;
                }
                cout<<"颜色(输入quit退出添加):";
                cin>>car_color;
                if(car_color=="quit"){
                    cout<<"添加车辆已取消！"<<endl;
                    this->car_manage_menu2(user);
                    return;
                }
                cout<<"年份(输入quit退出添加):";
                cin>>car_year;
                if(car_year=="quit"){
                    cout<<"添加车辆已取消！"<<endl;
                    this->car_manage_menu2(user);
                    return;
                }
                Car car(car_number, car_type, car_color, car_year);
                CarFile carfile(car);
                carfile.addcar(car_number, car_type, car_color, car_year);
                this->car_manage_menu2(user);
            }
            case 2:{
                cout<<"********************删除车辆********************"<<endl;
                string car_number;
                cout<<"请输入需要删除的车辆车牌号(输入quit退出删除):";
                cin >> car_number;
                if(car_number == "quit"){
                    cout<<"删除车辆已取消！"<<endl;
                    this->car_manage_menu2(user);
                    return;
                }
                Car car("default", "default", "default", "default");
                car.attachUser(User("default", "default", "default", 0));
                CarFile carfile(car);
                carfile.deletecar(car_number);
                this->car_manage_menu2(user);
                break;
            }
            case 3:{
                this->car_manage_menu3(user);
                break;
            }
            case 4:{
                this->car_manage_menu(user);
                break;
            }
            case 5:{
                this->admin_menu(user);
                break;
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->car_manage_menu2(user);
                break;
            }
        }
    }
    else{
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->car_manage_menu2(user);
    }
}

void Operation::car_manage_menu(User user){
    cout<<"******************车俩信息管理******************"<<endl;
    cout<<"1.车辆列表"<<endl;
    cout<<"2.车辆查询"<<endl;
    cout<<"3.车辆管理"<<endl;
    cout<<"4.返回上一级"<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin >> choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                cout<<"********************车辆列表********************"<<endl;
                Car car("default", "default", "default", "default");
                car.attachUser(user);
                CarFile carfile(car);
                carfile.printinfo();
                this->car_manage_menu(user);
                break;
            }
            case 2:{
                cout<<"********************车辆查询********************"<<endl;
                string car_number, car_type, car_color, car_year;
                while(1){
                    cout<<"请输入车辆相关信息"<<endl;
                    cout<<"输入请按照 车牌号——车型——颜色——年份 顺序输入(输入enter跳过该关键词):"<<endl;
                    cin.ignore();
                    getline(cin, car_number);
                    getline(cin, car_type);
                    getline(cin, car_color);
                    getline(cin, car_year);
                    Car car("default", "default", "default", "default");
                    car.attachUser(user);
                    CarFile carfile(car);
                    carfile.searchcar(car_number, car_type, car_color, car_year);
                    int choice2;
                    cout<<"******************是否继续查询******************"<<endl;
                    cout<<"1.继续查询"<<endl;
                    cout<<"2.返回上一级"<<endl;
                    cout<<"***********************************************"<<endl;
                    cout<<"请输入您的选择：";
                    cin>>choice2;
                    if(choice2==1){
                        continue;
                    }
                    else{
                        this->car_manage_menu(user);
                        return;
                    }
                }
            }
            case 3:{
                this->car_manage_menu2(user);
                break;
            }
            case 4:{
                this->admin_menu(user);
                break;
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->car_manage_menu(user);
                break;
            }
        }
    }
    else{
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->car_manage_menu(user);
    }
}

void Operation::admin_menu(User user){
    cout<<"*****************管理员菜单*****************"<<endl;
    cout<< "1.查询个人信息"<<endl;
    cout<< "2.管理用户信息"<<endl;
    cout<< "3.管理车辆信息"<<endl;
    cout<< "4.退出登录"<<endl;
    cout<<"*********************************************"<<endl;
    cout<<"请输入您的选择：";
    cin>>choice;
    if(cin.good()){
        switch(choice){
            case 1:{
                this->info_menu(user);
                break;
            }
            case 2:{
                this->info_manage_menu(user);
                break;
            }
            case 3:{
                this->car_manage_menu(user);
                break;
            }
            case 4:{
                cout << "感谢使用车辆管理系统，再见！"<<endl;
                this->start();
                break;
            }
            default:{
                cout<<"无效的选择，请重新输入！"<<endl;
                this->admin_menu(user);
                break;
            }
        }
    }
    else{
        cin.clear(); 
        cin.ignore();
        cout<<"输入无效，请重新输入！"<<endl;
        this->admin_menu(user);
    }
}

void Operation::run(){
    this->start();
}