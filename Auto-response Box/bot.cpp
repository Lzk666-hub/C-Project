#include "bot.h"
#include <sstream>

//Judge whether there are exact four input argument
void argMiss(int num) {
    if (num != 4) {
        throw 1002;
    }
}

//Judge whether the course file is opened successfully
void readCourse(const string &course) {
    ifstream ifs;
    ifs.open(course);
    if (!ifs) {
        throw 1;
    }
    ifs.close();
}

//Judge whether the group file is opened successfully
void readGroup(const string &group) {
    ifstream ifs;
    ifs.open(group);
    if (!ifs) {
        throw 2;
    }
    ifs.close();
}

//Judge whether the random seed is an integer
void intJudge(const string &seed) {
    bool flag = true;
    for (char i : seed) {
        int tmp = (int) i;
        if (tmp >= 48 && tmp <= 57) {
            continue;
        } else {
            flag = false;
        }
    }
    if (!flag) {
        throw 1001;
    }
}

//Output all the courses and their information whose course code include the keyword
int course(const string &num, const string &courseFile) {
    bool flag = false;
    string bar;
    int total;
    ifstream ifs;
    ifs.open(courseFile);
    getline(ifs, bar);
    total = stoi(bar);
    for (int i = 0; i < total; i++) {
        string courseInfo;
        getline(ifs, courseInfo);
        string::size_type idx = courseInfo.find(num);
        if (idx != string::npos) {
            flag = true;
            int len = courseInfo.length(), mark = 0;
            for (int j = 0; j < len; j++) {
                if (courseInfo[j] == ',') {
                    string str_1 = courseInfo.substr(0, j);
                    mark = j;
                    cout << "Course Code: " << str_1 << endl;
                    break;
                }

            }
            for (int j = mark + 1; j < len; j++) {
                if (courseInfo[j] == ',') {
                    string str_2 = courseInfo.substr(mark + 1, j - mark - 1);
                    string str_3 = courseInfo.substr(j + 1, len);
                    cout << "Course Name: " << str_2 << endl;
                    cout << "Instructor: " << str_3 << endl;
                    break;
                }
            }
        }
    }
    if (!flag) {
        cout << COURSE_NOT_FOUND << endl;
    }
    cout << endl;
    ifs.close();
    return 0;
};


//Output all the instructors whose name contains the keyword and all the courses they are teaching
int instructor(const string &key, const string &courseFile) {
    bool exist = false;
    string bar;
    int total;
    ifstream ifs;
    ifs.open(courseFile);
    getline(ifs, bar);
    total = stoi(bar);
    bool flag[total];
    string code[total], name[total], ins[total];
    for (int i = 0; i < total; i++) {
        flag[i] = true;
    }
    for (int i = 0; i < total; i++) {
        string str1, str2, str3;
        string courseInfo;
        getline(ifs, courseInfo);
        int len = courseInfo.length(), mark = 0;
        for (int j = 0; j < len; j++) {
            if (courseInfo[j] == ',') {
                code[i] = courseInfo.substr(0, j);
                mark = j;
                break;
            }
        }
        for (int j = mark + 1; j < len; j++) {
            if (courseInfo[j] == ',') {
                name[i] = courseInfo.substr(mark + 1, j - mark - 1);
                ins[i] = courseInfo.substr(j + 1, len);
                break;
            }
        }

    }
    for (int i = 0; i < total; i++) {
        string::size_type idx = ins[i].find(key);
        if (idx != string::npos && flag[i]) {
            exist = true;
            flag[i] = false;
            cout << "Instructor: " << ins[i] << endl;
            cout << "Courses: " << code[i];
            for (int j = i + 1; j < total; j++) {
                if (ins[j] == ins[i] && flag[j]) {
                    cout << " " << code[j];
                    flag[j] = false;
                }
            }
            cout << endl;
        }
    }
    if (!exist) {
        cout << FACULTY_NOT_FOUND << endl;
    }
    cout << endl;
    ifs.close();
    return 0;
};


//Return the time of the input time
void timeFun(const string &time) {
    cout << time << endl;
    cout << endl;
}


//Return the exit message when the bot is shut down by the admin
void stop() {
    cout << EXIT_PROMPT << endl;
    cout << endl;
};


//Output the error message when the person who is not admin try to shut down the bot
void stopFail() {
    cout << STOP_BOT_FAIL << endl;
    cout << endl;
}


//Judge whether the user is the admin of the group which he belongs to
bool judgeAd(const string &group, const string &name, const string &groupFile) {
    bool judge = false;
    string fileOuter, groupNum;
    ifstream ifs;
    ifs.open(groupFile);
    getline(ifs, fileOuter);
    string fileIn = fileOuter + '/' + group;
    ifstream stream;
    stream.open(fileIn);
    string adminNum;
    getline(stream, adminNum);
    int adminNumber = stoi(adminNum);
    string admin[adminNumber];
    for (int j = 0; j < adminNumber; j++) {
        getline(stream, admin[j]);
        if (name == admin[j]) {
            judge = true;
        }
    }
    return judge;
};


//Output the help message when the user input #help command
void help() {
    cout << HELP_TEXT << endl;
    cout << endl;
};

//Judge whether the group belongs to the group which the bot can control
bool judgeGroup(const string &group, const string &groupFile){
    bool judge = false;
    string fileOuter, groupNum;
    ifstream ifs;
    ifs.open(groupFile);
    getline(ifs, fileOuter);
    getline(ifs,groupNum);
    int index=stoi(groupNum);
    string groupName[index];
    for(int i=0;i<index;i++){
        getline(ifs,groupName[i]);
    }
    for(int i=0;i<index;i++){
        if(groupName[i]==group){
            judge= true;
        }
    }
    return judge;
}