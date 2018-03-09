#ifndef DATA_TRANSMISSION_H
#define DATA_TRANSMISSION_H

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>      //memset
#include <sys/types.h>
#include <netinet/in.h>

using namespace std;

class data_transmission{
  private:
    struct sockaddr_in local;
    struct sockaddr_in remote;
    int remotelen, socketS;
    int do_send(char* buffer_scp, int len);
  public:
    int init_transmission(
        char* ip_local_scp, short port_local_ss,
        char* ip_remote_scp, short port_remote_ss);
    int init_transmission(char* ip_address_scp, short port);
    int send(char* array_scp, int len);
    int send(double* number_dbp, int len);
    int send(float* array_flp, int len);
    int send(int* array_sip, int len);
    int send(short* number_ssp, int len);
    int listen(char* buffer_scp, int len);
    int close_transmission();

    void num2charray(short in_ss, char* out_scp);
    void num2charray(short in_ss, char* out_scp, int* len_out_sip);
    void num2charray(unsigned short in_us, char* out_scp);
    void num2charray(unsigned short in_us, char* out_scp, int* len_out_sip);
    void charray2num(char* in_scp, short* out_ssp);

    short chararray2short(unsigned char *in_ch);
    unsigned char* short2chararray(short in_sh);
    unsigned char* short2chararray(unsigned short in_sh);
};

#endif
