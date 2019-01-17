/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:31:09 by ariperez          #+#    #+#             */
/*   Updated: 2019/01/17 16:00:11 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		validtetriminos(char *buf)
{
	int		i;
	int		count;
	int		link;

	count = 0;
	link = 0;
	i = -1;
	while (++i < 21)
		if (buf[i] == '#')
		{
			if (buf[i + 1] == '#')
				link++;
			if (buf[i - 1] == '#')
				link++;
			if (buf[i + 5] == '#')
				link++;
			if (buf[i - 5] == '#')
				link++;
			count++;
		}
	if (count == 4 && (link == 6 || link == 8))
		return (0);
	return (1);
}

int		checkerror(char *buf, char ***tetriminos)
{
	int		i;
	int		dot;
	int		ret;

	i = -1;
	ret = 0;
	dot = 0;
	while (++i < 21)
	{
		if ((i % 5 == 4 && buf[i] != '\n') || validtetriminos(buf) ||
		(buf[i] != '#' && buf[i] != '.' && buf[i] != '\n' && buf[i] != '\0'))
			ret = 1;
		else if (buf[i] == '.')
			dot++;
	}
	if (dot != 12)
		ret = 1;
	if (ret)
		free(tetriminos);
	return (ret);
}

char	***unitetri(char ***tetri)
{
	int		i;
	int		j;

	i = 0;
	while (tetri[i])
	{
		while (tetri[i][0][0] == '.' && tetri[i][0][1] == '.' &&
				tetri[i][0][2] == '.' && tetri[i][0][3] == '.' && (j = -1))
		{
			while (++j < 12 && (tetri[i][j % 3][j / 3] =
						tetri[i][j % 3 + 1][j / 3]))
				tetri[i][j % 3 + 1][j / 3] = '.';
		}
		while (tetri[i][0][0] == '.' && tetri[i][1][0] == '.' &&
				tetri[i][2][0] == '.' && tetri[i][3][0] == '.' && (j = -1))
		{
			while (++j < 12 && (tetri[i][j / 3][j % 3] =
						tetri[i][j / 3][j % 3 + 1]))
				tetri[i][j / 3][j % 3 + 1] = '.';
		}
		i++;
	}
	return (tetri);
}

char	***tetreadminos(int fd, char ***tetriminos, char *buf)
{
	int		i;
	char	letter;
	int		red;
	int		final;

	letter = 'A';
	while ((red = read(fd, buf, 21)) > 0)
	{
		buf[red] = '\0';
		final = red;
		if (checkerror(buf, tetriminos))
			return (NULL);
		i = -1;
		while (++i < 21)
			if (buf[i] == '#')
				tetriminos[letter - 'A'][i / 5][i % 5] = letter;
			else if (buf[i] == '.')
				tetriminos[letter - 'A'][i / 5][i % 5] = '.';
			else if (i % 5 == 4)
				tetriminos[letter - 'A'][i / 5][i % 5] = '\0';
		tetriminos[letter - 'A'][4] = 0;
		letter++;
	}
	tetriminos[letter - 'A'] = 0;
	return ((final == red + 21) ? NULL : tetriminos);
}

char	***file_it(char *file, char ***tetriminos)
{
	int		fd;
	char	*buf;

	if ((fd = open(file, O_RDONLY)) == -1 ||
			(buf = malloc(sizeof(*buf) * (21 + 1))) == NULL ||
			(tetriminos = tetreadminos(fd, tetriminos, buf)) == NULL)
	{
		ft_putstr("error\n");
		return (0);
	}
	free(buf);
	return (unitetri(tetriminos));
}
