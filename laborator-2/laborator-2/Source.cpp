#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "windows.h"

int vis[53][530], n = 1, m = 0;
int dl[] = { 1, 0, -1, 0 };
int dc[] = { 0, 1, 0, -1 };

int go(int matrix[53][530], int x, int y, int fx, int fy) {
	vis[x][y] = 1;
	if (x == fx && y == fy) {
		printf("FOUND IT\n");
		matrix[x][y] = -1;
		return 1;
	}
	int isFound = 0;
	for (int i = 0; i < 4; i++) {
		int dx = x + dl[i], dy = y + dc[i];
		if (vis[dx][dy] == 0 && matrix[dx][dy] == 0) {
			isFound = go(matrix, dx, dy, fx, fy);
			matrix[x][y] = -isFound;
			if (isFound == 1)
				return 1;
		}
	}
	return isFound;
}

int main() {
	for (int i = 1; i <= 52; i++)
		for (int j = 1; j <= 500; j++)
			vis[i][j] = 0;
	int lab[53][530], sx = 0, sy = 0, fx = 0, fy = 0;
	FILE *file;
	file = fopen("labirint.txt", "r");
	char c = NULL;
	while (c != EOF) {
		int j = 1;
		c = getc(file);
		while (c != EOF && c != '\n') {
			if (c == ' ') lab[n][j++] = 0;
			else if (c == '1') lab[n][j++] = 1;
			else if (c == 'S') {
				sx = n;
				sy = j;
				lab[n][j++] = 0;
			}
			else if (c == 'F') {
				fx = n;
				fy = j;
				lab[n][j++] = 0;
			}
			c = getc(file);
		}
		m = j;
		n++;
	}

	n--;
	m--;

	go(lab, sx, sy, fx, fy);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (lab[i][j] == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("X");
			}
			else if (lab[i][j] == 0)
				printf(" ");
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("*");
			} 
		}
		printf("\n");
	}

	return 0;

}