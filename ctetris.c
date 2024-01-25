
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <wchar.h>

#define WIDTH 10
#define HEIGHT 20
#define EMPTY 0
#define BLOCK 1
#define FROZEN 2
#define FPS 5

enum BlockNames
{
	J, L, S, Z, O, I, T
};
struct BlockRepresentations
{
	int J[4][4][4] = {
		{ {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
		{ {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
		{ {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
		{ {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	};
	int L[4][4][4] = {
		{ {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{ {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
		{ {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
		{ {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
	};
	int S[4][4][4] = {
		{ {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{ {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
		{ {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
		{ {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
	};
	int Z[4][4][4] = {
		{ {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{ {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
		{ {0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
		{ {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
	};
	int O[4][4][4] = {
		{ {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{ {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{ {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
		{ {0, 0, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
	};
	int I[4][4][4] = {
		{ {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{ {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
		{ {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
		{ {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},
	};
	int T[4][4][4] = {
		{ {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		{ {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
		{ {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
		{ {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
	};
};
struct Block
{
	int x_size;
	int y_size;
	int (*reprPtr)[4];
};
int main()
{
	srand(time(NULL));
	int figure_fall(int game_field[HEIGHT][WIDTH], int figure[4][2]);
	void render_game(int game_field[HEIGHT][WIDTH]);
	void set_rand_block(int game_field[HEIGHT][WIDTH], int* cur_block_x, int* cur_block_y, int figure[4][2]);
	void clear_game_field(int game_field[HEIGHT][WIDTH]);
	setlocale(LC_ALL, "");
	int game_field[HEIGHT][WIDTH] = { 0 };
	int cur_block_x = 0, cur_block_y = 0;
	int figure[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };
	int is_fall_figure; 

	set_rand_block(game_field, &cur_block_x, &cur_block_y, figure);
	while (1)
	{
		render_game(game_field);
		//clear_game_field(game_field);
		is_fall_figure = figure_fall(game_field, figure);
		if (is_fall_figure)
		{
			set_rand_block(game_field, &cur_block_x, &cur_block_y, figure);
		}
	}

	return 0;
}
void clear_game_field(int game_field[HEIGHT][WIDTH])
{
	for (int row = 0; row < HEIGHT; row++)
	{
		for (int col = 0; col < WIDTH; col++)
		{
			game_field[row][col] = 0;
		}
	}
}
void draw_game(int game_field[HEIGHT][WIDTH])
{
	printf("+");
	for (int i = 0; i < WIDTH * 2; i++)
		printf("*");
	printf("+\n");
	for (int row = 0; row < HEIGHT; row++)
	{
		printf("*");
		for (int col = 0; col < WIDTH; col++)
		{
			if (game_field[row][col] == EMPTY)
				printf("· ");
			else if (game_field[row][col] == BLOCK)
			{
				printf("$ ");
			}
			else if (game_field[row][col] == FROZEN)
				printf("# ");
		}
		printf("*\n");
	}
	printf("+");
	for (int i = 0; i < WIDTH * 2; i++)
		printf("*");
	printf("+\n");
}
void render_game(int game_field[HEIGHT][WIDTH])
{
	void draw_game(int game_field[HEIGHT][WIDTH]);

	draw_game(game_field);
	Sleep(1000 / FPS);
	system("cls");	
}

Block get_random_block()
{
	int rand_block = rand() % 7;
	int rand_block_repr = rand() % 4;
	int arr[4][4] = {0};
	
	BlockRepresentations block_reprs;
	Block block;

	if (rand_block == J)
	{
		block.reprPtr = block_reprs.J[rand_block_repr];
		block.x_size = 4;
		block.y_size = 4;
	}
	else if (rand_block == L)
	{
		block.reprPtr = block_reprs.L[rand_block_repr];
		block.x_size = 4;
		block.y_size = 4;
	}
	else if (rand_block == S)
	{
		block.reprPtr = block_reprs.S[rand_block_repr];
		block.x_size = 4;
		block.y_size = 4;
	}
	else if (rand_block == Z)
	{
		block.reprPtr = block_reprs.Z[rand_block_repr];
		block.x_size = 4;
		block.y_size = 4;
	}
	else if (rand_block == O)
	{
		block.reprPtr = block_reprs.O[rand_block_repr];
		block.x_size = 4;
		block.y_size = 4;
	}
	else if (rand_block == I)
	{
		block.reprPtr = block_reprs.I[rand_block_repr];
		block.x_size = 4;
		block.y_size = 4;
	}
	else if (rand_block == T)
	{
		block.reprPtr = block_reprs.T[rand_block_repr];
		block.x_size = 4;
		block.y_size = 4;
	}
	return block;
}
void set_block(Block block, int game_field[HEIGHT][WIDTH], int* cur_block_x, int* cur_block_y, int figure[4][2])
{
	int spawn_x = (WIDTH + block.x_size) / 4;
	*cur_block_x = spawn_x;
	*cur_block_y = 0;
	int fig_elem_counter = 0;
	for (int row = 0; row < block.y_size; row++)
	{
		for (int col = 0; col < block.x_size; col++)
		{
			if (block.reprPtr[row][col] == BLOCK)
			{
				game_field[row][spawn_x + col] = BLOCK;
				figure[fig_elem_counter][0] = spawn_x + col;
				figure[fig_elem_counter][1] = row;
				fig_elem_counter++;
			}
		}
	}
	system("pause");

}
void set_rand_block(int game_field[HEIGHT][WIDTH], int *cur_block_x, int *cur_block_y, int figure[4][2])
{
	int(*game_field_ptr)[WIDTH] = game_field;
	Block get_random_block();
	Block block = get_random_block();
	set_block(block, game_field_ptr, cur_block_x, cur_block_y, figure);

}

int figure_fall(int game_field[HEIGHT][WIDTH], int figure[4][2])
{
	for (int i = 3; i >= 0; i--)
	{
		if (figure[i][1] < HEIGHT-1 && (game_field[figure[i][1] + 1][figure[i][0]] == EMPTY
			|| game_field[figure[i][1]+1][figure[i][0]] == BLOCK))
		{
			game_field[figure[i][1]][figure[i][0]] = EMPTY;
			figure[i][1]++;
		}
		else if (figure[i][1] < HEIGHT-1 && game_field[figure[i][1] + 1][figure[i][0]] == FROZEN)
		{
			// Froze figure
			for (int j = 0; j < 4; j++)
			{
				game_field[figure[j][1]][figure[j][0]] = FROZEN;
			}
			return 1;
		}
		else if (figure[i][1] >= HEIGHT-1)
		{
			// Froze figure
			for (int j = 0; j < 4; j++)
			{
				game_field[figure[j][1]][figure[j][0]] = FROZEN;
			}
			return 1;
				
		}
	}
	for (int i = 0; i < 4; i++)
	{
		game_field[figure[i][1]][figure[i][0]] = BLOCK;
		
	}
	for (int p = 0; p < 4; p++)
		printf("figure x: %d, figure y: %d\n", figure[p][0], figure[p][1]);
	return 0;
}
