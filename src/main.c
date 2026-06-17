#include <stdio.h>

void renderBoard(char boardState[3][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("[%c]",boardState[i][j]);
			if(j==2){
				printf("\n");
			}
		}
	}
}

int main(){
	char message[]="Tic Tac Toe\n\n";
	printf(message);

	printf("Choose your side: x or o?\n");

	char side;
	scanf("%c", &side);

	while(side!='x'&&side!='o'){
		printf("You have to choose x or o. You typed %c\n", side);
		printf("Choose your side:\n");
		scanf("%c", &side);
	}

	printf("Good. You play as %c\n",side);

	char boardState[3][3];

	for(int i=0; i<3;i++){
		for(int j=0; j<3;j++){
			boardState[i][j]=' ';
		}
	}

	renderBoard(boardState);

	int freeFields=9;
	while(freeFields>0){
		printf("Make your move: \n");

		int x,y;

		bool isFieldValid=false;
		while(!isFieldValid){
			scanf("%d %d", &x, &y);
			if(x<1||x>3||y<1||y>3){
				printf("Invalid coordinated. Enter coordinates between 1 and 3.\n");
				continue;
			}

			printf("You entered %d %d\n", x, y);

			if(boardState[x-1][y-1]!=' '){
				printf("Field already taken. Choose a different one.\n");
				continue;
			}

			isFieldValid=true;
		}

		boardState[x-1][y-1]=side;
		freeFields--;

		renderBoard(boardState);
	}

	printf("Game ends!");

	return 0;
}
