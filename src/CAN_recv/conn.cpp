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
  this->skt = 0;

  struct sockaddr_in addr;
  this->skt = socket(AF_INET,SOCK_STREAM,0);

  if(skt < 0){
    perror("[ERR] Opening socket failure.");
    exit(1);
  }

  /* Configure Socket */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(50000);
  addr.sin_addr.s_addr = INADDR_ANY;

  if(-1 == bind(this->skt,(struct sockaddr *)&addr,sizeof(addr)) ){
    perror("[ERR] Binding failure");
    close(skt);
    return -1;
  }

  if(listen(this->skt,CAPACITY_CONN_NUM) == -1){
    perror("[ERR] Listening failure");
    return -1;
  }

  // *acpt_skt = 0;
  // struct sockaddr_in acpt_addr;
  // socklen_t len = sizeof(acpt_addr);
  // *acpt_skt = accept(this->skt,(struct sockaddr *)&acpt_addr,&len);
  //
  // printf("Accepted!\n");
  conn_srv(acpt_skt);

  return 0;
}

int ConnectionManager::conn_srv(int *acpt_skt){
  assert(this->skt >= 0);

  printf("Connecting...\n");

  struct sockaddr_in acpt_addr;
  socklen_t len = sizeof(acpt_addr);
  *acpt_skt = accept(this->skt,(struct sockaddr *)&acpt_addr,&len);

  printf("Accepted!\n");
}

result_t ConnectionManager::send_data(int *acpt_skt,char *buf,int buflen, int *sent_len)
{
  assert(acpt_skt != NULL);
  assert(sent_len != NULL);
  assert(buf != NULL);

  int flags = EPIPE;
  int sent_retval = 0;
  int sent_amount = 0;
  int bytesizeTobeSend = 0;
  bytesizeTobeSend = strlen(buf) * sizeof(char);
  if(bytesizeTobeSend > buflen){
    fprintf(stderr,"[WRN] Send data exceeds buffer size\n");
    bytesizeTobeSend = buflen;
  }

  while(sent_amount < bytesizeTobeSend){
    sent_retval = send(*acpt_skt,(buf+sent_amount),bytesizeTobeSend,flags);
    if(sent_retval == -1){
      perror("[WRN] func send() returned errno:");
      return FAIL;
    }

    sent_amount += sent_retval;
    printf("Sent:%s(%d bytes)\n",buf,sent_amount);
  }

  *sent_len = sent_amount;

  return OK;
}
