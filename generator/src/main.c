/*
** EPITECH PROJECT, 2017
** generator
** File description:
** main.c
*/

#include <generator.h>

void target_hole(int pos, generator_t *generator)
{
	if (MAP[pos] != '\n')
		MAP[pos] = '*';
	if (check_outside_pos(pos - 1, generator) == false)
		MAP[pos - 1] = '*';
	if (check_outside_pos(pos + 1, generator) == false)
		MAP[pos + 1] = '*';
	if (check_outside_pos(pos - 2, generator) == false)
		MAP[pos - 2] = '*';
	if (check_outside_pos(pos + 2, generator) == false)
		MAP[pos + 2] = '*';
}

void place_random_hole(generator_t *generator)
{
	target_hole(1, generator);
	target_hole(1 + LEN_X, generator);
	target_hole(rand() % (SIZE - 2), generator);
	target_hole(rand() % (SIZE - 2), generator);
	if (SIZE <= 40)
		return;
	target_hole(rand() % (SIZE - 2), generator);
	target_hole(rand() % (SIZE - 2), generator);
	target_hole(rand() % (SIZE - 2), generator);
	target_hole(rand() % (SIZE - 2), generator);

}

void cheat(generator_t *generator)
{
	MAP[0] = '*';
	MAP[1] = '*';
	MAP[4] = '*';
	destroy_generator(generator);
	exit(0);
}

void my_signals(int sig)
{
	if (sig == SIGSEGV)
		exit(84);
}

int main(int ac, char **av)
{
	generator_t generator = init_generator();

	if (ac != 4 && ac != 3)
		return (84);
	signal(SIGSEGV, &my_signals);
	if (set_generator(&generator, av) != 0)
		return (84);
	srand(time(NULL));
	if (generator.len.x == 2 && generator.len.y == 2)
		cheat(&generator);
	start_backtrack(&generator);
	if (generator.perfect == false)
		place_random_hole(&generator);
	if (write(1, generator.map, generator.size - 1) == -1) {
		destroy_generator(&generator);
		return (84);
	}
	destroy_generator(&generator);
	return (0);
}