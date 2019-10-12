/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 19:01:49 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/03/03 19:01:57 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 333

# include "unistd.h"
# include "stdlib.h"
# include "../libft/libft.h"

int get_next_line(const int fd, char **line);

#endif
