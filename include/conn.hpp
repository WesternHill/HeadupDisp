#ifndef CONN_MANAGER_H
#define CONN_MANAGER_H

#include "storage.hpp"
#include "type.hpp"

class ConnectionManager
{
public:
  int setup_srv(int *acpt_skt);
  result_t send_data(int *acpt_skt,char *buf,int buflen, int *sent_len);
  int conn_srv(int *acpt_skt);

private:
  int spd;
  int skt;
};

#endif
