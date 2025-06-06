#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Field.h"
#include "BOARD.h"

#define FAIL(...)                        \
    printf("failed: %s\n", __VA_ARGS__); \
    return -1;


int main(void)
{
    BOARD_Init();

    Field ownfield_uut, oppfield_uut;
    GuessData guess_uut;
    
    memset(&guess_uut, 0, sizeof(GuessData));
    

    //******** FieldInit/FieldPrint_UART ********
    printf("FieldInit/FieldPrint_UART Test\n");

    FieldInit(&ownfield_uut, &oppfield_uut);
    printf("Verify following field is empty:\n");
    FieldPrint_UART(&ownfield_uut, &oppfield_uut);
    printf("\n\n");

    //******** FieldAddBoat ********
    printf("FieldAddBoat Test\n");
    
    // Initial Boat placement
    if (FieldAddBoat(&ownfield_uut, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE)) {FAIL("bp1")}
    if (FieldAddBoat(&ownfield_uut, 2, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_MEDIUM)) {FAIL("bp3")}
    if (FieldAddBoat(&ownfield_uut, 3, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL)) {FAIL("bp4")}

    printf("Verify three boats, then four boats placed:\n");
    FieldPrint_UART(&ownfield_uut, &oppfield_uut);

    // Try placing boats on other boats
    if (!FieldAddBoat(&ownfield_uut, 3, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp5")} // Rowwise full
    if (!FieldAddBoat(&ownfield_uut, 0, 3, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp6")} // Rowwise full
    if (!FieldAddBoat(&ownfield_uut, 0, 5, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp7")} // Rowwise part
    if (!FieldAddBoat(&ownfield_uut, 0, 0, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp8")} // Colwise full
    if (!FieldAddBoat(&ownfield_uut, 3, 2, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp9")} // Colwise part

    // Try placing boats off field
    if (!FieldAddBoat(&ownfield_uut, 4, 7, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp10")} // Rowwise part
    if (!FieldAddBoat(&ownfield_uut, 0, 8, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp11")} // Rowwise part
    if (!FieldAddBoat(&ownfield_uut, 3, 3, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp12")} // Colwise part
    if (!FieldAddBoat(&ownfield_uut, 5, 7, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp13")} // Colwise part

    // Try using illegal coords out of bound of field
    if (!FieldAddBoat(&ownfield_uut, 6, 10, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp14")}
    if (!FieldAddBoat(&ownfield_uut, -1, -8, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp15")}

    // Continue Boat placement
    if (FieldAddBoat(&ownfield_uut, 1, 8, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_LARGE)) {FAIL("bp2")}


    FieldPrint_UART(&ownfield_uut, &oppfield_uut);

    printf("\n\n");

    //******** FieldRegisterEnemyAttack ********
    printf("FieldRegisterEnemyAttack Test\n");
    printf("There should be no difference between the two field prints, 7 hit/misses in total\n");

    // Do valid attacks

    // Do an enemy hit
    guess_uut.row = 0;
    guess_uut.col = 0;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_HUGE_BOAT) {FAIL("bp16p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_HIT) {FAIL("bp16")}
    if (guess_uut.result != RESULT_HIT) {FAIL("bp16a")}

    // Do an enemy miss
    guess_uut.row = 1;
    guess_uut.col = 7;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_EMPTY) {FAIL("bp17p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_MISS) {FAIL("bp17")}
    if (guess_uut.result != RESULT_MISS) {FAIL("bp17a")}

    // Do an enemy hit
    guess_uut.row = 3;
    guess_uut.col = 0;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_SMALL_BOAT) {FAIL("bp18p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_HIT) {FAIL("bp18")}
    if (guess_uut.result != RESULT_HIT) {FAIL("bp18a")}

    // Do an enemy hit
    guess_uut.row = 3;
    guess_uut.col = 1;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_SMALL_BOAT) {FAIL("bp19p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_HIT) {FAIL("bp19")}
    if (guess_uut.result != RESULT_HIT) {FAIL("bp19a")}

    // Do an enemy hit
    guess_uut.row = 3;
    guess_uut.col = 2;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_SMALL_BOAT) {FAIL("bp20p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_HIT) {FAIL("bp20")}
    if (guess_uut.result != RESULT_SMALL_BOAT_SUNK) {FAIL("bp20a")}

    // Do an enemy miss
    guess_uut.row = 5;
    guess_uut.col = 2;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_EMPTY) {FAIL("bp21p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_MISS) {FAIL("bp21")}
    if (guess_uut.result != RESULT_MISS) {FAIL("bp21a")}

    // Do an enemy miss
    guess_uut.row = 4;
    guess_uut.col = 6;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_EMPTY) {FAIL("bp22p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_MISS) {FAIL("bp22")}
    if (guess_uut.result != RESULT_MISS) {FAIL("bp22a")}


    FieldPrint_UART(&ownfield_uut, &oppfield_uut);

    // Now do invalid attacks

    // Out of bounds
    guess_uut.row = -1;
    guess_uut.col = -8;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_INVALID) {FAIL("bp23p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_INVALID) {FAIL("bp23")}
    if (guess_uut.result != RESULT_MISS) {FAIL("bp23a")}

    // Enemy attack on previously attacked missed square 
    guess_uut.row = 4;
    guess_uut.col = 6;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_MISS) {FAIL("bp24p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_MISS) {FAIL("bp24")}
    if (guess_uut.result != RESULT_MISS) {FAIL("bp24a")}


    // Enemy attack on previously attacked hit square 
    guess_uut.row = 3;
    guess_uut.col = 2;
    if (FieldRegisterEnemyAttack(&ownfield_uut, &guess_uut) != FIELD_SQUARE_HIT) {FAIL("bp25p")}
    if (FieldGetSquareStatus(&ownfield_uut, guess_uut.row, guess_uut.col) != FIELD_SQUARE_HIT) {FAIL("bp25")}
    if (guess_uut.result != RESULT_HIT) {FAIL("bp25a")}

    FieldPrint_UART(&ownfield_uut, &oppfield_uut);

    printf("\n\n");


    //******** FieldUpdateKnowledge ********
    printf("FieldUpdateKnowledge Test\n");

    guess_uut.row = 0;
    guess_uut.col = 0;
    guess_uut.result = RESULT_HIT;
    if (FieldUpdateKnowledge(&oppfield_uut, &guess_uut) != FIELD_SQUARE_UNKNOWN) {FAIL("bp26p")}
    if (oppfield_uut.grid[guess_uut.row][guess_uut.col] != FIELD_SQUARE_HIT) {FAIL("bp26")}

    guess_uut.row = 1;
    guess_uut.col = 0;
    guess_uut.result = RESULT_MISS;
    if (FieldUpdateKnowledge(&oppfield_uut, &guess_uut) != FIELD_SQUARE_UNKNOWN) {FAIL("bp27p")}
    if (oppfield_uut.grid[guess_uut.row][guess_uut.col] != FIELD_SQUARE_MISS) {FAIL("bp27")}

    guess_uut.row = 2;
    guess_uut.col = 0;
    guess_uut.result = RESULT_HUGE_BOAT_SUNK;
    if (FieldUpdateKnowledge(&oppfield_uut, &guess_uut) != FIELD_SQUARE_UNKNOWN) {FAIL("bp28p")}
    if (oppfield_uut.grid[guess_uut.row][guess_uut.col] != FIELD_SQUARE_HIT) {FAIL("bp28a")}
    if (oppfield_uut.hugeBoatLives != 0) {FAIL("bp28b")}


    guess_uut.row = 3;
    guess_uut.col = 0;
    guess_uut.result = RESULT_LARGE_BOAT_SUNK;
    if (FieldUpdateKnowledge(&oppfield_uut, &guess_uut) != FIELD_SQUARE_UNKNOWN) {FAIL("bp29p")}
    if (oppfield_uut.grid[guess_uut.row][guess_uut.col] != FIELD_SQUARE_HIT) {FAIL("bp29a")}
    if (oppfield_uut.largeBoatLives != 0) {FAIL("bp29b")}

    guess_uut.row = 4;
    guess_uut.col = 0;
    guess_uut.result = RESULT_MEDIUM_BOAT_SUNK;
    if (FieldUpdateKnowledge(&oppfield_uut, &guess_uut) != FIELD_SQUARE_UNKNOWN) {FAIL("bp30p")}
    if (oppfield_uut.grid[guess_uut.row][guess_uut.col] != FIELD_SQUARE_HIT) {FAIL("bp30a")}
    if (oppfield_uut.mediumBoatLives != 0) {FAIL("bp30b")}

    guess_uut.row = 5;
    guess_uut.col = 0;
    guess_uut.result = RESULT_SMALL_BOAT_SUNK;
    if (FieldUpdateKnowledge(&oppfield_uut, &guess_uut) != FIELD_SQUARE_UNKNOWN) {FAIL("bp31p")}
    if (oppfield_uut.grid[guess_uut.row][guess_uut.col] != FIELD_SQUARE_HIT) {FAIL("bp31a")}
    if (oppfield_uut.smallBoatLives != 0) {FAIL("bp31b")}

    FieldPrint_UART(&ownfield_uut, &oppfield_uut);

    //******** FieldGetSquareStatus ********
    //******** FieldSetSquareStatus ********
    
    
    //******** FieldGetBoatStates ********
    //******** FieldAIPlaceAllBoats ********

    FieldInit(&ownfield_uut, &oppfield_uut);
    FieldAIPlaceAllBoats(&ownfield_uut);
    FieldPrint_UART(&ownfield_uut, &oppfield_uut);

    //******** FieldAIDecideGuess ********

    guess_uut = FieldAIDecideGuess(&oppfield_uut);
    guess_uut.result = RESULT_HIT;
    FieldUpdateKnowledge(&oppfield_uut, &guess_uut);

    guess_uut = FieldAIDecideGuess(&oppfield_uut);
    guess_uut.result = RESULT_HIT;
    FieldUpdateKnowledge(&oppfield_uut, &guess_uut);

    guess_uut = FieldAIDecideGuess(&oppfield_uut);
    guess_uut.result = RESULT_MISS;
    FieldUpdateKnowledge(&oppfield_uut, &guess_uut);

    guess_uut = FieldAIDecideGuess(&oppfield_uut);
    guess_uut.result = RESULT_MISS;
    FieldUpdateKnowledge(&oppfield_uut, &guess_uut);

    guess_uut = FieldAIDecideGuess(&oppfield_uut);
    guess_uut.result = RESULT_HUGE_BOAT_SUNK;
    FieldUpdateKnowledge(&oppfield_uut, &guess_uut);

    guess_uut = FieldAIDecideGuess(&oppfield_uut);
    guess_uut.result = RESULT_LARGE_BOAT_SUNK;
    FieldUpdateKnowledge(&oppfield_uut, &guess_uut);

    guess_uut = FieldAIDecideGuess(&oppfield_uut);
    guess_uut.result = RESULT_MEDIUM_BOAT_SUNK;
    FieldUpdateKnowledge(&oppfield_uut, &guess_uut);
    
    guess_uut = FieldAIDecideGuess(&oppfield_uut);
    guess_uut.result = RESULT_SMALL_BOAT_SUNK;
    FieldUpdateKnowledge(&oppfield_uut, &guess_uut);

    FieldPrint_UART(&ownfield_uut, &oppfield_uut);

    return 0;
}