#include <signal.h>

#include <data_transmission.h>

static volatile int g_stop = 0;

void intHandler(int foo) { g_stop = 1; }

int main(int argc, char *argv[]) {

  if (argc < 3) {
    printf(
        "\nPlease supply local and remote IP addresses (e.g. \"0.0.0.0\").\n");
    return -1;
  }

  // --- Setup transmission ---
  data_transmission transmission_rcv;
  data_transmission transmission_snd;
  char *ip_local_scp = argv[1];
  char *ip_remote_scp = argv[2];
  short port_local_rcv_ss = 17777;
  short port_local_snd_ss = 17778;
  short port_remote_ss = 17778;
  printf("\nSetting up loopback (%s:%d -> %s:%d)\n", ip_local_scp,
         port_local_rcv_ss, ip_remote_scp, port_remote_ss);
  transmission_rcv.init_transmission(ip_local_scp, port_local_rcv_ss);
  transmission_snd.init_transmission(ip_local_scp, port_local_snd_ss,
                                     ip_remote_scp, port_remote_ss);

  printf("\nListening for data...\n");
  printf("Press Ctrl+C to stop.\n");
  char message_ucp[1024];
  signal(SIGINT, intHandler);
  while (!g_stop) {
    transmission_rcv.listen(message_ucp, sizeof(double) * 2);
    transmission_snd.send(message_ucp, sizeof(message_ucp));
  }
}
