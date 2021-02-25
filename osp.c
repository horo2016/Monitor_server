#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>

/*pthread*/
#include "sys/ipc.h"
#include "sys/msg.h"
#include "pthread.h"
#include <arpa/inet.h>
#include <net/if.h>


#include <time.h> 
#include <sys/time.h> 

/*ListTable*/
#include  "DevList.h"
#include "client_pub_sub.h"

#define _T3MINUTES (3*1000000*60)
SList DevSList;

void send_databaseOnline(char *number,int sta)
{
   char tmpBuf[0xff]={0};
   sprintf(tmpBuf,"curl -s -d \"prNumber=%s&prState=%d\"  -X POST \"http://www.woyilian.com/gps_car/Login/UpdateDeviceStatusFromApp\"",number,sta);
   printf("%s\n",tmpBuf);
   system(tmpBuf);
}

unsigned long getmillis()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    unsigned long count = tv.tv_sec * 1000000 + tv.tv_usec;
    return count / 1000;
}
void offlineManage_handle(int *arg)
{
	unsigned long lastSubMillis = 0;

	while (1)
		{
			unsigned long loopTime = getmillis();
   			if(loopTime - lastSubMillis > (1000*10))//10s 判断一次
   				{
   				
				  if(0 == SListEmpty(&DevSList) )//不为空
				  	{
				  	   
						PNode p_mov= DevSList._pHead;
					    while(p_mov!=NULL)//条件为当前节点，遍历时主要显示当前节点
					    {
					      //  printf("%d %d %s\n",p_mov->_data  ,p_mov->score,p_mov->name);
					      //获取时间戳
					        struct timeval tv;
     						gettimeofday(&tv, NULL);
     						 long long  timestamp = tv.tv_sec * 1000000 + tv.tv_usec;
							 long long  timediff  = timestamp -p_mov->_devinfo.timestamp ;
							 printf("timediff %d %d \n",timediff,_T3MINUTES);
							 if(timediff > _T3MINUTES)
							 	{
							 	    send_databaseOnline(p_mov->_devinfo.sn,0);
								   SListErase(&DevSList, p_mov)	;
							 }
					         p_mov=p_mov->_PNext;
					    }
				  }else {
					printf("list is empyty \n");
				  }

				  lastSubMillis = loopTime;
			}
			usleep(2000);
		}
   

}

void *Mqtt_ClentTask(void *argv)
{
  
 SListInit(&DevSList);
// SListPushBack(&s, 1);
// SListPushBack(&s, 2);
// SListPushBack(&s, 3);
   sleep(2);
   mainSub("online");
	while (1)
	{
		
		printf("ReConnect\n");
		sleep(3);
	}




}

/*******************************************************************************
* function name	: main
* description	: main function for control_engine
* param[in] 	: none
* param[out] 	: none
* return 		: 0-success,-1-fail
*******************************************************************************/
int  main (int argc, char ** argv)
{
	
	pthread_attr_t attr;
    pthread_t pthread_id = 0 ;
	struct sched_param param;
	/*create task thread */

	
   
	  /*create task mqtt  client queue */
	pthread_attr_init (&attr);
	pthread_attr_setschedpolicy (&attr, SCHED_RR);
	param.sched_priority = 5;
	pthread_attr_setschedparam (&attr, &param);
	pthread_create (&pthread_id, &attr, &Mqtt_ClentTask, NULL);
	pthread_attr_destroy (&attr);
 

	/*create task message queue */
	offlineManage_handle(NULL);
}
