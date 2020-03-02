//
//  main.c
//  battleships
//
//  Created by Radek on 3/1/20.
//  Copyright © 2020 Radek. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>
#define EMPTY '.'
#define MISSED 'M'
#define HIT 'H'

void initBoard(char gameTable[10][10]);
void printBoard(char gameTable[10][10]);

struct shipStruct {
  int health;
  int size;
  char name[20];
};

struct gameStats {
	int missilesFired;
	int shipHits;
	int shipMisses;
};

void initializeAllShips(struct shipStruct allShips[5], char grid [10][10]);
int checkForWrap(int xx, int yy, int direction, int size);
int checkNoCollision(char grid[10][10], int xx, int yy, int direction, int size);
void placeShip(struct shipStruct aShip, char grid[10][10], int shipId);
void fire(int xx, int yy, char gameTable[10][10], struct shipStruct allShips[5],struct gameStats);
void printTheGame(char gameTable[10][10], struct shipStruct allShips[5],struct gameStats game);


int main(int argc, const char * argv[]) {
  srand(time(0));
  printf("\n");
  char gameTable[10][10] = {0};
	
  struct shipStruct allShips[5];

	struct gameStats game;
	game.shipHits=0;
	game.shipMisses=0;
	game.missilesFired=11;
	
	

  initBoard(gameTable);
  //printBoard(gameTable);
  initializeAllShips(allShips, gameTable);
  printBoard(gameTable);

  //  getUser target xx,yy
  printf("[MAIN] Calling fire [5,5]\n");
  fire(5, 5,  gameTable, allShips,game);
  printf("\n");
	printf("[MAIN] Ship Hits %d \n",game.shipHits);
	printf("[Main] Ship Miss %d \n",game.shipMisses);
	printf("[MAIN] Ship Miss %d \n",game.missilesFired);

  printBoard(gameTable);

	printTheGame(gameTable, allShips,game);

  return 0;
}




void fire(int xx, int yy, char gameTable[10][10], struct shipStruct allShips[5],struct gameStats game) {
	printf("_______________\n");
	printf("%d %d %d\n", game.missilesFired, game.shipMisses, game.shipHits);

  printf("[FIRE] Taking a shot\n");
  int i = gameTable[xx][yy] - '0';
	game.missilesFired++;
	printf("[FIRE] Ship Miss %d \n",game.missilesFired);

  if (i >= 0 && i <= 4) {
    printf("[FIRE] We whacked ship index %d\n", i);
    printf("[FIRE] Health was %d\n", allShips[i].health);
    allShips[i].health--;
    printf("[FIRE] Health is %d\n", allShips[i].health);
    gameTable[xx][yy] = HIT;
		game.shipHits++;
		printf("[FIRE] Ship Hits %d \n",game.shipHits);
    return;
  }

  gameTable[xx][yy] = MISSED;
	game.shipMisses++;
		printf("[FIRE] Ship Miss %d \n",game.shipMisses);

}



void placeShip(struct shipStruct aShip, char grid[10][10], int shipId) {
  //
  int placed = 0;
  //printf("[PLACE SHIP] We're inside\n");
  //printBoard(grid);
  do {
    //printf("[PLACE SHIP] INSIDE DO with ship size = %d\n",aShip.size);
    int xx = rand() % 10;
    int yy = rand() % 10;
    int direction = rand() % 4;
    printf("[PLACE SHIP] Testing x=%d y=%d, dir=%d\n", xx, yy, direction);
    if ( checkForWrap(xx, yy, direction, aShip.size) == 1) {
      printf("[PLACE SHIP] Check for wrap was TRUE\n");
      if ( checkNoCollision(grid, xx, yy, direction, aShip.size) == 1 ) {
        //place ship
        for (int i = 0; i < aShip.size; i++) {
          printf("[PLACE SHIP] About to place %d [i=%d] at x=%d, y=%d\n", aShip.size + '0', i, xx, yy);
          grid[xx][yy] = shipId + '0';
          // grid[xx][yy] = 0xFF;
          if (direction == 0) xx++; //right
          if (direction == 2) xx--; //left
          if (direction == 3) yy--; //up
          if (direction == 1) yy++; //down
          //printBoard(grid);
        }
        placed = 1;
        printf("[PLACE SHIP] PLACED ship\n");
      }
    }


  } while (!placed);
}




int checkForWrap(int xx, int yy, int direction, int size) {
  if (direction == 0 && xx + size >= 9) return 0;
  if (direction == 2 && xx - size <= 0) return 0;
  if (direction == 1 && yy + size >= 9) return 0;
  if (direction == 3 && yy - size <= 0) return 0;
  return 1;
}





int checkNoCollision(char grid[10][10], int xx, int yy, int direction, int size) {

  while (size > 0) {
    if (grid[xx][yy] != EMPTY) {
      printf("[CHECK NO COLL] Collision!!!!!!\n");
      return 0;
    }
    if (direction == 0) xx++; //right
    if (direction == 2) xx--; //left
    if (direction == 3) yy--; //up
    if (direction == 1) yy++; //down
    size--;
  }
  printf("[CHECK NO COLL] No collision\n");
  return 1;

}




void initializeAllShips(struct shipStruct allShips[5], char grid[10][10]) {
  printf("\n");
  allShips[0].size = 5;
  strcpy(allShips[0].name, "Air Force Academy");
  allShips[0].health = 5;

  allShips[1].size = 4;
  allShips[1].health = 4;
  strcpy(allShips[1].name, "Valencia Destroyer");

  allShips[2].size = 3;
  allShips[2].health = 3;
  strcpy(allShips[2].name, "Eskimo University");

  allShips[3].size = 3;
  allShips[3].health = 3;
  strcpy(allShips[3].name, "Seminole State  ");

  allShips[4].size = 2;
  allShips[4].health = 2;
  strcpy(allShips[4].name, "Deland High School");

  for (int i = 0; i <= 4; i++) {
    printf("INITALLSHIPS: calling placeShip with i=%d\n", i);
    placeShip( allShips[i], grid, i);
  }
}





void initBoard(char gameTable[10][10]) {
  for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 10; x++) {
      //gameTable[x][y]=x+10*y;
      gameTable[x][y] = EMPTY;
    }
  }
}

void printBoard(char gameTable[10][10]) {
  for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 10; x++) {
      //  printf("%i ",gameTable[x][y]);
      printf("%c ", gameTable[x][y]);
    }
    printf("\n");
  }

}

void printTheGame(char gameTable[10][10], struct shipStruct allShips[5],struct gameStats game){
	printf("       ");
	for (int i = 'A'; i<='J'; i++){
		printf("%c ",i);
	}
	printf("\n");
	for (int y=1; y<=10; y++){
		printf("[");
		if(y<10) printf("0");
		printf("%d]   ",y);
		for(int x=0; x<10;x++){
			char c = gameTable[x][y-1];
			if (c>='0' && c<='4') c=EMPTY;
			printf("%c ",c);
		}
		printf("\n");

	}
	for(int i =0; i <5; i++){
		printf("%s\t", allShips[i].name);
		if(allShips[i].health > 0){
			printf("floating");
		}
		else{
			printf("sunk");
		}
		if(i == 0){
			printf("\tMisseles Fired\t%d",game.missilesFired);
		}
		if(i==2){
			printf("\tShip Hits\t%d",game.shipHits);
		}

		if(i==4){
			printf("\tShip Misses\t%d",game.shipMisses);
		}
		printf("\n");


	}

}