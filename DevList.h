#ifndef DEV_LIST_H
#define DEV_LIST_H
#pragma once
typedef int SDataType;
typedef struct{
	int id;
	char sn[17];
	long long timestamp;
}DevInfo;
//链表的节点
typedef struct SListNode
{
 SDataType _data;
 DevInfo _devinfo;
 struct SListNode* _PNext;
}Node,*PNode;

typedef struct SList       //封装了链表的结构
{
 PNode _pHead;//指向链表第一个节点
}SList;

void SListInit(SList*s);//链表的初始化

//在链表s最后一个节点后插入一个值为data的节点
void SListPushBack(SList* s, SDataType data ,DevInfo _devinfo );

//删除链表s最后一个节点
void SListPopBack(SList* s);

//在链表s第一个节点前插入值为data的节点
void SListPushFront(SList* s, SDataType data ,DevInfo _devinfo);

//删除链表s的第一个节点
void SListPopFront(SList* s);

//在链表的pos位置后插入值为data的节点
void SListInsert(PNode pos, SDataType data ,DevInfo _devinfo);

//删除链表s中pos位置的节点
void SListErase(SList* s, PNode pos);

// 在链表中查找值为data的节点，找到返回该节点的地址，否则返回NULL 
PNode SListFind(SList* s, SDataType data);
// 在链表中查找值为”data“的节点，找到返回该节点的地址，否则返回NULL 
PNode SListFindSn(SList* s, char* data);

//移除链表中第一个值为data的元素
void SListRemove(SList*s, SDataType data);

// 获取链表中有效节点的个数 
int SListSize(SList* s);

// 检测链表是否为空 
int SListEmpty(SList* s);

// 将链表中有效节点清空 
void SListClear(SList* s);

// 销毁链表 
void SListDestroy(SList* s);
//打印链表
void SListPrint(SList* s);
#endif
