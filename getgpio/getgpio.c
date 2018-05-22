#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/io.h>
#include "gpio.h"

int main(int argc, char **argv) {
  int n;

  if(argc != 1) {
        printf("Usage: setgpio \n");
        exit(0);
  }

  setup_io();
  setgpiofunc(7, 0);

  n = read_from_gpio(7);

  printf("The pin value is %d\n", n);

  return EXIT_SUCCESS;
}


