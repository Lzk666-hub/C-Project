#include <iostream>
#include "rand.h"
#include "constants.h"
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

//Judge whether there are exact four input argument
void argMiss(int num);


//Judge whether the course file is opened successfully
void readCourse(const string &course);

//Judge whether the group file is opened successfully
void readGroup(const string &group);


//Judge whether the random seed is an integer
void intJudge(const string &seed);

//Output all the courses and their information whose course code include the keyword
int course(const string &num, const string &courseFile);


//Output all the instructors whose name contains the keyword and all the courses they are teaching
int instructor(const string &key, const string &courseFile);


//Return the time of the input time
void timeFun(const string &time);


//Return the exit message when the bot is shut down by the admin
void stop();

//Output the error message when the person who is not admin try to shut down the bot
void stopFail();


//Judge whether the user is the admin of the group which he belongs to
bool judgeAd(const string &group, const string &name, const string &groupFile);


//Output the help message when the user input #help command
void help();

//Judge whether the group belongs to the group which the bot can control
bool judgeGroup(const string &group, const string &groupFile);