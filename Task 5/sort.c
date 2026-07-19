/*==================================Includes=================================*/



#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 256



/*===============================Insertion Sort==============================*/



/* sort linked list *list using merge insertion sort. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */
void insertion_sort(LinkedList *list, int (*compare)(void *, void *))
{
	Node *node;
    Node *temp;
    LinkedList *sorted;
    int comp;

    /* Initialise Linked List */
    sorted = initialise_linked_list();


    /*Moves the first item in the original list into the sorted list*/
    append_linked_list(sorted, list->head->data);
    remove_head_linked_list(list);

    while(list->head != NULL)
    {
        node = sorted->head;

        while(node)
        {
        	/*Compares the next element to be sorted to the element in sorted*/
            comp = (*compare)(list->head->data, node->data);

            /* Item needs to go in the place before */
            if(comp < 0)
            {
            	 /* Checks if the item needs to go to the front of the list */
                if(node->prev == NULL)
                {
                    prepend_linked_list(sorted, list->head->data);
                    remove_head_linked_list(list);
                }

                else
                {
                	/* INSERT INTO POSITION */
                    temp = initialise_node();
                    temp->data = list->head->data;
                    temp->next = node;
                    temp->prev = node->prev;
                    node->prev->next = temp;
                    node->prev = temp;
                    remove_head_linked_list(list);
                }
                break;
            }
            node = node->next;
        }

        if(!node)
        {
            append_linked_list(sorted, list->head->data);
            remove_head_linked_list(list);
        }


    }

    /* Moves the sorted list back into main list */
    while(sorted->head != NULL)
    {
        append_linked_list(list, sorted->head->data);
        remove_head_linked_list(sorted);
    }

    /* Free sorted linked list */
    free_linked_list(sorted);
}



/*=================================Merge Sort================================*/



/* sort linked list *list using merge sort algorithm. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */
/* Breaks the arrayay down into individual segements */
void merge_sort(LinkedList *list, int (*compare)(void *, void *))
{
    void merge_breakdown(char **, int, int);


    int list_len, i;
    char **array;
    void *reset;


    /* calculates number of elements in linked list */
    list_len = 0;
    reset = list->head;
    while(list->head != NULL){
        list_len++;
        list->head = list->head->next;
    }
    list->head = reset;



    /* Allocates memory to array */
    if(!(array = calloc(list_len, sizeof(char *))))
    {
        fprintf(stderr, "Error: Memory\n");
        exit(EXIT_FAILURE);
    }


    /* Moves everything from linked list to the array */
    for(i = 0; i < list_len; i++)
    {
        array[i] = list->head->data;
        remove_head_linked_list(list);
    }



    /* Runs Merge Sort Algorithm */
    merge_breakdown(array, 0, list_len - 1);



    /* Move sorted array into linked list */
    for(i = 0; i < list_len; i++)
    {
        append_linked_list(list, array[i]);
    }


    /* Frees array */
    free(array);
}



/* Breaks down the array into individual elements */
void merge_breakdown(char** array, int low_value, int high_value) 
{
    void merge_rebuild(char **, int, int, int);



    int middle_value = 0;


    if(low_value < high_value)
    {
        /* Breaks the array down into individual segements */
        middle_value = (low_value + high_value) / 2;
        merge_breakdown(array, low_value, middle_value);
        merge_breakdown(array, middle_value + 1, high_value);

        /* Rebuilds the array */
        merge_rebuild(array, low_value, middle_value, high_value);
    }
}


/* Rebuilds the array */
void merge_rebuild(char** array, int low_value, int middle_value, int high_value) 
{
    int left_size, right_size;
    int i, x;
    char **left_half, **right_half;



    /* Calculates the size of the left and right halves */
    left_size = middle_value - low_value + 1;
    right_size = high_value - middle_value;
    




     /* Allocates memory to the left and right arrays */
    if(!(left_half = calloc(left_size, sizeof(char *))))
    {
        fprintf(stderr, "Error: Memory\n");
        exit(EXIT_FAILURE);
    }



    if(!(right_half = calloc(right_size, sizeof(char *))))
    {
        fprintf(stderr, "Error: Memory\n");
        exit(EXIT_FAILURE);
    }


    




    /* Puts the left half of array into left_half */
    for(i = 0; i < left_size; i++)
    {
        if(!(left_half[i] = calloc(1, MAX_LINE * sizeof(array[low_value + i]))))
        {
            fprintf(stderr, "Error: Memory\n");
            exit(EXIT_FAILURE);
        }
        
        strcpy(left_half[i], array[low_value + i]);
    }

    for(i = 0; i < right_size; i++)
    {
        if(!(right_half[i] = calloc(1, MAX_LINE * \
            sizeof(array[middle_value + i + 1]))))
        {
            fprintf(stderr, "Error: Memory\n");
            exit(EXIT_FAILURE);
        }
        
        strcpy(right_half[i], array[middle_value + i + 1]);
    }



    /* Adds the 2 arrays into 1 */
    i = 0;
    x = 0;

    while(i < left_size && x < right_size)
    {
        /* Compairs the item in left to right */
        if(strcmp(left_half[i], right_half[x]) < 0)
            strcpy(array[low_value++], left_half[i++]);
        else
            strcpy(array[low_value++],right_half[x++]);
    }


    /* Adds the remaining items in the left half to the list */
    while(i < left_size)
        strcpy(array[low_value++], left_half[i++]);
    


    /* Adds the remaining items in the right half to the list */
    while(x < right_size)
        strcpy(array[low_value++], right_half[x++]);




    /* Frees left and right arrays */
    for(i = 0; i < left_size; i++)
        free(left_half[i]);
    free(left_half);

    for(i = 0; i < right_size; i++)
        free(right_half[i]);
    free(right_half);
}