#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void usage(char*);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    int mood = strtoul(argv[1], NULL, 10);

    if (mood == 0 || mood > 7) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    time_t current_time = time(NULL);
    struct tm *buf = localtime(&current_time);

    if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to obtain the current time.\n");
        exit(EXIT_FAILURE);
    }

    char *home = getenv("HOME");
    if (!home || !*home ) {
        fprintf(stderr, "Define $HOME.\n");
        exit(EXIT_FAILURE);
    }

    // The length of our base directory path
    size_t blen = strlen(home) + strlen("/.mood/");
    char* basepath = malloc(blen + 1);
    basepath[blen] = '\0';

    snprintf(basepath, blen, "%s/.mood/", home);

    struct stat st = {0};
    if (stat(basepath, &st) == -1) {
        mkdir(basepath, 0750);
    }

    size_t filelen = strlen("YYYY-MM.txt");

    char* filename = malloc(filelen + 1);
    strftime(filename, filelen+1, "%Y-%m.txt", buf);

    // The lenght of the final path
    size_t psize = blen + filelen;
    char* path = malloc(psize + 1);
    path[psize] = '\0';
    snprintf(path, psize+1, "%s/%s", basepath, filename);

    FILE *ft = fopen(path, "a");

    const size_t tslen = sizeof("YYYYMMDDHHMMSS");
    char timestamp[tslen+1];
    timestamp[tslen] = '\0';
    strftime(timestamp, tslen, "%Y%m%d%H%M%S", buf);
    fprintf(ft, "%s %d\n", timestamp, mood);

    fclose(ft);

    exit(EXIT_SUCCESS);
}


void usage(char* bin) {
    fprintf(stderr, "usage: %s <current mood>\n"
                    "\n"
                    "mood can be an integer between 1 and 7 (1 lowest, 7 highest)\n"
            , bin);
}
