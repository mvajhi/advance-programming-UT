#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

using namespace std;

struct User_login_info
{
    string username;
    string password;
};

// status massage
const string SUCCESS_MASSAGE = "OK";
const string BAD_REQUEST_MASSAGE = "Bad Request";
const string PERMISSION_DENIED_MASSAGE = "Permission Denied";
const string NOT_FOUND_MASSAGE = "Not Found";

// commands
const string SIGNUP_COMMAND = "POST signup ?";
const string LOGIN_COMMAND = "POST login ?";
const string LOGOUT_COMMAND = "POST logout";


// commands size
const int LOGIN_COMMAND_SIZE = 7;

// commands index
const int USERNAME_INDEX = 4;
const int PASSWORD_INDEX = 6;
