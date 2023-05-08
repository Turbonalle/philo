#include <fcntl.h>
#include <stdio.h>

void analyze(int n)
{
	read("result", O_RDONLY);

}

void test(int p, int life, int eat, int sleep, int n, int i)
{
	printf("TEST #%d : %d %d %d %d %d\n", i, p, life, eat, sleep, n);
	system("./philo %d %d %d %d %d > result", p, life, eat, sleep, n);
	analyze(n);
}

void multitest(void)
{
	int i;

	i = 0;
	printf("---- [4 philosophers] ---------------------------------------\n\n");
	test(4, 410, 200, 200, 10, ++i);
	test(4, 310, 200, 100, 10, ++i);

	test(4, 410, 200, 200, 10, ++i);
	test(4, 410, 200, 200, 10, ++i);
	test(4, 410, 200, 200, 10, ++i);
	test(4, 410, 200, 200, 10, ++i);
}

int main(int ac, char *av[])
{
	if (ac == 1)
		multitest();
	else if (ac == 6)
		test(av[1], av[2], av[3], av[4], av[5], 1);
	return (0);
}