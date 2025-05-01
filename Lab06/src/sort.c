/**
 * @file    sort_template.c
 *
 * @author
 *
 * @date
 *
 * @note    Heap size of >= 1024 required!
 */
// Standard libraries.
#include <stdio.h>
#include <string.h>

// User libraries.
#include "sort.h"


/**
 * SelectionSort() performs a selection sort on a passed to it. The list is
 * sorted alphabetically, as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member. It also
 * assumes that 'list' is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *SelectionSort(ListItem* list)
{
   // YOUR CODE GOES HERE!
}

/**
 * InsertionSort() performs an insertion sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *InsertionSort(ListItem* list)
{
   // YOUR CODE GOES HERE!
}

/**
 * CreateUnsortedList() uses the functions in the LinkedList library to
 * generate an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void)
{
    char* wordList[] = {
        "decide", "toothpaste", "lowly", "robin", "reign", "crowd", "pies",
        "reduce", "tendency", "surround", "finger", "rake", "alleged", "hug",
        "nest", "punishment", "eggnog", "side", "beef", "exuberant", "sort",
        "scream", "zip", "hair", "ragged", "damage", "thought", "jump",
        "frequent", "substance", "head", "step", "faithful", "sidewalk", "pig",
        "raspy", "juggle", "shut", "maddening", "rock", "telephone",
        "selective", NULL
    };

    int i = 0;
    ListItem* head = LinkedListNew(wordList[i]);
    ListItem* tail = head;
    for (i = 1; wordList[i] != NULL; i++) {
        tail = LinkedListCreateAfter(tail, wordList[i]);
        if (tail == NULL) {
          // If a NULL pointer is found, return NULL for the calling script to 
          // check.
          return NULL;
        }
    }
    return head;
}
