#include "../include/game.h"
void print_bits(uint32_t n)
{
	for (int i = 0; i < 32; i++)
	{
		uint32_t bit = n & (1 << (31 - i));
		if (bit > 0) printf("1");
		else printf("0");
	}
	printf("\n");
}
int main()
{
	
	srand(time(nullptr));
	Game game;
	game.run();

	return 0;
}