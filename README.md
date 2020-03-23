# MemoryLeakDetector-Project
内存泄漏检测器

1.重载new delete函数，将申请内存的时候将其加入双链表


2.申请类 在析构函数中检测文件结束后是否双链表还有值 很简单  就是检查前后指针是否指向自己

使用方法:
1.注释掉头文件进行编译得到可执行文件


g++ main.cpp -o a


2.不注释  一起编译测试文件和头文件.cpp


g++ main.cpp LeakDetector.cpp -std=c++11 -Wno-write-strings

3.执行a.out


./a


-一个长期运行不断的占用内存的程序：

int main()
{
  while(1)
  {
    int *a=new int;
    return 0;
  }  
}

-若正常分支有内存需要释放，则不要忘了异常分支的内存释放如try语句的catch分支，函数中的多个return分支都要考虑到相应内存的释放

 try {  
     void *ptrData = new char[128];   
     if(NULL  !=  ptrData) 
       {  delete ptrData;  ptrData = NULL; }
     } catch(CException &e)
      {
         LOG(LOG_LEVEL_ERROR, " errorcode:"<< e.errorCode());
      }catch(…)
     { 
         LOG(LOG_LEVEL_ERROR, " errorcode:…");
     } 
  }
