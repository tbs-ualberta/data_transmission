#include <data_transmission/data_transmission.h>

#ifdef WIN32
  void data_transmission::InitWinsock()
  {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
      printf("\nWSAStartup failed with error: %d\n", iResult);
    }
  }
#endif

void die(char *s){
  perror(s);
}

int data_transmission::init_transmission(
    char* ip_local_scp, short port_local_ss){

  // zero out the structure
  memset((char *) &local, 0, sizeof(local));
  local.sin_family = AF_INET;
  local.sin_port = htons(port_local_ss);
  local.sin_addr.s_addr = inet_addr(ip_local_scp);
  remotelen = sizeof(remote);

  #ifdef WIN32
    int error = 0;
    InitWinsock();

    //TODO Add error check (same as linux implementation)
    socketS = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bind(socketS, (sockaddr*)&local, sizeof(local));
    if (socketS == INVALID_SOCKET) {
      die("socket");
      error = WSAGetLastError();
      WSACleanup();
    }

    return error;

  #elif __linux__

    if ((socketS = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
      die("socket");
      return -1;
    }

    // bind the socket to the local IP and port
    if (bind(socketS, (struct sockaddr*)&local, sizeof(local)) == -1) {
      die("bind");
      return -1;
    }
    return socketS;
  #endif
}

int data_transmission::init_transmission(
    char* ip_local_scp, short port_local_ss, int rcvbuf_len){

  // zero out the structure
  memset((char *) &local, 0, sizeof(local));
  remotelen = sizeof(remote);
  local.sin_family = AF_INET;
  local.sin_port = htons(port_local_ss);
  local.sin_addr.s_addr = inet_addr(ip_local_scp);

  #ifdef WIN32
    int error = 0;
    InitWinsock();

    //TODO Add error check (same as linux implementation)
    socketS = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    char rcvbuf_len_uc = (char)rcvbuf_len;
    setsockopt(socketS, SOL_SOCKET, SO_RCVBUF, &rcvbuf_len_uc, sizeof(rcvbuf_len_uc));

    bind(socketS, (sockaddr*)&local, sizeof(local));

    if (socketS == INVALID_SOCKET) {
      die("socket");
      error = WSAGetLastError();
      WSACleanup();
    }

    return error;

  #elif __linux__
    if ((socketS = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
      die("socket");
      return -1;
    }

    if (setsockopt(socketS, SOL_SOCKET, SO_RCVBUF, &rcvbuf_len,
        sizeof(rcvbuf_len)) == -1) {
      die("setsockopt SO_RCVBUF");
      return -1;
    }

    // bind the socket to the local IP and port
    if (bind(socketS, (struct sockaddr*)&local, sizeof(local)) == -1) {
      die("bind");
      return -1;
    }
    return socketS;
  #endif
}

int data_transmission::init_transmission(
    char* ip_local_scp, short port_local_ss,
    char* ip_remote_scp, short port_remote_ss){

  memset((char *) &remote, 0, sizeof(remote));
  remotelen = sizeof(remote);
  local.sin_family = AF_INET;
  local.sin_port = htons(port_local_ss);
  local.sin_addr.s_addr = inet_addr(ip_local_scp);
  remote.sin_family = AF_INET;
  remote.sin_port = htons(port_remote_ss);
  remote.sin_addr.s_addr = inet_addr(ip_remote_scp);

  #ifdef WIN32
    int error = 0;
    InitWinsock();
    socketS = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketS == INVALID_SOCKET) {
      error = WSAGetLastError();
      WSACleanup();
    }

    return error;
  #elif __linux__
    //create a UDP socket
    if ((socketS = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
      die("socket");
      return -1;
    }
    if (inet_aton(ip_remote_scp, &remote.sin_addr) == 0) {
      fprintf(stderr, "inet_aton() failed\n");
      return -1;
    }

    return socketS;
  #endif
}

int data_transmission::do_send(char* buffer_scp, int len){

  #ifdef WIN32
    int error = 0;
      if(sendto(socketS, buffer_scp, len, 0, (sockaddr*)&remote, remotelen)
                == SOCKET_ERROR){
      error = WSAGetLastError();
      die("sendto()");
    }
  #elif __linux__
    if(sendto(socketS, buffer_scp, len, 0, (struct sockaddr*)&remote, remotelen)
              == -1){
      die("sendto()");
    }
  #endif
  return 0;
}

int data_transmission::send(char* array_scp, int len){
  return do_send((char*)array_scp, len);
}

int data_transmission::send(double* array_dbp, int len){
  return do_send((char*)array_dbp, len*8);
}

int data_transmission::send(float* array_flp, int len){
  return do_send((char*)array_flp, len*4);
}

int data_transmission::send(int* array_sip, int len){
  return do_send((char*)array_sip, len*4);
}

int data_transmission::send(short* array_ssp, int len){
  return do_send((char*)array_ssp, len*2);
}

int data_transmission::listen(char* buffer_scp, int len){
  //try to receive some data, this is a blocking call
  //memset(buffer_scp,'\0', len);
  #ifdef WIN32
    int error = 0;
    if(recvfrom(socketS, buffer_scp, len, 0, (sockaddr*)&remote, &remotelen)
                == SOCKET_ERROR){
      error = WSAGetLastError();
      die("recvfrom()");
    }
    return error;
  #elif __linux__
    if(recvfrom(
        socketS, buffer_scp, len, 0, (struct sockaddr*)&remote, (socklen_t*)&remotelen)
        == -1){
      die("recvfrom()");
      return -1;
    }
    return 0;
  #endif
}

int data_transmission::close_transmission(){
  #ifdef __linux__
	  ::close(socketS);
  #endif
  return 0;
}

void data_transmission::num2charray(short in_ss, char* out_scp){
  out_scp = (char*)&in_ss;
}

void data_transmission::num2charray(
    short in_ss, char* out_scp, int* len_out_sip){
  out_scp = (char*)&in_ss;
  *len_out_sip = 2;
}

void data_transmission::num2charray(unsigned short in_us, char* out_scp){
  out_scp = (char*)&in_us;
}

void data_transmission::num2charray(
    unsigned short in_us, char* out_scp, int* len_out_sip){
  out_scp = (char*)&in_us;
  *len_out_sip = 2;
}

void data_transmission::charray2num(char* in_scp, short* out_ssp){
  out_ssp = (short*)in_scp;
}

short data_transmission::chararray2short(unsigned char *in_ch){
  short temp = in_ch[0];
  temp = temp << 8;
  return temp | in_ch[1];
}

unsigned char* data_transmission::short2chararray(short in_sh){
  unsigned char temp[2];
  temp[0] = (in_sh >> 8) & 0xFF;
  temp[1] = in_sh & 0x00FF;
  return temp;
}

unsigned char* data_transmission::short2chararray(unsigned short in_sh){
  unsigned char temp[2];
  temp[0] = (in_sh >> 8) & 0xFF;
  temp[1] = in_sh & 0x00FF;
  return temp;
}

#ifdef __linux__
  bool data_transmission::setNonBlocking(int sockfd) {
      int flag = fcntl(sockfd, F_GETFL, 0);
      if (flag < 0) {
          perror("fcntl F_GETFL fail");
          return false;
      }
      if (fcntl(sockfd, F_SETFL, flag | O_NONBLOCK) < 0) {
          perror("fcntl F_SETFL fail");
          return false;
      }
      return true;
  }
#endif
