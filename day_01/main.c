#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("day_01_input.txt", "r");
    int cur_loc = 50;
    int cycle_length = 100;
    int zero_count = 0;
    char buffer[256];
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("Start: %d\n", cur_loc);
        buffer[strcspn(buffer, "\n")] = '\0';
        char direction = buffer[0];
        int rot_value = atoi(&buffer[1])%100;
        int rot_offset = atoi(&buffer[1])/100;
        printf("OFFSET: %d\n", rot_offset);
        zero_count += rot_offset;
        printf("Move: %d\n", rot_value);
        printf("Direction: %c\n", direction);
        if (direction == 'L') {
            if (cur_loc - rot_value < 0 && cur_loc != 0){
                zero_count += 1;
            }
            // We are moving Left 
            cur_loc = cur_loc - rot_value;
        } else if (direction == 'R'){
            if (cur_loc + rot_value > 100 && cur_loc != 0){
                zero_count += 1;
            }
            // We are moving Right 
            cur_loc = cur_loc + rot_value;
        }
        else {
            printf("Unspecified Direction %c\n", direction);
            return -1;
        }
        printf("Mid: %d\n", cur_loc);
        if (cur_loc > 0) {
            cur_loc = cur_loc%100; 
        }
        else if (cur_loc < 0) {
            cur_loc = (cycle_length + cur_loc)%100;
        }
        if (cur_loc == 0) {
            zero_count+=1;
        }
        printf("End: %d Zero Count: %d\n\n", cur_loc, zero_count);
    }
    printf("ZERO COUNT: %d\n", zero_count);

    return 0;
}
