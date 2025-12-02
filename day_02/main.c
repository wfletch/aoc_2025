#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    // We iterate through each range.

    printf("Maximum value for int: %d\n", INT_MAX);
    char buffer[512];
    char range_buffer[256];
    FILE *fp = fopen("day_02_input.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }
    fgets(buffer, sizeof(buffer), fp);
    // We need to find the newline and replace it with the null terminator
    buffer[strcspn(buffer, "\n")] = '\0';
    char *save_token;
    char *token = strtok_r(buffer, ",", &save_token);
    char *save_range_token;
    long long int invalid_id_totel = 0;
    int invalid_ids_count_this_cycle =0;
    while (token != NULL) {
        invalid_ids_count_this_cycle =0;
        int index = 0;
        char *range_token = strtok_r(token,"-", &save_range_token);
        char range_start[10];
        char range_end[10];
        long long int start_range_unclamped;
        long long int start_range_value;
        long long int end_range_value;
        strcpy(range_start, range_token);
        start_range_unclamped = atoll(range_start);
        range_token = strtok_r(NULL,"-", &save_range_token);
        strcpy(range_end, range_token);
        size_t start_len = strlen(range_start);
        size_t eff_start_len = strlen(range_start);
        size_t end_len = strlen(range_end);
        size_t eff_end_len = strlen(range_end);
        if (start_len%2!=0 && end_len%2!=0) {


            // For len = 3, we can only have 1 character repeated
            // For len = 5, we can only have 1 character repeated
            // For len = 7, we can only have 1 character repated
            // For len = 9, we can have 1 character and 3 characters repeated
            token = strtok_r(NULL, ",", &save_token);
            continue;
        }
        printf("Range Start: %s\n", range_start);
        printf("Range End: %s\n", range_end);

            // We have an odd number of digits.
        // We can still clamp, but we need to be a little clever

        if (start_len%2 !=0) {
            // Increase by 1 digit length and set to 1XXXXX0
            int i;
            range_start[0] = '1';
            for (i=1; i < start_len+1; i++) {
                range_start[i] = '0';
            }
            range_start[start_len+1] = '\0';
            size_t eff_start_len = start_len + 1;

        }

        if (end_len%2 !=0) {
            // decrease by 1 digit length and set to 9XXXXX9
            int i;
            for (i=0; i < end_len-1; i++) {
                range_end[i] = '9';
            }
            range_end[end_len-1] = '\0';
            size_t eff_end_len = end_len -1;

        }

        printf("Effective Range Start: %s\n", range_start);
        printf("Effective Range End: %s\n", range_end);
        end_range_value = atoll(range_end);
        start_range_value = atoll(range_start);


        if (start_range_value != start_range_unclamped) {
            // We have clamped. Let's compensate
            printf("unclamped range\n");
        }

        range_start[eff_start_len/2] = '\0';
        range_end[eff_end_len/2] = '\0';
        printf("Effective Loop Range Start: %s\n", range_start);
        printf("Effective Loop Range End: %s\n", range_end);
        // Now that we've gated the ranges. We can start looking for duplicates
        // long long int cur_number = atoll(range_start)
        long long int current_id = atoll(range_start);
        long long int upper_bound = atoll(range_end);
        char temp_buffer[10] = "0000000000";
        while (1) {
            if (current_id > upper_bound) {
                break;
                
            }
            sprintf(temp_buffer,     "%lld", current_id);   // writes "123" starting at index 0
            sprintf(temp_buffer+ eff_end_len/2, "%lld", current_id);   // writes "456" starting at index 3
            if (atoll(temp_buffer) <= end_range_value && atoll(temp_buffer) >= start_range_value) { 
                // printf("Found an Invalid ID: %lld\n", atoll(temp_buffer));
                invalid_ids_count_this_cycle +=1;
                invalid_id_totel += atoll(temp_buffer); 
            }
            current_id +=1;
        }
        printf("Invalid IDs found in this range: %d\n", invalid_ids_count_this_cycle);
        token = strtok_r(NULL, ",", &save_token);
    }
    printf("Total Invalid IDS: %lld\n", invalid_id_totel);
}
