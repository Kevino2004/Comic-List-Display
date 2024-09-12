#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comic.h"
#define BUFFER3 1000
#define BUFFER2 100
#define BUFFER1 10

void load(struct Comic_List* list, const char* filename, FILE* output_file) {
    // Open file
    FILE* file = fopen(filename, "r");

    // Skip the header line
    char header[BUFFER3];
    fgets(header, BUFFER3, file);

    // String buffers to store the parsed data with apropriate sizes
    // Initialize i as a tally for how many comics are read
    char buffer1[100];
    char buffer2[100];
    char buffer3[100];
    char buffer4[1000];
    char buffer5[10];
    int i = 0;

    // Read comics
    while (fscanf(file, " %[^,],%[^,],%[^,],%[^,],%[^\n]", buffer1, buffer2, buffer3, buffer4, buffer5) != EOF) {

        // Reallocate memory if the array is full
        if ((*list).count == (*list).size) {
            // Double the size of the list
            (*list).size *= 2;
            (*list).list = realloc((*list).list, (*list).size * sizeof(struct Comic));
        }

        // Allocate memory for each of the data fields
        list->list[list->count].date = strdup(buffer1);
        list->list[list->count].code = strdup(buffer2);
        list->list[list->count].publisher = strdup(buffer3);
        list->list[list->count].title = strdup(buffer4);
        list->list[list->count].cost = strdup(buffer5);

        // Increment the comic lists count so that new memory is stored for each new comic
        list->count++;
        i++;
    }
    // Close the file and print the tally i to display the amount of comics stored
    fclose(file);
    fprintf(output_file, "    Number of comics: %d\n", i);
}

static void print_comic(struct Comic comic, FILE* output_file) {
    // Simply print to the output file all of the comics data with proper indentation
    fprintf(output_file, "    Date: %s\n", comic.date);
    fprintf(output_file, "    Code: %s\n", comic.code);
    fprintf(output_file, "    Publisher: %s\n", comic.publisher);
    fprintf(output_file, "    Title: %s\n", comic.title);
    fprintf(output_file, "    Cost: %s\n", comic.cost);
}

void buy(struct Comic_List* main_list, struct Comic_List* purchase_list, int index, FILE* output_file) {
    // Ensure that the given index is in bounds
    if (index >= 0 && index < main_list->count) {
        // Check if the purchase list needs more memory
        if (purchase_list->count == purchase_list->size) {
            // Double the size of the purchase list
            purchase_list->size *= 2;
            purchase_list->list = realloc(purchase_list->list, purchase_list->size * sizeof(struct Comic));
        }
        // add the comic from the main list to the purchase list and increment the purchase lists count
        purchase_list->list[purchase_list->count++] = main_list->list[index];
        fprintf(output_file, "Comic #%d added to purchase list\n", index);
    } 
    else {
        // If index is out bounds print unable to buy
        fprintf(output_file, "Unable to buy comic #%d\n", index);
    }
}

void checkout(struct Comic_List* purchase_list, FILE* output_file) {
    // Initialize required variables with the tax rate at 5%.
    double subtotal = 0.0;
    double tax = 0.05;
    double total = 0.0;
    struct Comic comic;

    // Print comics in purchase list and calculate subtotal
    fprintf(output_file, "Comics in Purchase List\n");
    for (int i = 0; i < purchase_list->count; i++) {
        comic = purchase_list->list[i];
        fprintf(output_file, "Comic Number: %d\n", i + 1);
        print_comic(comic, output_file);

        // Calculate subtotal
        if (strcmp(comic.cost, "AR") != 0) {
            subtotal += atof(comic.cost + 1);
        }
    }

    // Calculate total after tax
    total = subtotal * (1 + tax);

    // Print appropriate variables
    fprintf(output_file, " Subtotal: $%.2f\n", subtotal);
    fprintf(output_file, "      Tax: $%.2f\n", subtotal * tax);
    fprintf(output_file, "    Total: $%.2f\n", total);

    // Clear the purchase list
    purchase_list->count = 0;
}

void display(struct Comic_List* list, FILE* output_file) {
    // Print empty if list is empty
    if (list->count == 0) {
        fprintf(output_file, "List is currently empty.\n");
    }
    // Iterate through all of the comics in the list, printing with helper function
    for (int i = 0; i < list->count; i++) {
        fprintf(output_file, "Comic Number: %d\n", i + 1);
        print_comic(list->list[i], output_file);
    }
}

void save(struct Comic_List* list, const char* filename) {
    // Open file
    FILE* file = fopen(filename, "w");

    // Write comics to the file with a filler header line to not interfere with load
    fprintf(file, "HEADER LINE\n");
    for (int i = 0; i < list->count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s\n", list->list[i].date, list->list[i].code, 
                list->list[i].publisher, list->list[i].title, list->list[i].cost);
    }
    // Close file
    fclose(file);
}

void clear(struct Comic_List* list) {
    // Free memory allocated for comics
    for (int i = 0; i < list->count; i++) {
        free(list->list[i].date);
        free(list->list[i].code);
        free(list->list[i].publisher);
        free(list->list[i].title);
        free(list->list[i].cost);
    }
    // Reset count to 0
    list->count = 0;
}

void find(struct Comic_List* list, int index, FILE* output_file) {
    // Check if there is a comic at given index and print respective comic
    if (index >= 0 && index < list->count) {
        print_comic(list->list[index], output_file);
    } 
    
    else {
        // Print comic was not in the list
        fprintf(output_file, "There is no comic at index #%d in the list.\n", index);
    }
}

void remove_comic(struct Comic_List* list, int index, FILE* output_file) {
    // Ensure index is in bounds
    if (index >= 0 && index < list->count) {
        // Free memory allocated for the comic to be removed
        free(list->list[index].date);
        free(list->list[index].code);
        free(list->list[index].publisher);
        free(list->list[index].title);
        free(list->list[index].cost);

        // Shift comics after the removed comic one position to the left
        for (int i = index; i < list->count - 1; i++) {
            list->list[i] = list->list[i + 1];
        }

        // Print comic removed successfully
        fprintf(output_file, "Comic at index %d successfully removed\n", index);

        // Decrease count
        list->count--;
    }
    else {
        // Print comic was not removed
        fprintf(output_file, "Comic at index %d was not removed\n", index);
    }
}

