#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*uc_dst;
	const char	*uc_src;
	size_t		i;

	uc_dst = dst;
	uc_src = src;
	if (dst < src)
		while (0 < len--)
			*uc_dst++ = *uc_src++;
	else if (dst > src)
	{
		i = len;
		while (0 < i--)
			uc_dst[i] = uc_src[i];
	}
	return (dst);
}
