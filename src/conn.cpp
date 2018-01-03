#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>


#include "conn.hpp"

#define CAPACITY_CONN_NUM 10


int ConnectionManager::setup_srv(int *acpt_skt)
{
  assert(acpt_skt != NULL);
  int skt = 0;

  struct sockaddr_in addr;
  skt = socket(AF_INET,SOCK_STREAM,0);

  if(skt < 0){
    perror("[ERR] Opening socket failure.");
    exit(1);
  }

  /* Configure Socket */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(50000);
  addr.sin_addr.s_addr = INADDR_ANY;

  if(-1 == bind(skt,(struct sockaddr *)&addr,sizeof(addr)) ){
    perror("[ERR] Binding failure");
    close(skt);
    return -1;
  }

  if(listen(skt,CAPACITY_CONN_NUM) == -1){
    perror("[ERR] Listening failure");
    return -1;
  }

  *acpt_skt = 0;
  struct sockaddr_in acpt_addr;
  socklen_t len = sizeof(acpt_addr);
  *acpt_skt = accept(skt,(struct sockaddr *)&acpt_addr,&len);

  printf("Accepted!\n");

  return 0;
}

int ConnectionManager::send_data(int *acpt_skt,char *buf,int buflen)
{
  int flags = 0;
  int sent_amount = 0;
  int bytesizeTobeSend = 0;
  bytesizeTobeSend = strlen(buf) * sizeof(char);
  if(bytesizeTobeSend > buflen){
    fprintf(stderr,"[WRN] Send data exceeds buffer size\n");
    bytesizeTobeSend = buflen;
  }

  while(sent_amount < bytesizeTobeSend){
    sent_amount += send(*acpt_skt,(buf+sent_amount),bytesizeTobeSend,flags);
    printf("Sent:%s(%d bytes)\n",buf,sent_amount);
  }

  return sent_amount;
}
