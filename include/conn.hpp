#ifndef CONN_MANAGER_H
#define CONN_MANAGER_H

#include "storage.hpp"

class ConnectionManager
{
public:
  int setup_srv(int *acpt_skt);
  int send_data(int *acpt_skt,char *buf,int buflen);

private:
  int spd;
};

#endif
