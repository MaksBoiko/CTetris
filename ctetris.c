
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

#define WIDTH 10
#define HEIGHT 20
#define EMPTY 0
#define BLOCK 1
#define FROZEN 2
#define FPS 20
#define ROTATE 'w'
#define LEFT 'a'
#define RIGHT 'd'
#define FAST_FALLING 's'
#define ROTATION_CENTER 1

enum FigureNames
{
	J, L, S, Z, O, I, T
};
struct FigureRepresentations
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
		{ {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
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
struct Figure
{
	int x_size;
	int y_size;
	int type;
	int repr_type;
	int (*reprPtr)[4];
};
int main()
{
	srand(time(NULL));
	int figure_fall(int game_field[HEIGHT][WIDTH], int figure[4][2]);
	void render_game(int game_field[HEIGHT][WIDTH], int figure_arr[4][2]);
	void set_rand_figure(int game_field[HEIGHT][WIDTH], int* cur_figure_x, int* cur_figure_y, int figure[4][2]);
	void clear_game_field(int game_field[HEIGHT][WIDTH]);
	int keyboard_controller(int game_field[HEIGHT][WIDTH], int figure[4][2]);

	setlocale(LC_ALL, "");

	int game_field[HEIGHT][WIDTH] = { 0 };
	int cur_figure_x = 0, cur_figure_y = 0;
	int figure[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };
	int is_fall_figure;
	int is_change_figure_state = 0;

	set_rand_figure(game_field, &cur_figure_x, &cur_figure_y, figure);
	while (1)
	{
		render_game(game_field, figure);
		//clear_game_field(game_field);

		is_change_figure_state = keyboard_controller(game_field, figure);
		if (!is_change_figure_state )
		{
			is_fall_figure = figure_fall(game_field, figure);
		}
		
		if (is_fall_figure)
		{
			set_rand_figure(game_field, &cur_figure_x, &cur_figure_y, figure);
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
void draw_game(int game_field[HEIGHT][WIDTH], int figure_arr[4][2])
{
	int is_coord_in_figure(int figure_arr[4][2], int x, int y);
	printf("+");
	for (int i = 0; i < WIDTH * 2; i++)
		printf("*");
	printf("+\n");
	for (int row = 0; row < HEIGHT; row++)
	{
		printf("*");
		for (int col = 0; col < WIDTH; col++)
		{
			if (is_coord_in_figure(figure_arr, col, row))
			{
				printf("$ ");
			}
			else if (game_field[row][col] == EMPTY)
				printf("· ");
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
void render_game(int game_field[HEIGHT][WIDTH], int figure_arr[4][2])
{
	void draw_game(int game_field[HEIGHT][WIDTH], int figure_arr[4][2]);

	draw_game(game_field, figure_arr);
	Sleep(1000 / FPS);
	system("cls");	
}

Figure get_random_figure()
{
	int rand_figure = rand() % 7;
	int rand_figure_repr = rand() % 4;
	int arr[4][4] = {0};
	
	FigureRepresentations figure_reprs;
	Figure figure;

	if (rand_figure == J)
	{
		figure.reprPtr = figure_reprs.J[rand_figure_repr];
	}
	else if (rand_figure == L)
	{
		figure.reprPtr = figure_reprs.L[rand_figure_repr];
	}
	else if (rand_figure == S)
	{
		figure.reprPtr = figure_reprs.S[rand_figure_repr];
	}
	else if (rand_figure == Z)
	{
		figure.reprPtr = figure_reprs.Z[rand_figure_repr];
	}
	else if (rand_figure == O)
	{
		figure.reprPtr = figure_reprs.O[rand_figure_repr];
	}
	else if (rand_figure == I)
	{
		figure.reprPtr = figure_reprs.I[rand_figure_repr];
	}
	else if (rand_figure == T)
	{
		figure.reprPtr = figure_reprs.T[rand_figure_repr];
	}
	figure.x_size = 4;
	figure.y_size = 4;
	figure.type = rand_figure;
	figure.repr_type = rand_figure_repr;
	return figure;
}
void set_figure(Figure figure, int game_field[HEIGHT][WIDTH], int* cur_figure_x, int* cur_figure_y, int figure_arr[4][2])
{
	int spawn_x = (WIDTH + figure.x_size) / 4;
	*cur_figure_x = spawn_x;
	*cur_figure_y = 0;
	int fig_elem_counter = 0;
	for (int row = 0; row < figure.y_size; row++)
	{
		for (int col = 0; col < figure.x_size; col++)
		{
			if (figure.reprPtr[row][col] == BLOCK)
			{
				figure_arr[fig_elem_counter][0] = spawn_x + col;
				figure_arr[fig_elem_counter][1] = row;
				fig_elem_counter++;
			}
		}
	}
	system("pause");

}
void set_rand_figure(int game_field[HEIGHT][WIDTH], int *cur_figure_x, int *cur_figure_y, int figure[4][2])
{
	int(*game_field_ptr)[WIDTH] = game_field;
	Figure get_random_figure();
	Figure block = get_random_figure();
	set_figure(block, game_field_ptr, cur_figure_x, cur_figure_y, figure);

}

int figure_fall(int game_field[HEIGHT][WIDTH], int figure_arr[4][2])
{
	int figure_y;
	int is_frozen_block_down = 0;
	for (int i = 3; i >= 0; i--)
	{
		if (figure_arr[i][1] < HEIGHT - 1 && game_field[figure_arr[i][1] + 1][figure_arr[i][0]] == FROZEN)
		{
			is_frozen_block_down = 1;
			break;
		}
	}
	if (is_frozen_block_down)
	{
		// Froze figure
		for (int j = 0; j < 4; j++)
		{
			game_field[figure_arr[j][1]][figure_arr[j][0]] = FROZEN;
		}
		return 1;
	}
	for (int i = 3; i >= 0; i--)
	{
		figure_y = figure_arr[i][1];
		if (figure_y < HEIGHT-1 && (game_field[figure_y + 1][figure_arr[i][0]] == EMPTY
			|| game_field[figure_y +1][figure_arr[i][0]] == BLOCK))
		{
			game_field[figure_y][figure_arr[i][0]] = EMPTY;
			figure_arr[i][1]++;
		}
		else if (figure_y >= HEIGHT-1)
		{
			// Froze figure
			for (int j = 0; j < 4; j++)
			{
				game_field[figure_arr[j][1]][figure_arr[j][0]] = FROZEN;
			}
			return 1;
				
		}
	}
	for (int p = 0; p < 4; p++)
		printf("figure x: %d, figure y: %d\n", figure_arr[p][0], figure_arr[p][1]);

	return 0;
}
// side: 0 - left, 1 - right
void sides_figure_movement(int game_field[HEIGHT][WIDTH], int figure_arr[4][2], int side)
{
	int figure_x;
	if (side == 0)
	{
		int possible_moving_figure_parts_counter = 0;
		for (int i = 0; i < 4; i++)
		{
			figure_x = figure_arr[i][0];
			if (figure_x > 0 && game_field[figure_arr[i][1]][figure_x-1] != FROZEN)
			{
				possible_moving_figure_parts_counter++;
			}
		}
		if (possible_moving_figure_parts_counter == 4)
		{
			for (int i = 0; i < 4; i++)
			{
				game_field[figure_arr[i][1]][figure_arr[i][0]] = EMPTY;
				figure_arr[i][0]--;
			}
		}
	}
	else if(side == 1)
	{
		int possible_moving_figure_parts_counter = 0;
		for (int i = 3; i >= 0; i--)
		{
			figure_x = figure_arr[i][0];
			if (figure_x < WIDTH-1 && game_field[figure_arr[i][1]][figure_x + 1] != FROZEN)
			{
				possible_moving_figure_parts_counter++;
			}
		}
		if (possible_moving_figure_parts_counter == 4)
		{
			for (int i = 3; i >= 0; i--)
			{
				game_field[figure_arr[i][1]][figure_arr[i][0]] = EMPTY;
				figure_arr[i][0]++;
			}
		}
	}
}
int keyboard_controller(int game_field[HEIGHT][WIDTH], int figure_arr[4][2])
{
	void sides_figure_movement(int game_field[HEIGHT][WIDTH], int figure[4][2], int side);
	char key = 0;
	if (_kbhit())
		key = _getch();
	if (key == LEFT)
	{
		sides_figure_movement(game_field, figure_arr, 0);
		return 1;
	}
	else if (key == RIGHT)
	{
		sides_figure_movement(game_field, figure_arr, 1);
		return 1;
	}
	else if (key == ROTATE)
	{
		return 1;
	}
	else if (key == FAST_FALLING)
	{
		return 1;
	}
	return 0;
}
int is_coord_in_figure(int figure_arr[4][2], int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		if (figure_arr[i][0] == x && figure_arr[i][1] == y)
			return 1;
	}
	return 0;
}
void rotate_figure(int game_field[HEIGHT][WIDTH], int figure_arr[4][2])
{
	FigureRepresentations figure_reprs;
	Figure figure;
	

	
	
}

