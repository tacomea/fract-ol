#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char		*buffer;

	if (count > SIZE_MAX / size)
		return (NULL);
	buffer = (char *)malloc(count * size);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, count * size);
	return ((void *)buffer);
}
