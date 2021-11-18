#include <iostream>
#include "rand.h"
#include <string>
#include <sstream>
#include "bot.h"

using namespace std;

int main(int argc, char *argv[]) {

    //Initialize all the variables that will be used
    string line;
    string time, group, user, content, command, keyword, num, first;
    stringstream ss;

    //Suppose the bot is open at the beginning
    bool state = true;

    //Test whether all the arguments reach the requirement and legal
    try {
        argMiss(argc);
        readCourse(argv[1]);
        readGroup(argv[2]);
        intJudge(argv[3]);
    }

        //Catch different error to output error message respectively
    catch (int num) {
        if (num == 1002) {
            cout << MISSING_ARGUMENT_MESSAGE << endl;
            exit(0);
        } else if (num == 1) {
            cout << CANNOT_OPEN_FILE_PREFIX << argv[1] << endl;
            exit(0);
        } else if (num == 2) {
            cout << CANNOT_OPEN_FILE_PREFIX << argv[2] << endl;
            exit(0);
        } else if (num == 1001) {
            cout << INVALID_ARGUMENT_MESSAGE << endl;
            exit(0);
        }
        exit(0);
    }

        //Match all the unkonwn error message
    catch (...) {
        cerr << "Unknown Error happens. Program continues" << endl;
        exit(0);
    }

    //Initialize a random seed according to the argument
    initializeWithSeed(atoi(argv[3]));

    //The bot begin  to work when the state is open
    while (state) {

        //Get the input message from the users
        getline(cin, line);
        int len = line.length(), mark = 0, mark1 = 0;

        //Break down the input message into time, group, user and content
        for (int j = 0; j < len; j++) {
            if (line[j] == ',') {
                time = line.substr(0, j);
                mark = j;
                break;
            }
        }
        for (int j = mark + 1; j < len; j++) {
            if (line[j] == ',') {
                group = line.substr(mark + 1, j - mark - 1);
                mark1 = j;
                break;
            }
        }
        for (int j = mark1 + 1; j < len; j++) {
            if (line[j] == ',') {
                user = line.substr(mark1 + 1, j - mark1 - 1);
                content = line.substr(j + 1, len);
                break;
            }
        }
        if(judgeGroup(group,argv[2])){
        //Judge whether there's blank space before the command which makes it illegal and then output random response
        if (content[0] == ' ') {
            RespChoice r = randomResponse();
            if (r == NONE) {}
            else if (r == REPEAT) {
                cout << content << endl << endl;
            } else if (r == ADMIRE) {
                int decide = flipCoin();
                if (decide == 1) {
                    cout << "Respect " << content << endl << endl;
                } else if (decide == 0) { cout << "I really admire " << content << endl << endl; }
            };
        }
            //Judge the command and match different command functions
        else {
            //Get the command content and judge it
            ss.str(content);
            ss >> command;
            string courseKey,instructorKey;
            if (command == "#course") {
                //If #course command is legal, get the key number and out put the course function
                if (ss >> num) {
                    int length=content.length();
                    for(int i=8;i<length;i++){
                        if(content[i]!=' '){
                            courseKey=content.substr(i,length);
                            break;
                        }
                    }
                    course(courseKey, argv[1]);
                } else {
                    cout << MISSING_KEYWORD << endl << endl;
                }
            } else if (command == "#instructor") {
                //If #instructor command is legal, get the key word and out put the instructor function
                if (ss >> keyword) {
                    int length=content.length();
                    for(int i=11;i<length;i++){
                        if(content[i]!=' '){
                            instructorKey=content.substr(i,length);
                            break;
                        }
                    }
                    instructor(instructorKey, argv[1]);
                } else {
                    cout << MISSING_KEYWORD << endl << endl;
                }
            } //If #time command is legal, out put the time function
            else if (command == "#time") {
                timeFun(time);
            } //If the stop command is legal, first judge whether the user is admin then change the bot state according to the result and output message
            else if (command == "#stop") {
                if (judgeAd(group, user, argv[2])) {
                    stop();
                    state = false;
                } else stopFail();
            } //If #help command is legal, out put the help function
            else if (command == "#help") {
                help();
            } else {
                //For illegal message, return them randomly with different ways
                RespChoice r = randomResponse();
                if (r == NONE) {}
                else if (r == REPEAT) {
                    cout << content << endl << endl;
                } else if (r == ADMIRE) {
                    int decide = flipCoin();
                    if (decide == 1) {
                        cout << "Respect " << content << endl << endl;
                    } else if (decide == 0) { cout << "I really admire " << content << endl << endl; }
                };
            }
        }

        //clear all the content of the variables for the next loop
        time.clear(), group.clear(), user.clear(), command.clear();
        line.clear();
        ss.clear();
    }
    }

    return 0;
}