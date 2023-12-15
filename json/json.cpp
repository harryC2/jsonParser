#include "json.h"
#include <sstream>
#include "parser.h"
using namespace std;

using namespace yazi::json;


void Json::parser(const string& str)
{
    Parser parser;
    parser.load(str);
    *this =parser.parse();
}
Json::Json(/* args */)
{

}

Json::~Json()
{
    //clear();
}

Json::Json(bool value) :m_type(json_bool)
{
    m_value.m_bool = value;
}
Json::Json(int value):m_type(json_int)
{
    m_value.m_int = value;
}
Json::Json(double value):m_type(json_double)
{
    m_value.m_double = value;
}

Json::Json(const  char *  value):m_type(json_string)
{
    // 动态类型分配
    m_value.m_string = new string(value);
}
Json::Json(const  string&  value):m_type(json_string)
{
    // 动态类型分配
    m_value.m_string = new string(value);
}

Json::Json(Type type)
{
    m_type = type;
    switch (m_type)
    {
    case json_null:
        /* code */
        break;
    case json_bool:
        m_value.m_bool = false;
        break;
    case json_double:
     m_value.m_double = 0.0;
     break;
    case json_int:
        m_value.m_int = 0;
        break;
    case json_string:
        m_value.m_string = new std::string("");
        break;
    case json_array:
        m_value.m_vecJson = new std::vector<Json>();
        break;
    case json_object:
        m_value.m_mapJson = new std::map<string, Json>();
        break;
    default:
        break;
    }
}
Json::Json(const Json &other)
{  copy(other);
}

// operation() = 重载
Json::operator bool()
{
    if(m_type != json_bool)
    {
        throw new logic_error("type error , not bool value");
    }
    return m_value.m_bool;
}
Json::operator int()
{
    if(m_type != json_int)
    {
        throw new logic_error(" tyoe error , not int value");
    }
    return m_value.m_int;

}
Json::operator double()
{
        if(m_type != json_double)
    {
        throw new logic_error(" tyoe error , not double value");
    }
    return m_value.m_double;
}


Json::operator string()
{
    if(m_type != json_string)
    {
        throw new logic_error(" tyoe error , not string value");
    }
    return *m_value.m_string;
}


Json& Json::operator[] (int index)
{
        if(m_type != json_array)
    {
        m_type = json_array;
        m_value.m_vecJson = new vector<Json>();
    }
    if(index < 0)
    {
        throw new logic_error("array[] index < 0");
    }
    int size = m_value.m_vecJson->size();
    if(index >= size)
    {
        // 扩容
         //index > m_value.m_vecJson->max_size()?
        //m_value.m_vecJson->reserve(index) : NULL;
        for(int i = size; i <= index; i++)
        {
            m_value.m_vecJson->push_back(Json());
        }
    }
    return (m_value.m_vecJson)->at(index); // 返回当前索引的Json对象  
}
void Json::append(const Json & other)
{
    //Json temp = this;
    if(m_type != json_array)
    {
        clear();
        m_type = json_array;
        m_value.m_vecJson = new vector<Json>();

    }
    (m_value.m_vecJson)->push_back(other);
}

string Json::str() const
{
    stringstream ss;
    // 字符串输出流
    switch (m_type)
    {
    case json_null:
        ss << "null"; // 流向箭头一边
        break;
    case json_bool:
       if(m_value.m_bool)
       {
         ss<<"true";
       }
       else
       {
         ss<<"false";
       }
        break;
    case json_double:
         ss << m_value.m_double;
         break;
    case json_int:
         ss << m_value.m_int;
         break;
    case json_string:
        ss << '\"' << *m_value.m_string << '\"';
        break;
    case json_array:
    {
        ss << '[';
        for (auto it = m_value.m_vecJson->begin(); it != m_value.m_vecJson->end(); it++)
        {
            if (it != m_value.m_vecJson->begin())
            {
                ss << ',';
            }
            ss << it->str(); // recursion递归 recurred
        }
        ss << ']';
          break;
    }
    case json_object:
    {
        ss << '{';
        for (auto it = m_value.m_mapJson->begin(); it != m_value.m_mapJson->end(); it++)
        {
            if (it != m_value.m_mapJson->begin())
            {
                ss << ',';
            }
            ss << '\"' << it->first << '\"' << it->second.str(); // recursion递归 recurred
        }
        ss << '}';
          break;
    }
    default:
        break;
    }
    return ss.str();
}

Json& Json::operator [] (const char* key)
{
    string name(key);
    return (*(this))[name];
}
Json& Json::operator [] (const string& key)
{
    if(m_type != json_object)
    {
        clear();
        m_type = json_object;
        m_value.m_mapJson = new std::map<string,Json>();
    }
    return  (*(m_value.m_mapJson))[key];
}
 void Json::copy(const Json & other){

     m_type = other.m_type;
    switch (m_type)
    {
    case json_null:
        /* code */
        break;
    case json_bool:
        m_value.m_bool = other.m_value.m_bool;
        break;
    case json_double:
        m_value.m_double = other.m_value.m_double;
        break;
    case json_int:
        m_value.m_int = other.m_value.m_int;
        break;
    case json_string:
        // 浅拷贝 提高性能，但是防止json被释放造成空指针
        m_value.m_string = other.m_value.m_string;
        break;
    case json_array:
        m_value.m_vecJson = other.m_value.m_vecJson;
        break;
    case json_object:
        m_value.m_mapJson = other.m_value.m_mapJson;
        break;
    default:
        break;
    }
    return void();
 }
void Json::operator= (const Json& other)
{
    copy(other);
}
bool Json::operator==(const Json& other)
{
    if(m_type != other.m_type)
    {
        return false;
    }
    switch (m_type)
    {
    case json_null:
        return true;    
    case json_bool:
        return m_value.m_bool == other.m_value.m_bool;
    case json_int:
    return m_value.m_int == other.m_value.m_int;
    case json_double:
    return m_value.m_double == other.m_value.m_double;   
    case json_string:
    return m_value.m_string->compare(*other.m_value.m_string) == 0;    // 这里使用指针需要考虑指针是否为空
    case json_array:
    return m_value.m_vecJson == other.m_value.m_vecJson;   
        case json_object:
    return m_value.m_mapJson == other.m_value.m_mapJson;   
    default:
     return false;
        break;
    }
}
bool Json::operator !=(const Json& other)
{
    return !((*this) == other);
}


void Json::clear()
{
    switch (m_type)
    {
    case json_null:
        /* code */
        break;
    case json_bool:
        m_value.m_bool = false;
        break;
    case json_double:
        m_value.m_double = 0.0;
        break;
    case json_int:
        m_value.m_int = 0;
        break;
    case json_string:
        // 浅拷贝 提高性能，但是防止json被释放造成空指针
       SafeDelete(m_value.m_string);
        break;
    case json_array:
       // 循环遍历delete
        for(auto iter = m_value.m_vecJson->begin(); iter != m_value.m_vecJson->end();iter++)
        {
            iter->clear();
        }
        SafeDelete(m_value.m_vecJson);
        break;
    case json_object:
        // 循环遍历delete
        for(auto iter = m_value.m_mapJson->begin(); iter != m_value.m_mapJson->end();iter++)
        {
            iter->second.clear();
        }
        SafeDelete(m_value.m_mapJson);
        break;
    default:
        break;
    }
    return void();
}

// 强制类型转换
bool Json::asbool() const
{
    if(m_type != json_bool)
    {
        throw new std::logic_error(" type error, not bool value");
    }
    return m_value.m_bool;
}
int Json::asInt() const
{
        if(m_type != json_int)
    {
        throw new std::logic_error(" type error, not int value");
    }
    return m_value.m_int;
}
double Json::asDouble() const
{
        if(m_type != json_double)
    {
        throw new std::logic_error(" type error, not double value");
    }
    return m_value.m_double;
}
string Json::asString() const
{
    if(m_type != json_string)
    {
        throw new std::logic_error(" type error, not string value");
    }
    return *m_value.m_string;
}

bool Json::has(int index)
{
    if(m_type != json_array)
    {
        return false;
    }
    int size  = m_value.m_vecJson->size();
    return index>=0 && index <=size;
}
bool Json::has(const char *key)
{
    has(string(key));
}
bool Json::has(const string &key)
{
    if(m_type != json_object)
    {
        return false;
    }
    return (m_value.m_mapJson->find(key) != m_value.m_mapJson->end());
}

void Json::remove(int index)
{
    if(m_type != json_array)
    {
        return ;
    }
    if(has(index))
    {
        // 如果是得delete掉
        // 会不会调用析构clear()
        auto iter =m_value.m_vecJson->begin()  + index;
        iter->clear();
        m_value.m_vecJson->erase(iter);
    }
}
void Json::remove(const string &key)
{
    if(m_type != json_object)
    {
        return ;
    }
    if(has(key))
    {
        // 如果是得delete掉
        // 会不会调用析构clear()
        auto iter = m_value.m_mapJson->find(key);
        iter->second.clear();
        m_value.m_mapJson->erase(iter);
    }
}
void Json::remove(const char* key)
{
    remove(string(key));
}
