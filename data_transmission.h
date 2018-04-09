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

/** \brief The class data_transmission containing convenience functions for
 *         intilizing UDP sockets and transmitting data.
 *
 */
class data_transmission{
  private:
    struct sockaddr_in local;
    struct sockaddr_in remote;
    int remotelen, socketS;
    int do_send(char* buffer_scp, int len);
  public:

    /**
     * Initializes a UDP socket for sending data to a specific IP address.
     * @param ip_local_scp The local IP address. Can be used to choose the
     *                     network interface via which to send data.
     * @param port_local_ss The local port
     * @param ip_remote_scp The remote IP address.
     * @param port_local_ss The remote port.
     */
    int init_transmission(
        char* ip_local_scp, short port_local_ss,
        char* ip_remote_scp, short port_remote_ss);
    /**
     * Initializes a UDP socket for receiving data from a specific IP address.
     * @param ip_address_scp The local IP address. The socket binds to this IP
     *                       address.
     * @param port The local port at which data is received.
     */
    int init_transmission(char* ip_address_scp, short port);
    /**
     * Initializes a UDP socket for receiving data from a specific IP address.
     * Additionally, the receive buffer SO_RCVBUF can be set.
     * @param ip_local_scp The local IP address. The socket binds to this IP
     *                     address.
     * @param port The local port at which data is received.
     * @param rcvbuf_len Sets the length of SO_RCVBUF.
     * @see http://man7.org/linux/man-pages/man7/socket.7.html
     */
    int init_transmission(char* ip_address_scp, short port, int rcvbuf_len);
    /**
     * Sends a package containing an array of signed chars to the remote host
     * defined via init_transmission().
     * @param array_scp Pointer to the array of chars to be sent to the
     *                  remote host.
     * @param len The array length.
     */
    int send(char* array_scp, int len);
    /**
     * Sends a package containing an array of double-precision floats to the
     * remote host defined via init_transmission().
     * @param number_dbp Pointer to the array of doubles to be sent to the
     *                   remote host.
     * @param len The array length.
     */
    int send(double* number_dbp, int len);
    /**
     * Sends a package containing an array of floats to the remote host defined
     * via init_transmission().
     * @param array_flp Pointer to the array of floats to be sent to the
     *                  remote host.
     * @param len The array length.
     */
    int send(float* array_flp, int len);
    /**
     * Sends a package containing an array of signed integers to the remote host
     * defined via init_transmission().
     * @param array_sip Pointer to the array of integers to be sent to the
     *                  remote host.
     * @param len The array length.
     */
    int send(int* array_sip, int len);
    /**
     * Sends a package containing an array of signed short to the remote host
     * defined via init_transmission().
     * @param array_ssp Pointer to the array of shorts to be sent to the
     *                  remote host.
     * @param len The array length.
     */
    int send(short* number_ssp, int len);
    /**
     * Listens for packages from the remote host defined via init_transmission().
     * Calls to this functions are blocking calls.
     * @param buffer_scp Pointer to the char array to store the received data
     *                   in.
     * @param len The array length.
     */
    int listen(char* buffer_scp, int len);
    /**
     * Function is not implemented, yet.
     */
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
