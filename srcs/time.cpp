#include "time.hpp"

unsigned long	ft_abs_time(void)
{
	struct timeval	tv;
	unsigned long	s;
	unsigned long	u;

	if (gettimeofday(&tv, NULL) == -1)
		std::cerr << "Error: GETTIMEOFDAY(2)" << std::endl;
	s = tv.tv_sec * 1000;
	u = tv.tv_usec / 1000;
	return (s + u);
}
