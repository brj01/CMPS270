#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define SIZE 10
#define MAX_SHIPS 5

typedef struct {
    char name[50];
    bool grid[SIZE][SIZE];
    bool hits[SIZE][SIZE];
    int shipsSunk;
    int smokeScreens;
    int torpedoAvailable;
    int artilleryAvailable;
    int radarSweepsRemaining;
} Player;

typedef struct {
    char name[50];
    bool grid[SIZE][SIZE];
    bool hits[SIZE][SIZE];
    int shipsSunk;
    int difficulty; // 1: Easy, 2: Medium, 3: Hard
    int lastHitRow;
    int lastHitCol;
    bool lastHitSuccess;
    int smokeScreens;
    int torpedoAvailable;
    int artilleryAvailable;
    int radarSweepsRemaining;
} Bot;

const int shipSizes[] = {5, 4, 3, 3, 2};
const char *shipNames[] = {"Carrier", "Battleship", "Destroyer 1", "Destroyer 2", "Submarine"};

void initializeGrid(bool grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = false;
        }
    }
}

void displayGrid(bool grid[SIZE][SIZE], const char *label, bool showMisses) {
    printf("\n%s:\n", label);
    printf("  A B C D E F G H I J\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j])
                printf("~ ");
            else
                printf("%c ", showMisses ? 'X' : '.');
        }
        printf("\n");
    }
}

bool parseCoordinates(const char *input, int *row, int *col) {
    if (strlen(input) < 2 || !isalpha(input[0]) || !isdigit(input[1])) {
        return false;
    }
    *col = toupper(input[0]) - 'A';
    *row = atoi(input + 1) - 1;
    return (*row >= 0 && *row < SIZE && *col >= 0 && *col < SIZE);
}

bool checkShipSunk(bool grid[SIZE][SIZE], bool hits[SIZE][SIZE], int row, int col) {
    if (!grid[row][col]) return false;

<<<<<<< HEAD
    int startCol = col, endCol = col;
    while (startCol > 0 && grid[row][startCol - 1]) startCol--;
    while (endCol < SIZE - 1 && grid[row][endCol + 1]) endCol++;
=======
    if (!grid[row][col]) {
        return false; }
   
    int startCol = col, endCol = col;
    while (startCol > 0 && grid[row][startCol - 1]) {
        startCol--; }
    while (endCol < SIZE - 1 && grid[row][endCol + 1]) {
        endCol++; }

>>>>>>> 178bb4d8d6d5789c4234eeab5c44843110be7988
    bool isHorizontalSunk = true;
    for (int c = startCol; c <= endCol; c++) {
        if (!hits[row][c]) {
            isHorizontalSunk = false;
            break; }
    }

    int startRow = row, endRow = row;
<<<<<<< HEAD
    while (startRow > 0 && grid[startRow - 1][col]) startRow--;
    while (endRow < SIZE - 1 && grid[endRow + 1][col]) endRow++;
=======
    while (startRow > 0 && grid[startRow - 1][col]) {
        startRow--; }
    while (endRow < SIZE - 1 && grid[endRow + 1][col]) {
        endRow++; }

>>>>>>> 178bb4d8d6d5789c4234eeab5c44843110be7988
    bool isVerticalSunk = true;
    for (int r = startRow; r <= endRow; r++) {
        if (!hits[r][col]) {
            isVerticalSunk = false;
            break; }
    }

    return isHorizontalSunk || isVerticalSunk;
}

void artillery(Player *opponent, int centerRow, int centerCol) {
    printf("Artillery strike at %c%d:\n", 'A' + centerCol, centerRow + 1);
    for (int i = centerRow - 1; i <= centerRow + 1; i++) {
        for (int j = centerCol - 1; j <= centerCol + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                opponent->hits[i][j] = true;
                opponent->grid[i][j] = false;
            }
        }
    }
    printf("Artillery strike completed.\n");
}

void torpedo(Player *opponent, char *direction, int index) {
    printf("Torpedo strike on %s %d:\n", strcmp(direction, "row") == 0 ? "row" : "column", index + 1);
    if (strcmp(direction, "row") == 0) {
        for (int col = 0; col < SIZE; col++) {
            opponent->hits[index][col] = true;
            opponent->grid[index][col] = false;
        }
    } else if (strcmp(direction, "column") == 0) {
        for (int row = 0; row < SIZE; row++) {
            opponent->hits[row][index] = true;
            opponent->grid[row][index] = false;
        }
    }
    printf("Torpedo strike completed.\n");
}

void radarSweep(Player *opponent, int centerRow, int centerCol) {
    printf("Radar sweep at %c%d:\n", 'A' + centerCol, centerRow + 1);
    for (int i = centerRow - 1; i <= centerRow + 1; i++) {
        for (int j = centerCol - 1; j <= centerCol + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                if (opponent->grid[i][j]) {
                    printf("Ship detected at %c%d\n", 'A' + j, i + 1);
                }
            }
        }
    }
}

bool fire(Player *opponent, int row, int col, char *result) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        strcpy(result, "Out of bounds!");
        return false;
    }
    if (opponent->grid[row][col]) {
        opponent->hits[row][col] = true;
        opponent->grid[row][col] = false;
        strcpy(result, "Hit!");
        return true;
    } else {
        opponent->hits[row][col] = true;
        strcpy(result, "Miss.");
        return false;
    }
}

void botPlaceShips(Bot *bot) {
    for (int i = 0; i < MAX_SHIPS; i++) {
        bool placed = false;
        while (!placed) {
            int row = rand() % SIZE;
            int col = rand() % SIZE;
            bool isVertical = rand() % 2;
            if (canPlaceShip(bot->grid, row, col, shipSizes[i], isVertical)) {
                placeShip(bot->grid, row, col, shipSizes[i], isVertical);
                placed = true;
            }
        }
    }
}
void easyBotFire(Bot *bot, Player *opponent) {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (opponent->hits[row][col]);
    char result[20];
    fire(opponent, row, col, result);
    printf("Bot fires at %c%d: %s\n", 'A' + col, row + 1, result);
}

<<<<<<< HEAD
void mediumBotFire(Bot *bot, Player *opponent) {
    int row, col;
    if (bot->lastHitSuccess) {
        if (bot->lastHitRow > 0 && !opponent->hits[bot->lastHitRow - 1][bot->lastHitCol]) {
            row = bot->lastHitRow - 1;
            col = bot->lastHitCol;
        } else if (bot->lastHitRow < SIZE - 1 && !opponent->hits[bot->lastHitRow + 1][bot->lastHitCol]) {
            row = bot->lastHitRow + 1;
            col = bot->lastHitCol;
        } else if (bot->lastHitCol > 0 && !opponent->hits[bot->lastHitRow][bot->lastHitCol - 1]) {
            row = bot->lastHitRow;
            col = bot->lastHitCol - 1;
        } else if (bot->lastHitCol < SIZE - 1 && !opponent->hits[bot->lastHitRow][bot->lastHitCol + 1]) {
            row = bot->lastHitRow;
            col = bot->lastHitCol + 1;
        } else {
            do {
                row = rand() % SIZE;
                col = rand() % SIZE;
            } while (opponent->hits[row][col]);
        }
    } else {
        do {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (opponent->hits[row][col]);
    }
    char result[20];
    bot->lastHitSuccess = fire(opponent, row, col, result);
    bot->lastHitRow = row;
    bot->lastHitCol = col;
    printf("Bot fires at %c%d: %s\n", 'A' + col, row + 1, result);
}

void hardBotFire(Bot *bot, Player *opponent) {
    int row, col;
    if (bot->torpedoAvailable) {
        printf("Bot uses torpedo!\n");
        int leastHits = SIZE;
        int targetIndex = 0;
        char direction[10];
        for (int i = 0; i < SIZE; i++) {
            int rowHits = 0, colHits = 0;
            for (int j = 0; j < SIZE; j++) {
                if (opponent->hits[i][j]) rowHits++;
                if (opponent->hits[j][i]) colHits++;
            }
            if (rowHits < leastHits) {
                leastHits = rowHits;
                targetIndex = i;
                strcpy(direction, "row");
            }
            if (colHits < leastHits) {
                leastHits = colHits;
                targetIndex = i;
                strcpy(direction, "column");
            }
        }
        torpedo(opponent, direction, targetIndex);
        bot->torpedoAvailable = 0;
    } else if (bot->lastHitSuccess) {
        mediumBotFire(bot, opponent);
    } else {
        do {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (opponent->hits[row][col]);
        char result[20];
        fire(opponent, row, col, result);
        printf("Bot fires at %c%d: %s\n", 'A' + col, row + 1, result);
    }
}

=======
//for bot to automatically place its ships
void botPlaceShips(Bot *bot) {
    for (int i = 0; i < MAX_SHIPS; i++) {
        bool placed = false;
        while (!placed) {
            int row = rand() % SIZE;
            int col = rand() % SIZE;
            bool isVertical = rand() % 2;

            if (canPlaceShip(bot->grid, row, col, shipSizes[i], isVertical)) {
                placeShip(bot->grid, row, col, shipSizes[i], isVertical);
                placed = true; }
        }
    }
}


>>>>>>> 178bb4d8d6d5789c4234eeab5c44843110be7988
// Main function
int main() {
    srand(time(NULL));

    Player player;
    Bot bot;

    printf("Do you want to display missiles? (Y/N) ");
    char wantMissiles;
    bool showMissiles = false;
    scanf("%49s", wantMissiles);

    if (wantMissiles == 'Y' || wantMissiles == 'y') {
        showMissiles = true; }

    printf("Enter your name: ");
    scanf("%49s", player.name);

    printf("Select bot difficulty (1 = Easy, 2 = Medium, 3 = Hard): ");
    scanf("%d", &bot.difficulty);

    initializeGrid(player.grid);
    initializeGrid(player.hits);
    initializeGrid(bot.grid);
    initializeGrid(bot.hits);

    player.shipsSunk = bot.shipsSunk = 0;
    player.smokeScreens = 0;
    player.torpedoAvailable = 0;
    player.artilleryAvailable = 0;
    player.radarSweepsRemaining = 3;

    bot.smokeScreens = 0;
    bot.torpedoAvailable = 0;
    bot.artilleryAvailable = 0;
    bot.radarSweepsRemaining = 3;

    printf("Place your ships:\n");
    for (int i = 0; i < MAX_SHIPS; i++) {
        char coordinate[4];
        char orientation[10];
        while (true) {
            displayGrid(player.grid, "Your Ships", showMissiles);
            printf("Enter coordinate for your %s (size %d): ", shipNames[i], shipSizes[i]);
            scanf("%3s", coordinate);

            int row, col;
            if (!parseCoordinates(coordinate, &row, &col)) {
                printf("Invalid coordinates! Try again.\n");
                continue;
            }

            printf("Enter orientation (vertical or horizontal): ");
            scanf("%9s", orientation);
            bool isVertical = strcmp(orientation, "vertical") == 0;

            if (canPlaceShip(player.grid, row, col, shipSizes[i], isVertical)) {
                placeShip(player.grid, row, col, shipSizes[i], isVertical);
                break;
            } else {
                printf("Invalid placement! Try again.\n");
            }
        }
    }

    printf("Bot is placing ships...\n");
    botPlaceShips(&bot);

    int currentPlayerIndex = 0;

<<<<<<< HEAD
    while (player.shipsSunk < MAX_SHIPS && bot.shipsSunk < MAX_SHIPS) {
        if (currentPlayerIndex == 0) { 
            displayGrid(bot.hits, "Opponent's Grid", true);
            char command[20];
            printf("Your turn! Choose action (Fire, Radar, Smoke, Torpedo, Artillery): ");
            scanf("%s", command);
            bot.artilleryAvailable=0;
            bot.torpedoAvailable=0;
            
            if (strcmp(command, "Fire") == 0) {
                char coordinates[4];
                printf("Enter coordinates to fire: ");
                scanf("%3s", coordinates);

                int row, col;
                char result[20];
                if (parseCoordinates(coordinates, &row, &col)) {
                    if (fire(&bot, row, col, result)) {
                        if (checkShipSunk(bot.grid, bot.hits, row, col)) {
                            bot.shipsSunk++;
                            printf("You sunk the opponent's ship!\n");
                            player.smokeScreens++;
                            player.artilleryAvailable=1;
                            player.radarSweepsRemaining=1;
                        }
                        printf("%s\n", result);
=======
            int row, col;
            char result[20];
            if (parseCoordinates(coordinates, &row, &col)) {
                if (fire(&bot, row, col, result)) {
                    if (checkShipSunk(bot.grid, bot.hits, row, col)) {
                        bot.shipsSunk++;
                        printf("You sunk the opponent's ship!\n");
>>>>>>> 178bb4d8d6d5789c4234eeab5c44843110be7988
                    }
                } else {
                    printf("Invalid coordinates! Try again.\n");
                }
            } else if (strcmp(command, "Radar") == 0) {
                if (player.radarSweepsRemaining > 0) {
                    char coordinates[4];
                    printf("Enter coordinates for radar sweep: ");
                    scanf("%3s", coordinates);

                    int row, col;
                    if (parseCoordinates(coordinates, &row, &col)) {
                        radarSweep(&bot, row, col);
                        player.radarSweepsRemaining--;
                    } else {
                        printf("Invalid coordinates! Try again.\n");
                    }
                } else {
                    printf("No radar sweeps remaining!\n");
                }
            } else if (strcmp(command, "Smoke") == 0) {
                if (player.smokeScreens > 0) {
                    char coordinates[4];
                    printf("Enter coordinates for smoke screen: ");
                    scanf("%3s", coordinates);

                    int row, col;
                    if (parseCoordinates(coordinates, &row, &col)) {
                        printf("Smoke deployed at %c%d.\n", 'A' + col, row + 1);
                        player.smokeScreens--;
                    } else {
                        printf("Invalid coordinates! Try again.\n");
                    }
                } else {
                    printf("No smoke screens remaining!\n");
                }
            } else if (strcmp(command, "Torpedo") == 0) {
                if (player.torpedoAvailable > 0) {
                    char direction[10];
                    int index;
                    printf("Enter direction (row/column): ");
                    scanf("%s", direction);
                    printf("Enter index (1-10): ");
                    scanf("%d", &index);
                    index--;

                    if (index >= 0 && index < SIZE) {
                        torpedo(&bot, direction, index);
                        player.torpedoAvailable--;
                    } else {
                        printf("Invalid index! Try again.\n");
                    }
                } else {
                    printf("No torpedoes remaining!\n");
                }
            } else if (strcmp(command, "Artillery") == 0) {
                if (player.artilleryAvailable > 0) {
                    char coordinates[4];
                    printf("Enter coordinates for artillery strike: ");
                    scanf("%3s", coordinates);

                    int row, col;
                    if (parseCoordinates(coordinates, &row, &col)) {
                        artillery(&bot, row, col);
                        player.artilleryAvailable--;
                    } else {
                        printf("Invalid coordinates! Try again.\n");
                    }
                } else {
                    printf("No artillery strikes remaining!\n");
                }
            } else {
                printf("Invalid action! Try again.\n");
            }
<<<<<<< HEAD
        } else {
            switch (bot.difficulty) {
                case 1:
                    easyBotFire(&bot, &player);
                    break;
                case 2:
                    mediumBotFire(&bot, &player);
                    break;
                case 3:
                    hardBotFire(&bot, &player);
                    break;
            }
             player.artilleryAvailable=0;
                player.torpedoAvailable=0;
            if (checkShipSunk(player.grid, player.hits, bot.lastHitRow, bot.lastHitCol)) {
                player.shipsSunk++;
               bot.artilleryAvailable=1;
               bot.torpedoAvailable=1;
               bot.smokeScreens++;

                printf("The bot sunk one of your ships!\n");
=======
        } else { // Bot's turn
            botFire(&bot, &player);
            if (bot.lastHitSuccess) {
                if (checkShipSunk(player.grid, player.hits, bot.lastHitRow, bot.lastHitCol)) {
                    player.shipsSunk++;
                    printf("The bot sunk one of your ships!\n");
                }
>>>>>>> 178bb4d8d6d5789c4234eeab5c44843110be7988
            }
        }

        currentPlayerIndex = 1 - currentPlayerIndex;
    }

    printf("%s wins!\n", player.shipsSunk == MAX_SHIPS ? bot.name : player.name);

    return 0;
}
