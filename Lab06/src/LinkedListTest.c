
#include <stdio.h>

#include "BOARD.h"
#include "LinkedList.h"

int main(void)
{
    BOARD_Init();

    printf("Starting Testbench.\n");

    printf("****************** Testing LinkedListNew ******************\n\n");

    ListItem* uut_1 = LinkedListNew("First UUT!");
    printf("Ran LinkedListNew...\n");

    printf("Test LinkedListGetFirst: %s\n\tExpected: First UUT!\n", LinkedListGetFirst(uut_1)->data); // Test Get First
    printf("Test LinkedListGetLast: %s\n\tExpected: First UUT!\n", LinkedListGetLast(uut_1)->data); // Test Get Last
    printf("Test LinkedListSize: %d\n\tExpected: 1\n", LinkedListSize(uut_1)); // Test Size
    printf("Test LinkedListPrint: ");
    LinkedListPrint(uut_1);
    printf("\tExpected: [First UUT!]\n");
    
    uut_1 = LinkedListNew("UUT 1");
    printf("Ran LinkedListNew Again...\n");

    printf("Test LinkedListGetFirst: %s\n\tExpected: UUT 1\n", LinkedListGetFirst(uut_1)->data); // Test Get First
    printf("Test LinkedListGetLast: %s\n\tExpected: UUT 1\n", LinkedListGetLast(uut_1)->data); // Test Get Last
    printf("Test LinkedListSize: %d\n\tExpected: 1\n", LinkedListSize(uut_1)); // Test Size
    printf("Test LinkedListPrint: ");
    LinkedListPrint(uut_1);
    printf("\tExpected: [UUT 1]\n");

    printf("\n\n");

    printf("****************** Testing LinkedListCreateAfter/Before ******************\n\n");
    printf("Running instances of LinkedListCreateAfter/Before...\n");
    printf("Added UUT 2 after UUT 1: ");
    ListItem* uut_2 = LinkedListCreateAfter(uut_1, "UUT 2"); // Test Create After (Tail)
    LinkedListPrint(uut_2);
    printf("\tExpected: [UUT 1, UUT 2]\n");
    printf("Added UUT 0 before UUT 1: ");
    ListItem* uut_0 = LinkedListCreateBefore(uut_1, "UUT 0"); // Test Create Before (Head)
    LinkedListPrint(uut_0);
    printf("\tExpected: [UUT 0, UUT 1, UUT 2]\n");
    printf("Added UUT 0.5 after UUT 0: ");
    ListItem* uut_0_5 = LinkedListCreateAfter(uut_0, "UUT 0.5"); // Test Create After (Inbetween)
    LinkedListPrint(uut_0_5);
    printf("\tExpected: [UUT 0, UUT 0.5, UUT 1, UUT 2]\n");
    printf("Added UUT 1.5 before UUT 2: ");
    ListItem* uut_1_5 = LinkedListCreateBefore(uut_2, "UUT 1.5"); // Test Create Before (Inbetween)
    LinkedListPrint(uut_1_5);
    printf("\tExpected: [UUT 0, UUT 0.5, UUT 1, UUT 1.5, UUT 2]\n");


    printf("Test LinkedListGetFirst: %s\n\tExpected: UUT 0\n", LinkedListGetFirst(uut_1)->data); // Test Get First
    printf("Test LinkedListGetLast: %s\n\tExpected: UUT 2\n", LinkedListGetLast(uut_1)->data); // Test Get Last
    printf("Test LinkedListSize: %d\n\tExpected: 5\n", LinkedListSize(uut_1)); // Test Size

    printf("\n\n");
    
    printf("****************** Testing LinkedListSwapData ******************\n\n");
    printf("Running instances of LinkedListSwapData...\n");
    LinkedListSwapData(uut_0_5, uut_1_5); // Test SwapData
    printf("Swapped UUT 0.5 and UUT 1.5: ");
    LinkedListPrint(uut_1);
    printf("\tExpected [UUT 0, UUT 1.5, UUT 1, UUT 0.5, UUT 2]\n");
    LinkedListSwapData(uut_1_5, uut_0_5); // Test SwapData
    printf("Swapped UUT 0.5 and UUT 1.5: ");
    LinkedListPrint(uut_1);
    printf("\tExpected [UUT 0, UUT 0.5, UUT 1, UUT 1.5, UUT 2]\n");

    LinkedListSwapData(uut_1, uut_0); // Test SwapData
    printf("Swapped UUT 0 and UUT 1: ");
    LinkedListPrint(uut_1);
    printf("\tExpected [UUT 1, UUT 0.5, UUT 0, UUT 1.5, UUT 2]\n");
    LinkedListSwapData(uut_0, uut_1); // Test SwapData
    printf("Swapped UUT 0 and UUT 1: ");
    LinkedListPrint(uut_1);
    printf("\tExpected [UUT 0, UUT 0.5, UUT 1, UUT 1.5, UUT 2]\n");

    printf("\n\n");

    printf("****************** Testing LinkedListRemove ******************\n\n");
    printf("Running instances of LinkedListRemove...\n");
    LinkedListRemove(uut_0_5);
    printf("Removed UUT 0.5: ");
    LinkedListPrint(uut_1);
    printf("\tExpected: [UUT 0, UUT 1, UUT 1.5, UUT 2]\n");
    LinkedListRemove(uut_0);
    printf("Removed UUT 0: ");
    LinkedListPrint(uut_1);
    printf("\tExpected: [UUT 1, UUT 1.5, UUT 2]\n");
    LinkedListRemove(uut_2);
    printf("Removed UUT 2: ");
    LinkedListPrint(uut_1);
    printf("\tExpected: [UUT 1, UUT 1.5]\n");

    printf("Removing UUT 1 and UUT 2 and returning contents: %s, %s\n\tExpected: UUT 1, UUT 1.5\n",
        LinkedListRemove(uut_1), LinkedListRemove(uut_1_5));

    printf("\n\n");


    // Test NULL Params
    printf("****************** Testing NULL Params ******************\n\n");

    printf("LinkedListNew(NULL): ");
    uut_1 = LinkedListNew(NULL);
    LinkedListPrint(uut_1);
    printf("\tExpected: [(null)]\n");

    printf("LinkedListCreateAfter(NULL, NULL): ");
    uut_1 = LinkedListCreateAfter(NULL, NULL);
    LinkedListPrint(uut_1);
    printf("\tExpected: [(null)]\n");

    printf("LinkedListCreateBefore(NULL, NULL): ");
    uut_1 = LinkedListCreateBefore(NULL, NULL);
    LinkedListPrint(uut_1);
    printf("\tExpected: [(null)]\n");

    printf("\nRunning uut_1 = LinkedListNew(\"UUT 1\")...\n\n");
    uut_1 = LinkedListNew("UUT 1");
    
    printf("LinkedListCreateBefore(uut_1, NULL): ");
    uut_0 = LinkedListCreateBefore(uut_1, NULL);
    LinkedListPrint(uut_1);
    printf("\tExpected: [(null), UUT 1]\n");

    printf("LinkedListCreateAfter(uut_1, NULL): ");
    uut_2 = LinkedListCreateAfter(uut_1, NULL);
    LinkedListPrint(uut_1);
    printf("\tExpected: [(null), UUT 1, (null)]\n");

    printf("LinkedListRemove(NULL): %s\n\tExpected: Is null\n", 
        LinkedListRemove(NULL) == NULL ? "Is null" : "Not null");

    printf("LinkedListSize(NULL): %d\n\tExpected: 0\n", LinkedListSize(NULL));

    printf("LinkedListGetFirst(NULL): %s\n\tExpected: Is null\n", 
        LinkedListGetFirst(NULL) == NULL ? "Is null" : "Not null");

    printf("LinkedListGetLast(NULL): %s\n\tExpected: Is null\n", 
        LinkedListGetLast(NULL) == NULL ? "Is null" : "Not null");

    printf("LinkedListSwapData(NULL, NULL): %d\n\tExpected: %d\n", 
        LinkedListSwapData(NULL, NULL), STANDARD_ERROR);

    printf("LinkedListPrint(NULL): %d\n\tExpected: %d\n", 
        LinkedListPrint(NULL), STANDARD_ERROR);

    printf("\n\n");

    printf("Testbench done. Verify results.\n");

    while (1);

    return 0;
}
