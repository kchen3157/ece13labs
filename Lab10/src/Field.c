// Field.c

/**
 * author: Sai Akhil Madurakavi (smadurak)
 * Field.c
 *
 * Implements functions for initializing fields, placing boats, registering
 * attacks, and updating knowledge for the BattleBoats game.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Field.h"

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef STANDARD_ERROR
#define STANDARD_ERROR 1
#endif

void FieldPrint_UART(Field *ownField, Field *oppField)
{
    if (!ownField || !oppField)
    {
        return;
    }

    // Print column headers for both fields
    printf("   Own Field%*sOpp Field\n", FIELD_COLS * 2 - 1, "");
    printf("   ");
    for (int c = 0; c < FIELD_COLS; c++)
    {
        printf("%2d", c);
    }
    printf("%*s", 3, "");
    printf("   ");
    for (int c = 0; c < FIELD_COLS; c++)
    {
        printf("%2d", c);
    }
    printf("\n");

    // Print each row
    for (int r = 0; r < FIELD_ROWS; r++)
    {
        // Own field row
        printf("%2d ", r);
        for (int c = 0; c < FIELD_COLS; c++)
        {
            SquareStatus s = ownField->grid[r][c];
            char sym = '.';
            switch (s)
            {
            case FIELD_SQUARE_EMPTY:
                sym = '.';
                break;
            case FIELD_SQUARE_SMALL_BOAT:
                sym = '3';
                break;
            case FIELD_SQUARE_MEDIUM_BOAT:
                sym = '4';
                break;
            case FIELD_SQUARE_LARGE_BOAT:
                sym = '5';
                break;
            case FIELD_SQUARE_HUGE_BOAT:
                sym = '6';
                break;
            case FIELD_SQUARE_HIT:
                sym = 'X';
                break;
            case FIELD_SQUARE_MISS:
                sym = 'M';
                break;
            default:
                sym = '?';
                break;
            }
            printf(" %c", sym);
        }

        // Spacing between fields
        printf("%*s", 3, "");

        // Opponent field row
        printf("%2d ", r);
        for (int c = 0; c < FIELD_COLS; c++)
        {
            SquareStatus s = oppField->grid[r][c];
            char sym = '.';
            switch (s)
            {
            case FIELD_SQUARE_UNKNOWN:
                sym = '.';
                break;
            case FIELD_SQUARE_HIT:
                sym = 'X';
                break;
            case FIELD_SQUARE_MISS:
                sym = 'M';
                break;
            default:
                sym = '?';
                break;
            }
            printf(" %c", sym);
        }
        printf("\n");
    }
}

void FieldInit(Field *ownField, Field *oppField)
{
    if (ownField)
    {
        for (int r = 0; r < FIELD_ROWS; r++)
        {
            for (int c = 0; c < FIELD_COLS; c++)
            {
                ownField->grid[r][c] = FIELD_SQUARE_EMPTY;
            }
        }
        ownField->smallBoatLives = 0;
        ownField->mediumBoatLives = 0;
        ownField->largeBoatLives = 0;
        ownField->hugeBoatLives = 0;
    }
    if (oppField)
    {
        for (int r = 0; r < FIELD_ROWS; r++)
        {
            for (int c = 0; c < FIELD_COLS; c++)
            {
                oppField->grid[r][c] = FIELD_SQUARE_UNKNOWN;
            }
        }
        oppField->smallBoatLives = FIELD_BOAT_SIZE_SMALL;   // 3
        oppField->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM; // 4
        oppField->largeBoatLives = FIELD_BOAT_SIZE_LARGE;   // 5
        oppField->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;     // 6
    }
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col)
{
    if (!f || row >= FIELD_ROWS || col >= FIELD_COLS)
    {
        return FIELD_SQUARE_INVALID;
    }
    return (SquareStatus)f->grid[row][col];
}

SquareStatus FieldSetSquareStatus(
    Field *f,
    uint8_t row,
    uint8_t col,
    SquareStatus p)
{
    if (!f || row >= FIELD_ROWS || col >= FIELD_COLS)
    {
        return FIELD_SQUARE_INVALID;
    }
    SquareStatus old = (SquareStatus)f->grid[row][col];
    f->grid[row][col] = p;
    return old;
}

uint8_t FieldAddBoat(
    Field *ownField,
    uint8_t row,
    uint8_t col,
    BoatDirection dir,
    BoatType boatType)
{
    if (!ownField ||
        boatType < FIELD_BOAT_TYPE_SMALL ||
        boatType > FIELD_BOAT_TYPE_HUGE)
    {
        return STANDARD_ERROR;
    }

    uint8_t size = 0;
    SquareStatus boatStatus = FIELD_SQUARE_INVALID;
    switch (boatType)
    {
    case FIELD_BOAT_TYPE_SMALL:
        size = FIELD_BOAT_SIZE_SMALL;
        boatStatus = FIELD_SQUARE_SMALL_BOAT;
        break;
    case FIELD_BOAT_TYPE_MEDIUM:
        size = FIELD_BOAT_SIZE_MEDIUM;
        boatStatus = FIELD_SQUARE_MEDIUM_BOAT;
        break;
    case FIELD_BOAT_TYPE_LARGE:
        size = FIELD_BOAT_SIZE_LARGE;
        boatStatus = FIELD_SQUARE_LARGE_BOAT;
        break;
    case FIELD_BOAT_TYPE_HUGE:
        size = FIELD_BOAT_SIZE_HUGE;
        boatStatus = FIELD_SQUARE_HUGE_BOAT;
        break;
    default:
        return STANDARD_ERROR;
    }

    // Check bounds
    if (dir == FIELD_DIR_SOUTH)
    {
        if (row + size > FIELD_ROWS)
        {
            return STANDARD_ERROR;
        }
    }
    else
    {
        if (col + size > FIELD_COLS)
        {
            return STANDARD_ERROR;
        }
    }

    // Verify all squares are empty
    for (uint8_t i = 0; i < size; i++)
    {
        uint8_t r = (dir == FIELD_DIR_SOUTH) ? (row + i) : row;
        uint8_t c = (dir == FIELD_DIR_EAST) ? (col + i) : col;
        if (ownField->grid[r][c] != FIELD_SQUARE_EMPTY)
        {
            return STANDARD_ERROR;
        }
    }

    // Place the boat
    for (uint8_t i = 0; i < size; i++)
    {
        uint8_t r = (dir == FIELD_DIR_SOUTH) ? (row + i) : row;
        uint8_t c = (dir == FIELD_DIR_EAST) ? (col + i) : col;
        ownField->grid[r][c] = boatStatus;
    }

    // Set boat lives
    switch (boatType)
    {
    case FIELD_BOAT_TYPE_SMALL:
        ownField->smallBoatLives = size;
        break;
    case FIELD_BOAT_TYPE_MEDIUM:
        ownField->mediumBoatLives = size;
        break;
    case FIELD_BOAT_TYPE_LARGE:
        ownField->largeBoatLives = size;
        break;
    case FIELD_BOAT_TYPE_HUGE:
        ownField->hugeBoatLives = size;
        break;
    default:
        break;
    }
    return SUCCESS;
}

SquareStatus FieldRegisterEnemyAttack(Field *ownField, GuessData *opp_guess)
{
    if (!ownField || !opp_guess)
    {
        return FIELD_SQUARE_INVALID;
    }

    uint8_t row = opp_guess->row;
    uint8_t col = opp_guess->col;
    if (row >= FIELD_ROWS || col >= FIELD_COLS)
    {
        opp_guess->result = RESULT_MISS;
        return FIELD_SQUARE_INVALID;
    }

    SquareStatus old = (SquareStatus)ownField->grid[row][col];
    SquareStatus newStatus;
    ShotResult result = RESULT_MISS;

    switch (old)
    {
    case FIELD_SQUARE_SMALL_BOAT:
        ownField->smallBoatLives--;
        if (ownField->smallBoatLives == 0)
        {
            result = RESULT_SMALL_BOAT_SUNK;
        }
        else
        {
            result = RESULT_HIT;
        }
        newStatus = FIELD_SQUARE_HIT;
        ownField->grid[row][col] = newStatus;
        break;

    case FIELD_SQUARE_MEDIUM_BOAT:
        ownField->mediumBoatLives--;
        if (ownField->mediumBoatLives == 0)
        {
            result = RESULT_MEDIUM_BOAT_SUNK;
        }
        else
        {
            result = RESULT_HIT;
        }
        newStatus = FIELD_SQUARE_HIT;
        ownField->grid[row][col] = newStatus;
        break;

    case FIELD_SQUARE_LARGE_BOAT:
        ownField->largeBoatLives--;
        if (ownField->largeBoatLives == 0)
        {
            result = RESULT_LARGE_BOAT_SUNK;
        }
        else
        {
            result = RESULT_HIT;
        }
        newStatus = FIELD_SQUARE_HIT;
        ownField->grid[row][col] = newStatus;
        break;

    case FIELD_SQUARE_HUGE_BOAT:
        ownField->hugeBoatLives--;
        if (ownField->hugeBoatLives == 0)
        {
            result = RESULT_HUGE_BOAT_SUNK;
        }
        else
        {
            result = RESULT_HIT;
        }
        newStatus = FIELD_SQUARE_HIT;
        ownField->grid[row][col] = newStatus;
        break;

    case FIELD_SQUARE_HIT:
    case FIELD_SQUARE_MISS:
        // No change if already attacked here
        if (old == FIELD_SQUARE_HIT)
        {
            result = RESULT_HIT;
        }
        else
        {
            result = RESULT_MISS;
        }
        newStatus = old;
        break;

    default:
        // Miss on empty square
        result = RESULT_MISS;
        newStatus = FIELD_SQUARE_MISS;
        ownField->grid[row][col] = newStatus;
        break;
    }

    opp_guess->result = result;
    return old;
}

SquareStatus FieldUpdateKnowledge(Field *oppField, const GuessData *own_guess)
{
    if (!oppField || !own_guess)
    {
        return FIELD_SQUARE_INVALID;
    }

    uint8_t row = own_guess->row;
    uint8_t col = own_guess->col;
    if (row >= FIELD_ROWS || col >= FIELD_COLS)
    {
        return FIELD_SQUARE_INVALID;
    }

    SquareStatus old = (SquareStatus)oppField->grid[row][col];
    ShotResult res = own_guess->result;

    if (res == RESULT_MISS)
    {
        oppField->grid[row][col] = FIELD_SQUARE_MISS;
    }
    else
    {
        oppField->grid[row][col] = FIELD_SQUARE_HIT;
    }

    switch (res)
    {
    case RESULT_SMALL_BOAT_SUNK:
        oppField->smallBoatLives = 0;
        break;
    case RESULT_MEDIUM_BOAT_SUNK:
        oppField->mediumBoatLives = 0;
        break;
    case RESULT_LARGE_BOAT_SUNK:
        oppField->largeBoatLives = 0;
        break;
    case RESULT_HUGE_BOAT_SUNK:
        oppField->hugeBoatLives = 0;
        break;
    default:
        break;
    }

    return old;
}

uint8_t FieldGetBoatStates(const Field *f)
{
    if (!f)
    {
        return 0;
    }

    uint8_t state = 0;
    if (f->smallBoatLives > 0)
    {
        state |= FIELD_BOAT_STATUS_SMALL;
    }
    if (f->mediumBoatLives > 0)
    {
        state |= FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->largeBoatLives > 0)
    {
        state |= FIELD_BOAT_STATUS_LARGE;
    }
    if (f->hugeBoatLives > 0)
    {
        state |= FIELD_BOAT_STATUS_HUGE;
    }
    return state;
}

uint8_t FieldAIPlaceAllBoats(Field *ownField)
{
    if (!ownField)
    {
        return STANDARD_ERROR;
    }

    BoatType boatOrder[FIELD_NUM_BOATS] = {
        FIELD_BOAT_TYPE_SMALL,
        FIELD_BOAT_TYPE_MEDIUM,
        FIELD_BOAT_TYPE_LARGE,
        FIELD_BOAT_TYPE_HUGE};

    for (int b = 0; b < FIELD_NUM_BOATS; b++)
    {
        BoatType bt = boatOrder[b];
        uint8_t placed = 0;
        while (!placed)
        {
            BoatDirection dir = (rand() % 2 == 0)
                                    ? FIELD_DIR_SOUTH
                                    : FIELD_DIR_EAST;
            uint8_t row, col;
            uint8_t size;
            switch (bt)
            {
            case FIELD_BOAT_TYPE_SMALL:
                size = FIELD_BOAT_SIZE_SMALL;
                break;
            case FIELD_BOAT_TYPE_MEDIUM:
                size = FIELD_BOAT_SIZE_MEDIUM;
                break;
            case FIELD_BOAT_TYPE_LARGE:
                size = FIELD_BOAT_SIZE_LARGE;
                break;
            case FIELD_BOAT_TYPE_HUGE:
                size = FIELD_BOAT_SIZE_HUGE;
                break;
            default:
                size = 0;
                break;
            }

            if (dir == FIELD_DIR_SOUTH)
            {
                row = rand() % (FIELD_ROWS - size + 1);
                col = rand() % FIELD_COLS;
            }
            else
            {
                row = rand() % FIELD_ROWS;
                col = rand() % (FIELD_COLS - size + 1);
            }

            if (FieldAddBoat(ownField, row, col, dir, bt) == SUCCESS)
            {
                placed = 1;
            }
        }
    }
    return SUCCESS;
}

GuessData FieldAIDecideGuess(const Field *oppField)
{
    GuessData g = {0, 0, RESULT_MISS};
    if (!oppField)
    {
        return g;
    }

    int unknownCount = 0;
    for (int r = 0; r < FIELD_ROWS; r++)
    {
        for (int c = 0; c < FIELD_COLS; c++)
        {
            if (oppField->grid[r][c] == FIELD_SQUARE_UNKNOWN)
            {
                unknownCount++;
            }
        }
    }
    if (unknownCount == 0)
    {
        return g;
    }

    int choice = rand() % unknownCount;
    int idx = 0;
    for (int r = 0; r < FIELD_ROWS; r++)
    {
        for (int c = 0; c < FIELD_COLS; c++)
        {
            if (oppField->grid[r][c] == FIELD_SQUARE_UNKNOWN)
            {
                if (idx == choice)
                {
                    g.row = r;
                    g.col = c;
                    return g;
                }
                idx++;
            }
        }
    }
    return g;
}
