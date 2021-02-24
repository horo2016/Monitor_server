#include <stdio.h>
#include "DevList.h"
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


void SListInit(SList*s) {
 assert(s);
 s->_pHead = NULL;
}
PNode BuySListNode(SDataType data ,DevInfo devinfo )
{ 
    PNode p; 
	p= (PNode)malloc(sizeof(Node)); 
	if (p == NULL) {
		return NULL;
	}
	p->_data=data;
	p->_devinfo.id =data;
	memcpy(p->_devinfo.sn ,devinfo.sn,16);
	p->_devinfo.timestamp = devinfo.timestamp ;
	p->_PNext=NULL; 
	return p;
}


PNode buyslistnode(SDataType data) {
	PNode newnode = (PNode)malloc(sizeof(Node));
	if (newnode == NULL) {
		return NULL;
	}
	newnode->_data = data;
	newnode->_PNext = NULL;
	return newnode;
}

//尾插
void SListPushBack(SList* s, SDataType data ,DevInfo _devinfo ) {
 //找链表最后一个节点
 assert(s);
 PNode pNewNode = BuySListNode(data,_devinfo);
 if (s->_pHead == NULL) {//链表没有节点的情况
  s->_pHead = pNewNode;
 }
 else {
  PNode pCur = s->_pHead;
  while (pCur->_PNext) {
   pCur = pCur->_PNext;
  }
  //让最后一个节点指向新节点
  pCur->_PNext = pNewNode;
 }
}
//尾删除
void SListPopBack(SList* s) {
 assert(s);
 if (s->_pHead == NULL) {//链表中没有节点
  return;
 }
 else if (s->_pHead->_PNext == NULL) {//只有一个节点
  free(s->_pHead);
  s->_pHead = NULL;
 }
 else {                           //多个节点
  PNode pCur = s->_pHead;
  PNode pPre = NULL;
  while (pCur->_PNext) {
   pPre = pCur;
   pCur = pCur->_PNext;
  }
  free(pCur);
  pPre->_PNext = NULL;
 }
}
//头插
void SListPushFront(SList* s, SDataType data ,DevInfo _devinfo) {
 assert(s);
 PNode pNewNode = BuySListNode(data,_devinfo);
 if (s->_pHead == NULL) {//链表为空
  s->_pHead = pNewNode;
 }
 else {
  pNewNode->_PNext = s->_pHead;
  s->_pHead = pNewNode;
 }
}
//头山
void SListPopFront(SList* s) {
 assert(s);
 if (s->_pHead == NULL) {//链表为空
  return;
 }
 else if (s->_pHead->_PNext == NULL) {//只有一个节点
  free(s->_pHead);
  s->_pHead = NULL;
 }
 else {
  PNode pCur = s->_pHead;
  s->_pHead = pCur->_PNext;
  free(pCur);
 }
}
void SListInsert(PNode pos, SDataType data ,DevInfo _devinfo) {
 PNode pNewNode = NULL;
 if (pos == NULL) {
  return;
 }
 pNewNode = BuySListNode(data,_devinfo);
 
 pNewNode->_PNext = pos->_PNext;
 pos->_PNext = pNewNode;
}
//查找
PNode SListFind(SList* s, SDataType data) {
 assert(s);
 PNode pCur = s->_pHead;
 while (pCur) {
  if (pCur->_data == data) {
   return pCur;
  }
  pCur = pCur->_PNext;
 }
 return NULL;
}
//查找某个字符串是否相等
PNode SListFindSn(SList* s, char* data) {
 assert(s);
 PNode pCur = s->_pHead;
 while (pCur) {
  if (0 == memcmp(pCur->_devinfo.sn ,data, 16)) {
   return pCur;
  }
  pCur = pCur->_PNext;
 }
 return NULL;
}
//修改节点的值
SList*  SListModifyTimestamp(SList* s, SDataType data ,long long timestamp) {
 assert(s);
 
 PNode pCur = s->_pHead;
 while (pCur) {
  if (pCur->_data == data) {
  	pCur->_devinfo.timestamp = timestamp ;
   return s;
  }
  pCur = pCur->_PNext;
 }
 return NULL;
}

//遍历
void SListAll(SList *s)
{
    PNode p_mov= s->_pHead;
    while(p_mov!=NULL)//条件为当前节点，遍历时主要显示当前节点
    {
      //  printf("%d %d %s\n",p_mov->_data  ,p_mov->score,p_mov->name);
        p_mov=p_mov->_PNext;
    }
}

//删除给定pos位置的节点。
void SListErase(SList* s, PNode pos) {
 assert(s);
 if (pos == NULL || s->_pHead == NULL) {
  return;
 }
 if (pos== s->_pHead) {
  s->_pHead = pos->_PNext;
 }
 else {
  PNode pPrePos = s->_pHead;
  while (pPrePos&&pPrePos->_PNext != pos) {
   pPrePos = pPrePos->_PNext;
  }
  pPrePos->_PNext = pos->_PNext;
 }
 free(pos);
}

void SListRemove(SList*s, SDataType data) {
 assert(s);
 if (s->_pHead == NULL) {
  return;
 }
 PNode pPre = NULL;
 PNode pCur = s->_pHead;
 while (pCur) 
 {
	  if (pCur->_data == data) 
	  	{
			   if (pCur == s->_pHead) {         //要删除的是第一个位置的节点
			    s->_pHead = pCur->_PNext;
			   }
			   else {
			    pPre->_PNext = pCur->_PNext;      //其它位置的情况，让前一个节点指向其后一个节点
			   }
	   free(pCur);
	   return;
	  }
	  else {
	   	 pPre = pCur;
	  	 pCur = pCur->_PNext;
	  }
 }
}

int SListSize(SList* s) {            //获取链表有效节点的个数
 assert(s);
 int count = 0;
 PNode pCur = s->_pHead;
 while (pCur) {
  count++;
  pCur = pCur->_PNext;
 }
 return count;
}

int SListEmpty(SList* s) {              //检测链表是否为空
 assert(s);
 if (s->_pHead == NULL) {
  return -1;
 }
 return 0;
}

void SListClear(SList* s) {             //清空链表
 assert(s);
 if (s->_pHead == NULL) {
  return;
 }
 PNode pCur = s->_pHead;
 while (pCur->_PNext) {    //循环清空链表中的节点
  PNode Tmp = pCur->_PNext;
  free(pCur);
  pCur = Tmp;
 }
 if (pCur) {      //清空最后一个节点
  free(pCur);
  pCur = NULL;
 }
}

void SListDestroy(SList* s) {            //销毁链表
 assert(s);
 if (s->_pHead == NULL) {
  free(s->_pHead);
  return;
 }
 while (s->_pHead) {    
  PNode Tmp = s->_pHead->_PNext;
  free(s->_pHead);
  s->_pHead = Tmp;
 }
}

void SListPrint(SList* s) {             //打印链表
 assert(s);
 PNode pCur = s->_pHead;
 while (pCur) {
  printf("{%d,[%d,%s,%ld]}--->", pCur->_data,pCur->_devinfo.id,pCur->_devinfo.sn,pCur->_devinfo.timestamp);
  pCur = pCur->_PNext;
 }
 printf("\n");
}




/*void main() {
 SList s;
 SListInit(&s);
 SListPushBack(&s, 1);
 SListPushBack(&s, 2);
 SListPushBack(&s, 3);
 printf("size=%d\n", SListSize(&s));
 SListPrint(&s);
 SListInsert(SListFind(&s, 2), 0);
 SListPrint(&s);
 SListRemove(&s, 2);
 SListPrint(&s);
  system("pause");
 return;
}*/
