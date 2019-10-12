//
// Created by Екатерина on 2019-10-11.
//

#include "minishell.h"

unsigned int	define_ctlcmnd(unsigned int parsed, char receivedchar)
{
	if (receivedchar == 'h') //host
		return (SET_BIT(parsed, 0));
	if (receivedchar == 'H')
		return (SET_BIT(parsed, 1));
	if (receivedchar == 'u')
		return (SET_BIT(parsed, 2));
	if (receivedchar == 'A') //time
		return (SET_BIT(parsed, 3));
	if (receivedchar == 't')
		return (SET_BIT(parsed, 4));
	if (receivedchar == 'T')
		return (SET_BIT(parsed, 5));
	if (receivedchar == 'd')
		return (SET_BIT(parsed, 6));
	if (receivedchar == '@')
		return (SET_BIT(parsed, 7));
	if (receivedchar == 'w') // his
		return (SET_BIT(parsed, 8));
	if (receivedchar == 'W')
		return (SET_BIT(parsed, 9));
	if (receivedchar == '$')
		return (SET_BIT(parsed, 10));
	if (receivedchar == '#')
		return (SET_BIT(parsed, 11));
	return (0);
}

unsigned int parse_ps1(char *str)
{
	unsigned int parsed;
	int i;

	i = 0;
	parsed = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			parsed = define_ctlcmnd(parsed, str[++i]);
		}
		i++;
	}
	return (parsed);
}
int	check_parsed(unsigned int parsed, char receivedchar)
{
	if (receivedchar == 'h' && CHECK_FLAG(parsed, 0) == BIT(0))
		return (1);
	if (receivedchar == 'H' && CHECK_FLAG(parsed, 1) == BIT(1))
		return (1);
	if (receivedchar == 'u' && CHECK_FLAG(parsed, 2) == BIT(2))
		return (1);
	if (receivedchar == 'A' && CHECK_FLAG(parsed, 3) == BIT(3))
		return (1);
	if (receivedchar == 't' && CHECK_FLAG(parsed, 4) == BIT(4))
		return (1);
	if (receivedchar == 'T' && CHECK_FLAG(parsed, 5) == BIT(5))
		return (1);
	if (receivedchar == 'd' && CHECK_FLAG(parsed, 6) == BIT(6))
		return (1);
	if (receivedchar == '@' && CHECK_FLAG(parsed, 7) == BIT(7))
		return (1);
	if (receivedchar == 'w' && CHECK_FLAG(parsed, 8) == BIT(8))
		return (1);
	if (receivedchar == 'W' && CHECK_FLAG(parsed, 9) == BIT(9))
		return (1);
	if (receivedchar == '$' && CHECK_FLAG(parsed, 10) == BIT(10))
		return (1);
	if (receivedchar == '#' && CHECK_FLAG(parsed, 11) == BIT(11))
		return (1);
	return (0);
}
