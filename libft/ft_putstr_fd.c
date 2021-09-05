#include <unistd.h>
#include "libft.h"
#include <limits.h>

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > INT_MAX)
	{
		write(fd, s, INT_MAX);
		len -= INT_MAX;
		s += INT_MAX;
	}
	write(fd, s, ft_strlen(s));
}

//#include <string.h>
//#include <printf.h>
//
//int main() {
//	char *s = malloc(2147483651);
//	memset(s, 'a', 2147483650);
//	s[2147483650] = 0;
////	printf("%s", &s[2147483647]);
////	ft_putstr_fd(s, 1);
//	FILE *fp = fopen("a.txt", "a");
//	for (long i = 0; i < 2147483650; i++)
//		fprintf(fp, "%c", 'a');
//	fclose(fp);
//}
