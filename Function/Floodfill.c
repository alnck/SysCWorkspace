//seçili alanın bölünmesi için floodfill algoritması

#include <stdio.h>
#include <stdlib.h>

char g_bitmap[10][22];

int read_bitmap(const char *path)
{
	FILE *f;
	int i;

	if ((f = fopen(path, "r")) == NULL)
		return 0;

	for (i = 0; i < 10; ++i)
		fgets(g_bitmap[i], 22, f);

	fclose(f);

	return 1;
}

void floodfill(int row, int col, int ch)
{
	if (g_bitmap[row][col] == '#' || g_bitmap[row][col] == ch)
		return;

	g_bitmap[row][col] = ch;

	floodfill(row - 1, col, ch);
	floodfill(row, col + 1, ch);
	floodfill(row + 1, col, ch);
	floodfill(row, col - 1, ch);
}

void disp_bitmap(void)
{
	int row, col;

	for (row = 0; row < 10; ++row) {
		for (col = 0; col < 20; ++col)
			putchar(g_bitmap[row][col]);
		putchar('\n');
	}
}

int main(void)
{
	if (!read_bitmap("bitmap.txt")) {
		fprintf(stderr, "cannot read bitmap!..\n");
		exit(EXIT_FAILURE);
	}

	floodfill(5, 5, '.');

	disp_bitmap();

    getchar();
	return 0;
}