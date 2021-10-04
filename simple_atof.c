#include "fractol.h"
#include <math.h>
#include <limits.h>

static int	ft_atoi_v2(const char **str)
{
	long	rtn;
	int		sign;

	rtn = 0;
	sign = 1;
	while (('\t' <= **str && **str <= '\r') || **str == ' ')
		(*str)++;
	if (**str == '-')
		sign = -1;
	if (**str == '+' || **str == '-')
		(*str)++;
	while ('0' <= **str && **str <= '9')
	{
		if ((rtn * 10 + **str - '0') / 10 != rtn)
		{
			if (sign == 1)
				return ((int)(LONG_MAX));
			return ((int)(LONG_MIN));
		}
		rtn = rtn * 10 + **str - '0';
		(*str)++;
	}
	return ((int)(sign * rtn));
}

double	simple_atof(char *str)
{
	double	rtn;
	int		cnt;
	int		sign;

	sign = 1;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	rtn = ft_atoi_v2((const char **)&str);
	cnt = 0;
	if (*str == '.')
	{
		str++;
		while ('0' <= *str && *str <= '9')
		{
			cnt++;
			rtn += (*str++ - '0') * pow(0.1, cnt);
		}
	}
	return (sign * rtn);
}

//#include "printf.h"
//#include <stdlib.h>
//
//int main()
//{
//	{
//		char *str = "-12.12";
//		printf("ft: %f \n", simple_atof(str));
//		printf("li: %f \n", atof(str));
//	}
//	{
//		char *str = "-12.1212121212";
//		printf("ft: %f \n", simple_atof(str));
//		printf("li: %f \n", atof(str));
//	}
//}
