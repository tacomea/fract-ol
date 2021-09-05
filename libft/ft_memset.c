#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*uc;

	uc = (unsigned char *)b;
	while (0 < len--)
		*uc++ = c;
	return (b);
}
