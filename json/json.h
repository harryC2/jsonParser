#pragma once
#include <string>
using namespace std;
#include<vector>
#include <map>

#define SafeDelete(a)  \
     if(a!= nullptr){ \
        delete a; \
        a = nullptr; \
     }
namespace yazi{
    namespace json{


     class Json
     {
        public:
        // link json.org/json-en.html  
        // include  all type form json
        enum Type
        {
            json_null = 0,
            json_bool,
            json_int,
            json_double,
            json_string,
            json_array,
            json_object
        };
        Json(/* args */);
        Json(bool value);
        Json (int value);
        Json(double value);
        Json (const char* value);
        Json(const  string&  value);
        Json(Type type);
        Json(const Json &other);
        ~Json();

        void parser(const string& str);
        // operation() = 重载
        // 基本类型转换
        operator bool();
        operator int();
        operator double();
        operator string();

        //数组下标符号运算发重载
        Json& operator[] (int index);
        void append(const Json & other);

        Json& operator [] (const char* key);
        Json& operator [] (const string& key);

        void operator= (const Json& other);
        bool operator== (const Json& other);
        bool operator!= (const Json& other);

        bool isNull() const {return m_type == json_null ;};
        bool isBool() const {return m_type == json_bool;};
        bool isInt() const {return m_type == json_int;};
        bool isDouble() const {return m_type == json_double;};
        bool isString() const {return m_type == json_string;};

        bool isArray() const {return m_type == json_array;};
        bool isObject() const {return m_type == json_object;};

        // 强制类型转换
        bool asbool() const;
        int asInt() const;
        double asDouble() const;
        string asString() const;

        bool has(int index);
        bool has(const char* key);
        bool has(const  string& key);
        
        void remove(int index);
        void remove(const char* key);
        void remove(const string& key);

        void copy(const Json & other);

        void clear();
        // 输出json到文件
        string str() const;

    typedef std::vector<Json>::iterator vecIterator;
    typedef std::map<string,Json>::iterator mapIterator;
    vecIterator VecBegin()
    {
        if(m_type == Type::json_array)
        {
            return m_value.m_vecJson->begin();
        }
    };
    mapIterator MapBegin()
    {
        if (m_type == Type::json_object)
        {
            return m_value.m_mapJson->begin();
        }
    };
    vecIterator VecEnd()
    {
        if(m_type == Type::json_array)
        {
            return m_value.m_vecJson->end();
        }
    };
    mapIterator MapEnd()
    {
        if(m_type == Type::json_array)
        {
            return m_value.m_mapJson->end();
        }
    };

     private:
        /* data */
        // union is a special data structure that allow differrnt data types to 
        //share the same memory location, this means that all members of a union occupy ths same
        // memory ,and only one member can hold a value at a time;
        // string obeject dynamically allocated memory ,which means theirs size is not know at compile-time 
        // but determied(决定 ) at runtime. hence/so dirrectly storing a string object in a union would disrupt（打乱）
        // the memory layout(布局)， potenially leading to memory leaks or data corryotion;

        // on the other handle(相反)，storing a poniter to a string in a union can avoid thers issues. pointers have a fied size,
        // so they do not affect(影响） tihe size and memory layout of the union; by using a pointer,the union can reference the
        // memory address of the string instead of direclty storing its  content
        // one pice memery, varitly type in zhe memery
        // but one time .only one menber 

        union Value
        {
            // memory size is defined by a bigest  member memory;
            bool m_bool;
            int m_int;
            double m_double; // 8字节
            std::string* m_string;// 不能放对象object在联合体里，放的是指针,
            std::vector<Json> * m_vecJson;
            std::map<string,Json> * m_mapJson;
        };
        Type m_type {json_null};
        Value m_value;
     };
    }

}