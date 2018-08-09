#include<memory>
bool isNumber(const char * str){
    int i =0;
    while(*str != 0 ){
        if( !isdigit(str[i]) )
            return false;
        i++;
        str++;
    }
    return true;
}
// note: this implementation does not disable this overload for array types
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
