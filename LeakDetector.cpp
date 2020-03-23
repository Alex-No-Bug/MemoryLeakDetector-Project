#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<bits/stdc++.h>
#define _NEW_OVERLOAD_IMPLEMENTATION__
using namespace std;
#include "LeakDetector.hpp"
//1.定义内存的双向链表
typedef struct memory_node//改成节点的定义
{
    struct memory_node *next,*prev ;
    size_t size; //申请内存的大小
    bool isArray;//是否申请的数组
    char* file ;//存储所在文件
    unsigned int line ;//保存所在行
} memory_node;
static unsigned long memory_allocated=0;//保存未被释放的空间
//双向链表的头结点
static memory_node root={
    &root,&root,//头结点指向自己
    0,false,NULL,0
};
unsigned int _leak_detector::callCount = 0;

//2.编写插入 删除的函数用于重载new
void*AllocateMemory(size_t _size,bool _array,char*_file,unsigned _line)
{
    size_t newSize = sizeof(memory_node)+_size;
    memory_node *newElem =(memory_node*)malloc(sizeof(memory_node));
    newElem->size=_size;
    newElem->isArray=_array;
    newElem->file=NULL;
    if(_file)//如果有文件信息 则保存下来
    {
        newElem->file=(char*)malloc(strlen(_file)+1);
        strcpy(newElem->file,_file);
    }

    //新申请的节点插入双向链表
    newElem->next=root.next;
    newElem->prev=&root;
    root.next=newElem;
    root.next->prev=newElem;

    memory_allocated+=_size;
    //返回申请的内存
    return (char*)newElem+sizeof(memory_node);
}

void DeleteMemory(void* _ptr,bool _array)
{
    memory_node *current=(memory_node*)( (char*)_ptr-sizeof(memory_node) );
    if(current->isArray !=_array)return;
    //删除节点
    current->next->prev=current->prev;
    current->prev->next=current->next;
    memory_allocated-=current->size;
    if(current->file) free(current->file);
    free(current);
}
//重载new 
void* operator new(size_t size)
{
    return(AllocateMemory(size,false,NULL,0));
}
void* operator new[](size_t size)
{
    return AllocateMemory(size,true,NULL,0);
}
void *operator new(size_t size ,char*file,unsigned int line)
{
    AllocateMemory(size,false,file,line);
}
void *operator new[](size_t size ,char*file,unsigned int line)
{
    AllocateMemory(size,true,file,line);
}
//重载delete
void operator delete(void *ptr) noexcept
{
    DeleteMemory(ptr,false);
}
void operator delete[](void *ptr) noexcept
{
    DeleteMemory(ptr,true);
}


//内存泄漏检测器
unsigned int _leak_detector :: LeakDetector(void) noexcept
{
    unsigned  int count=0;
    memory_node*ptr=root.next;
    //遍历链表如果内存泄漏 root.next总不是指向自己
    while(ptr&& ptr!=&root)//遍历 依次把信息输出
    {
        if(ptr->isArray)
        cout<<"leak[]";
        else cout<<"leak  ";
        cout<<ptr<<"    size   "<<ptr->size;
        if(ptr->file)//输出文件的位置
        cout<<"located in "<<ptr->file<<"line"<<ptr->line<<")";
        else 
        cout<< "cannot find position";
        cout<<endl;
        count++;
        ptr=ptr->next;
    }
    if(count)
    cout<<"Tatol"<<count<<" leak , size "<<  memory_allocated <<"byte."<<endl;
    return  count;
}



