/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:54:14 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/06/06 18:31:36 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	struct stat buf;

	lstat(argv[1], &buf);
	if (S_ISDIR(buf.st_mode) == 1)
		write(1, "d", 1);
	if (S_ISDIR(buf.st_mode) == 1)
		write(1, "f", 1);
	return (0);
}