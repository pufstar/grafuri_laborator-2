#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "windows.h"
#include <fstream>

using namespace std;

ofstream out("sol.txt");

typedef struct {
	short x, y, father;
} Node;

Node Q[1000000];

bool vis[63][5300];
int n = 1, m = 0;

short dl[] = { 1, 0, -1, 0 };
short dc[] = { 0, 1, 0, -1 };

void print_m(int matrix[53][530]) {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (matrix[i][j] == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("X");
			}
			else if (matrix[i][j] == 0)
				printf(" ");
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("*");
			}
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	for (int i = 1; i <= 52; i++)
		for (int j = 1; j <= 500; j++)
			vis[i][j] = 0;
	short lab[63][5300], sx = 0, sy = 0, fx = 0, fy = 0;
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

	int left = 1, right = 1;

	Q[left].x = sx;
	Q[left].y = sy;
	Q[left].father = 0;
	vis[sx][sy] = 1;

	while (left <= right) {
		//lab[Q[left].x][Q[left].y] = -1;
		//print_m(lab);

		for (int i = 0; i < 4; ++i) {
			int dx = Q[left].x + dl[i];
			int dy = Q[left].y + dc[i];

			if (vis[dx][dy] == 0 && lab[dx][dy] == 0) {
				Q[++right].father = left;
				Q[right].x = dx;
				Q[right].y = dy;
				vis[dx][dy] = 1;
			}

			if (dx == fx && dy == fy) {
				left = right + 1;
				//printf("found et\n");
			}
		}

		left++;
	}

	while (right != 0) {
		lab[Q[right].x][Q[right].y] = -1;
		right = Q[right].father;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (lab[i][j] == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("X");
				//out << char(178);
			}
			else if (lab[i][j] == 0)
				printf(" ");
				//out << ' ';
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf("*");
				//out << "+";
			} 
		}
		printf("\n");
		//out << '\n';
	}

	return 0;

}