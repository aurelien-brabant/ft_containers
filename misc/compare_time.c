#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "./compare_time <std_time> <ft_time>");
		return EXIT_FAILURE;
	}

	double stdTime = atof(argv[1]), ftTime = atof(argv[2]);

	if (stdTime < 0 || ftTime < 0) {
		fprintf(stderr, "Parsed invalid negative execution time");
		return EXIT_FAILURE;
	}

	double longestTime = stdTime > ftTime ? stdTime : ftTime, shortestTime = stdTime < ftTime ? stdTime : ftTime;

	double difference = longestTime / shortestTime;

	printf("ft \033[1m%6.2f\033[0mx %s\033[0m", difference, longestTime == ftTime ? "\033[0;31mSLOWER" : "\033[0;32mFASTER");

	return 0;
}
