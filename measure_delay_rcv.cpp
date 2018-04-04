#include <signal.h>
#include <stdio.h>
#include <string>
#include <time.h>

#include <data_transmission.h>
#include <fcsv.h>

static volatile int g_stop = 0;

void intHandler(int foo) { g_stop = 1; }

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("\nPlease supply local IP address (e.g. \"0.0.0.0\").\n");
    return -1;
  }

  // --- Setup name of csv file
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char filename_ucp[1024];
  sprintf(filename_ucp, "%d-%02d-%02d-%02d-%02d-%02d.csv", tm.tm_year + 1900,
          tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  std::string filename_st(filename_ucp);

  // --- Setup transmission ---
  data_transmission transmission;
  char *ip_local_scp = argv[1];
  short port_local_ss = 17778;
  printf("\nSetting up transmission (listening on %s:%d)\n", ip_local_scp,
         port_local_ss);
  transmission.init_transmission(ip_local_scp, port_local_ss);

  // --- Setup fCSV ---
  struct fCSV *fcsv = fcsv_create();
  struct fRow *row_fcsv = 0;
  row_fcsv = fcsv_first_row(fcsv);
  fcsv_set_fields_count(row_fcsv, 3);
  fcsv_set_field(row_fcsv, 0, "count");
  fcsv_set_field(row_fcsv, 1, "t_snd");
  fcsv_set_field(row_fcsv, 2, "t_rcv");

  printf("\nListening for data...\n");
  printf("Press Ctrl+C to stop.\n");
  char message_ucp[1024];
  signal(SIGINT, intHandler);
  while (!g_stop) {
    transmission.listen(message_ucp, sizeof(double) * 2);
    // Convert to double
    double *message_dp = (double *)message_ucp;

    // --- Get current time stamp ---
    struct timespec t_now = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &t_now);
    double t_now_d = (double)(t_now.tv_sec) + (double)(t_now.tv_nsec) * 1.0e-9;

    // --- Write to .csv ---
    row_fcsv = fcsv_insert_row(row_fcsv);
    fcsv_set_fields_count(row_fcsv, 3);
    char num_ucp[25];
    sprintf(num_ucp, "%1.15e", message_dp[0]);
    fcsv_set_field(row_fcsv, 0, num_ucp);
    sprintf(num_ucp, "%1.15e", message_dp[1]);
    fcsv_set_field(row_fcsv, 1, num_ucp);
    sprintf(num_ucp, "%1.15e", t_now_d);
    fcsv_set_field(row_fcsv, 2, num_ucp);
  }

  // --- Save the data to a file ---
  fcsv_save(fcsv, filename_ucp);
  fcsv_close(fcsv);

  printf("\n");

  return 0;
}
