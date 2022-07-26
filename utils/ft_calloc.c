#include "../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = b;
	while (len > 0)
	{
		ptr[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}

void	ft_bzero(void	*s, size_t	n)
{
	s = ft_memset(s, '\0', n);
}

void	*ft_calloc(int count, int size)
{
	void	*ptr;
	int		sizee;

	sizee = count * size;
	ptr = (void *)malloc(sizee);
	if (ptr != NULL)
		ft_bzero(ptr, sizee);
	else
		exit(1);
	return (ptr);
}