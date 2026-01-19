#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>


#define MIN_LENGTH 12

const char *lowercase = "abcdefghijklmnopqrstuvwxyz";
const char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *digits    = "0123456789";
const char *symbols   = "!@#$%^&*()-_=+[]{};:,.<>?/";

unsigned int secure_random(unsigned int max) {
    unsigned int num;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        perror("urandom");
        exit(1);
    }
     
    ssize_t bytes_read = read(fd, &num, sizeof(num));
    close(fd);

    if (bytes_read != sizeof(num)) {
        fprintf(stderr, "Failed to read enough random bytes\n");
        exit(1);
    }

    unsigned int limit = UINT_MAX - (UINT_MAX % max);
    while (num >= limit) {
        read(open("/dev/urandom", O_RDONLY), &num, sizeof(num));
    }

    return num % max;
}

char random_char(const char *set) {
    return set[secure_random(strlen(set))];
}

void shuffle(char *array, int len) {
    for (int i = len - 1; i > 0; i--) {
        int j = secure_random(i + 1);
        char tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

void generate_password(char *out, int length) {
    if (length < MIN_LENGTH) {
        printf("Minimum length is %d\n", MIN_LENGTH);
        exit(1);
    }

    const char *all = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{};:,.<>?/";

    // Guarantee at least one of each type
    out[0] = random_char(lowercase);
    out[1] = random_char(uppercase);
    out[2] = random_char(digits);
    out[3] = random_char(symbols);

    // Fill the rest
    for (int i = 4; i < length; i++) {
        out[i] = random_char(all);
    }

    // Shuffle for randomness
    shuffle(out, length);

    out[length] = '\0';
}

int main() {
    int length;

    printf("Enter password length (min %d): ", MIN_LENGTH);
    scanf("%d", &length);

    char *password = malloc(length + 1);
    if (!password) {
        perror("malloc");
        return 1;
    }

    generate_password(password, length);
    printf("Generated password: %s\n\n", password);

    free(password);
    return 0;
}
