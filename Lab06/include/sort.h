/**
 * @file    sort.h
 *
 * Header file for the sort.c library that contains functions invoking insertion
 * and selection sorting algorithms.
 *
 * @author  HARE Lab
 * @author  jLab
 * @version 1.0.0
 *
 * @date    27 Oct 2024
 */
#ifndef SORT_H
#define SORT_H

// Lab libraries.
#include "LinkedList.h"


/**
 * CreateUnsortedList() uses the functions in the LinkedList library to generate 
 * an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void); //this function has been written for you

/**
 * SelectionSort() performs a selection sort on a passed to it. The list is
 * sorted alphabetically, as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member. It also
 * assumes that 'list' is a valid, non-NULL pointer to a linked list.
 */
ListItem *SelectionSort(ListItem* list);

/**
 * InsertionSort() performs an insertion sort on a passed to it. The list is
 * sorted alphabetically, as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member. It also
 * assumes that 'list' is a valid, non-NULL pointer to a linked list.
 */
ListItem *InsertionSort(ListItem* list);

#endif  /* SORT_H */
