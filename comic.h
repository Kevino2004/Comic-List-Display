/**
 * These are the function signatures for the required C functions in 
 * this assignment.
 */ 

#ifndef COMIC_H
#define COMIC_H
#include <stdio.h>

// Comic and Comic list structs
struct Comic {
    char* date;
    char* code;
    char* publisher;
    char* title;
    char* cost;
};

struct Comic_List {
    struct Comic* list;
    int size;
    int count;
};

// Function declarations
void load(struct Comic_List* list, const char* filename, FILE* output_file);
void buy(struct Comic_List* main_list, struct Comic_List* purchase_list, int index, FILE* output_file);
void checkout(struct Comic_List* purchase_list, FILE* output_file);
void display(struct Comic_List* list, FILE* output_file);
void save(struct Comic_List* list, const char* filename);
void clear(struct Comic_List* list);
void find(struct Comic_List* list, int index, FILE* output_file);
void remove_comic(struct Comic_List* list, int index, FILE* output_file);

#endif
