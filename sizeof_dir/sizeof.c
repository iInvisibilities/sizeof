#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

void formatBytes(long long bytes, char* outputBuffer) {
    const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    int unitIndex = 0;
    double size = (double)bytes;

    while (size >= 1024 && unitIndex < sizeof(units) / sizeof(units[0]) - 1) {
        size /= 1024;
        unitIndex++;
    }

    sprintf(outputBuffer, "%.2f %s", size, units[unitIndex]);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "%s\n", strerror(EINVAL));
    errno = EINVAL;
    return -1;
  }
  struct stat *buf = malloc(sizeof(struct stat));

  for (int i = 1; i < argc; i++) {
    if (stat(argv[i], buf)) {
      fprintf(stderr, "[%s]\n", strerror(errno));
    }
    else {
      char *sbuf;
      formatBytes(buf -> st_size, sbuf);
      printf("%s\n", sbuf);
    }
  }
  free(buf);

  return 0;
}
