#ifndef _LEAK_DETECTOR_
#define _LEAK_DETECTOR_
#include<stdlib.h>
void* operator new(size_t size,char* file,unsigned int line);
void* operator new[](size_t  size,char*file, unsigned int line);
class _leak_detector//用于静态类
{
    public:
    static unsigned int callCount;
    _leak_detector() noexcept 
    {
        ++callCount;
    }
    ~_leak_detector() noexcept 
    {
        if(--callCount==0)
            LeakDetector();//析构的时候调用函数
    }
    private://函数负责检测最后的是否还剩余
    static unsigned int LeakDetector() noexcept;
};
static _leak_detector _exit_counter;
#endif


// 跨平台。
// 不同平台的size_t会用不同的类型实现，使用size_t而非int或unsigned可以写出扩展行更好的代码　　
// size_t类型是一个类型定义，通常将一些无符号的整形定义为size_t，
// 比如说unsigned int或者unsigned long，甚至unsigned long long