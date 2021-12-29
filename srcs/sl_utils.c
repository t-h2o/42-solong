#include	"sl.h"
int
	sl_strlen(char *s)
{
	int	r;

	r = 0;
	while (s[r])
		r++;
	return (r);
}
