
#include <stdio.h>

#include "BOARD.h"
#include "sort.h"
#include "LinkedList.h"

int main(void)
{
    ListItem* list_item_uut_1 = LinkedListNew("LinkedList UUT 1");

    printf("Size: %d\n", LinkedListSize(list_item_uut_1));

    LinkedListPrint(list_item_uut_1);
    ListItem* list_item_uut_2 = LinkedListCreateAfter(list_item_uut_1, "LinkedList UUT 2"); // Test Create After Tail
    LinkedListPrint(list_item_uut_2);
    ListItem* list_item_uut_0 = LinkedListCreateBefore(list_item_uut_1, "LinkedList UUT 0"); // Test Create Before Head
    LinkedListPrint(list_item_uut_0);
    ListItem* list_item_uut_0_5 = LinkedListCreateAfter(list_item_uut_0, "LinkedList UUT 0.5"); // Test Create After Inbetween
    LinkedListPrint(list_item_uut_0_5);
    ListItem* list_item_uut_1_5 = LinkedListCreateBefore(list_item_uut_2, "LinkedList UUT 1.5"); // Test Create Before Inbetween
    LinkedListPrint(list_item_uut_1_5);
    
    printf("First: %s\n", LinkedListGetFirst(list_item_uut_1)->data);
    printf("Last: %s\n", LinkedListGetLast(list_item_uut_1)->data);
    printf("Size: %d\n", LinkedListSize(list_item_uut_1));

    LinkedListSwapData(list_item_uut_0_5, list_item_uut_1_5);
    LinkedListPrint(list_item_uut_1);
    LinkedListSwapData(list_item_uut_0_5, list_item_uut_1_5);
    LinkedListPrint(list_item_uut_1);

    LinkedListRemove(list_item_uut_0_5);
    LinkedListPrint(list_item_uut_1);
    LinkedListRemove(list_item_uut_0);
    LinkedListPrint(list_item_uut_1);
    LinkedListRemove(list_item_uut_2);
    LinkedListPrint(list_item_uut_1);

    printf("Size: %d\n", LinkedListSize(list_item_uut_1));

    printf("%s\n%s\n", LinkedListRemove(list_item_uut_1), LinkedListRemove(list_item_uut_1_5));

    ListItem *list_uut = CreateUnsortedList();
    LinkedListPrint(list_uut);
    SelectionSort(list_uut);
    LinkedListPrint(list_uut);

    list_uut = CreateUnsortedList();
    LinkedListPrint(list_uut);
    InsertionSort(list_uut);
    LinkedListPrint(list_uut);

    return 0;
}
