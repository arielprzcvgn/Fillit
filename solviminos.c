/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solviminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:30:12 by ariperez          #+#    #+#             */
/*   Updated: 2019/01/17 16:00:19 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		place_piece(char **board, char **tetriminos, int pos, int size)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (count < 4)
	{
		if (ft_isalpha(tetriminos[i / 5][i % 5]))
		{
			if (pos / size + i / 5 >= size || pos % size + i % 5 >= size)
				return (0);
			if (board[pos / size + i / 5][pos % size + i % 5] == '.' && ++count)
				board[pos / size + i / 5][pos % size + i % 5] =
					tetriminos[i / 5][i % 5];
			else
				return (0);
		}
		i++;
	}
	return (1);
}

char	**makeboard(int size)
{
	int		i;
	int		j;
	char	**board;

	if ((board = malloc(sizeof(*board) * (size + 1))) == NULL)
		return (0);
	i = -1;
	while (++i < size)
	{
		if ((board[i] = malloc(sizeof(**board) * (size + 1))) == NULL)
			return (0);
		j = -1;
		while (++j < size)
			board[i][j] = '.';
	}
	return (board);
}

char	**resolve(char **board, char ***tetriminos, int size, int solved)
{
	char	**begin;
	int		nbtetri;
	int		pos;

	pos = 0;
	nbtetri = 0;
	while (tetriminos[nbtetri])
		nbtetri++;
	while (solved < nbtetri)
	{
		begin = ft_copytab(board);
		if (place_piece(board, tetriminos[solved], pos, size) &&
				(board = resolve(board, tetriminos, size, solved + 1)))
			return (board);
		else
			board = begin;
		if (++pos >= size * size && solved == 0 && size++ &&
				(board = makeboard(size)))
			pos = 0;
		else if (pos >= size * size)
			return (0);
	}
	return (board);
}

char	**solviminos(char ***tetriminos)
{
	char	**board;
	int		size;
	int		nbtetri;

	nbtetri = 0;
	while (tetriminos[nbtetri])
		nbtetri = nbtetri + 1;
	if (nbtetri == 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	size = 2;
	while (size * size < (nbtetri * 4))
		size++;
	board = makeboard(size);
	board = resolve(board, tetriminos, size, 0);
	return (board);
}

int		main(int argc, char **argv)
{
	char	***tetriminos;
	int		i;
	int		j;

	if (argc != 2)
		return (0);
	if ((tetriminos = malloc(sizeof(*tetriminos) * (26 + 1))) == NULL)
		return (0);
	i = -1;
	while (++i < 28)
	{
		if ((tetriminos[i] = malloc(sizeof(**tetriminos) * (4 + 1))) == NULL)
			return (0);
		j = -1;
		while (++j < 6)
			if ((tetriminos[i][j] = malloc(4 + 1)) == NULL)
				return (0);
	}
	tetriminos = file_it(argv[1], tetriminos);
	ft_puttab(solviminos(tetriminos));
	free(tetriminos);
	return (0);
}
