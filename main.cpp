#include <iostream>
#include "json\Json.h"
#include <string>
#include <sstream>
#include <fstream>
#include<sys/time.h>

using namespace std;
using namespace yazi::json;

void testParse()
{
     try
    {
        //读文件数据
        ifstream fin("D:\\chStudly\\vsCodeProject\\json_yazi\\test.txt");
        stringstream ss;
        ss<<fin.rdbuf();
        if(fin)
        {
            int a = 0;
        }
        
        const string & data = ss.str();
            Json json;
            json.parser(data);
            std::cout<<json.str()<<std::endl;
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    long long milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    std::cout << "Milliseconds since epoch: " << milliseconds << std::endl;

        const int max = 100000;
        for(int i = 0 ; i < max ;i++)
        {
            Json json;
            json.parser(data);
            json.clear();
        }
    gettimeofday(&tv, nullptr);
    long long millisecondsEnd = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    std::cout << "Milliseconds since epoch: " << millisecondsEnd << std::endl;

        double tiem = (millisecondsEnd - milliseconds) /1000000.0;
        std::cout<<tiem<<std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main()
{
    testParse();
    std::getchar();

    Json arra;
    arra["bool"] = true;
    arra["bool1"] = true;
    arra["bool2"] = true;
    arra["bool3"] = true;

    std::cout<<arra.str()<<std::endl;
    std::cout<<arra.has("bool")<<std::endl;
     bool b = arra.has("bool123");
    arra.remove("bool1");
    std::cout<<arra.str()<<std::endl;
    cout<<"hello World"<<endl;
    return 0;
}
