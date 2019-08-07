/* 
 * File:   tinylog.h
 * Author: qiangqiang.zhou
 *
 * Created on Aug.7, 2019
 */

#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <fstream>
#include <ctime> 

using namespace std;

enum typelog 
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

struct __declspec (dllexport) structlog 
{
    structlog()
    {
         headers = true;
         level = LOG_DEBUG;
    }
    bool headers;
    typelog level;
};

//extern structlog LOGCFG;

//
//usage TLOG(LOG_INFO) << "filename=" << filename << "\n";
//
class __declspec (dllexport) TLOG 
{
public:
    TLOG::TLOG() 
    {
        init();
        opened = false;
        msglevel = LOG_DEBUG;
        
    }
    TLOG::TLOG(typelog type) 
    {
        init();
        msglevel = type;
        if(LOGCFG.headers) 
        {
            // operator<< ("["+getLabel(type)+"]");
            //operator<< (getLabel(type));
            myfile << (getLabel(type)).c_str();
            myfile <<" "<<currentDateTime().c_str()<<" ";
        }
        
    }
    TLOG::~TLOG()
    {
        if(opened) 
        {
            cout << endl;
        }
        opened = false;   
        myfile.close();
    }
    template<class T>
    TLOG &operator<<(const T &msg) 
    {
        if(msglevel >= LOGCFG.level) 
        {
            cout << msg;
            opened = true;
            myfile << msg;
        }
        return *this;
    }
private:
    bool opened;
    typelog msglevel;
    ofstream myfile;
    inline void init()
    {
        myfile.open ("log.log",std::ios_base::app);
    }
    inline string TLOG::getLabel(typelog type) 
    {
        string label;
        switch(type) 
        {
        case LOG_DEBUG: label = "LOG_DEBUG"; break;
        case LOG_INFO:  label = "LOG_INFO"; break;
        case LOG_WARN:  label = "LOG_WARN"; break;
        case LOG_ERROR: label = "LOG_ERROR"; break;
        }
        return label;
    }
    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    inline const std::string currentDateTime() 
    {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

        return buf;
    }

    structlog LOGCFG;
};

#endif  /* LOG_H */
