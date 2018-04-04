#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <Timer.h>
#include <data_transmission.h>

data_transmission g_transmission;
int g_count = 0;
static volatile int g_stop = 0;

void intHandler(int foo) { g_stop = 1; }

void Callback() {
  struct timespec t_now = {0, 0};
  clock_gettime(CLOCK_MONOTONIC, &t_now);
  double t_now_d = (double)(t_now.tv_sec) + (double)(t_now.tv_nsec) * 1.0e-9;
  double msg_dp[2] = {(double)g_count / 1000.0, t_now_d};
  g_transmission.send(msg_dp, 2);
  g_count++;
}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    printf(
        "\nPlease supply local and remote IP addresses (e.g. \"0.0.0.0\").\n");
    return -1;
  }

  // --- Setup transmission ---
  char *ip_local_scp = argv[1];
  char *ip_remote_scp = argv[2];
  short port_local_ss = 17777;
  short port_remote_ss = 17777;
  printf("\nSetting up transmission (%s:%d -> %s:%d)\n", ip_local_scp,
         port_local_ss, ip_remote_scp, port_remote_ss);
  g_transmission.init_transmission(ip_local_scp, port_local_ss, ip_remote_scp,
                                   port_remote_ss);

  // --- Setup the callback timer
  Timer t(Interval(1), &Callback, true);
  t.Start();
  printf("\nSending data...\n");
  printf("Press Ctrl+C to stop.\n");
  signal(SIGINT, intHandler);
  while (!g_stop) {
  }

  t.Stop();
  printf("Timer stopped.\n");
}
