#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    FILE *fp = fopen("day_03_input.txt", "r");
    char buffer[256];
    int max;
    int max_2;
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }
    int overall_total = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Battery Values: %s\n", buffer);
        size_t battery_length = strlen(buffer);
        printf("Battery Langth: %lu\n", battery_length);
        int total_so_far = 0;
        for (int i =0; i < battery_length; i++) {
            if (isdigit(buffer[i])) {
                int bat_1 = buffer[i] - '0';
                for (int j = i+1; j < battery_length;j++){
                    if (isdigit(buffer[j])) {
                        int bat_2 = buffer[j] - '0';
                        if ((bat_1 * 10) + bat_2 > total_so_far) {
                            total_so_far = (bat_1*10) + bat_2;
                        }

                    }
                }
            }
        }
        overall_total+=total_so_far;
        printf("Overall Jolts: %i\n", overall_total);

    }

    return 0;
}
