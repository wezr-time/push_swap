#include "libft.h"
#include <stdio.h>
#include <bsd/string.h>

int main()
{
	char d[100];
	char s[100];


	printf("|%s| - |%s|\n", d, s);
	printf("%zu %zu\n", ft_strlen(s), ft_strlen(d));
	printf("%zu, %s\n", strlcat(d, "abcd", 10), d);
	printf("%zu, %s\n", ft_strlcat(s, "abcd", 10), s);
}