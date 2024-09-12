#include <stdio.h>
#include <stdlib.h>
#include "comic.h"
#include <string.h>
#define BUFFER 100

int main(int argc, char* argv[]) {
    // Ensure correct number of arguments are entered.
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <commands_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Create the main list and purchase list.
    struct Comic_List main_list = {.size = 10, .count = 0};
    struct Comic_List purchase_list = {.size = 10, .count = 0};

    // Allocate memory for 10 comics in main list and purchase list.
    main_list.list = malloc(10 * sizeof(struct Comic));
    purchase_list.list = malloc(10 * sizeof(struct Comic));

    // Open the entered command file and output file.
    FILE* commands_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");

    // String and int variables to store the parsed commands. 
    char command[BUFFER];
    int index;

    // Parse through the command file as a while loop for each command till the end of the file.
    // Store the command in a string and string compare to the valid commands.
    // Run the proper commands to match output display and input parameters for the comic.c functions.
    while (fscanf(commands_file, "%s", command) != EOF) 
    {
        if (strcmp(command, "load") == 0) 
        {
            char filename[BUFFER];
            fscanf(commands_file, "%s", filename);
            fprintf(output_file, "Command: %s %s\n", command, filename);
            load(&main_list, filename, output_file);
        } 
        else if (strcmp(command, "buy") == 0) 
        {
            fscanf(commands_file, "%d", &index);
            fprintf(output_file, "Command: %s %d\n", command, index);
            buy(&main_list, &purchase_list, index, output_file);
        } 
        else if (strcmp(command, "checkout") == 0) 
        {
            fprintf(output_file, "Command: %s\n", command);
            checkout(&purchase_list, output_file);
        } 
        else if (strcmp(command, "display") == 0) 
        {
            fprintf(output_file, "Command: %s\n", command);
            display(&main_list, output_file);
        } 
        else if (strcmp(command, "save") == 0) 
        {
            char filename[BUFFER];
            fscanf(commands_file, "%s", filename);
            fprintf(output_file, "Command: %s %s\n", command, filename);
            save(&main_list, filename);
        } 
        else if (strcmp(command, "clear") == 0) 
        {
            fprintf(output_file, "Command: %s\n", command);
            clear(&main_list);
        } 
        else if (strcmp(command, "find") == 0) 
        {
            fscanf(commands_file, "%d", &index);
            fprintf(output_file, "Command: %s %d\n", command, index);
            find(&main_list, index, output_file);
        } 
        else if (strcmp(command, "remove") == 0) 
        {
            fscanf(commands_file, "%d", &index);
            fprintf(output_file, "Command: %s %d\n", command, index);
            remove_comic(&main_list, index, output_file);
        } 
        else 
        {
            fprintf(stderr, "Invalid command: %s\n", command);
        }
    }

    // Close the files after use and free all allocated memory.
    fclose(commands_file);
    fclose(output_file);
    clear(&main_list);
    clear(&purchase_list);
    free(main_list.list);
    free(purchase_list.list);

    return EXIT_SUCCESS;
}
