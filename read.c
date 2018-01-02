/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 02:28:50 by tadey             #+#    #+#             */
/*   Updated: 2018/01/02 02:28:53 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**  func checks if the file is valid by checking if
**  each tetrimino is composed of four rows of five characters, these five
**  characters being either four #'s or .'s followed by a newline '\n'.
**
** 	each tetrimino should be separated by a \n.
**	if the file is either empty or exceeds 26 tetriminos, it is invalid.
*/

static	int	ft_check_file(char buff[], int shift)
{
	int i;

	i = 0;
	while (i < 20)
	{
		if ((i % 5) < 4)
			if (buff[shift + i] != '.' && buff[shift + i] != '#')
				return (0);
		if ((i % 5) == 4 && buff[shift + i] != '\n')
			return (0);
		i++;
	}
	if (buff[shift + i] && buff[shift + i] != '\n')
		return (0);
	return (1);
}

/*
**  func checks if the tetriminos in the file are
**  valid by counting the total number of neighbors and the total number of
**  hashes ('#').
**
**  neighbors are the hash ('#') next to a given hash.
**	if the number of neighors is 6 or 8, the tetrimino is valid.
**
**  if less than four hash are found per 20 bytes read, the tetrimino is
**  invalid.
*/

static	int	ft_check_tetrimino(char buff[], int shift, int hash)
{
	int		i;
	int		neighbor;

	i = 0;
	neighbor = 0;
	while (i < 19)
	{
		if (buff[shift + i] == '#')
		{
			if (i + 1 < 19 && (i + 1) % 5 != 4 && buff[shift + i + 1] == '#')
				neighbor++;
			if (i - 1 >= 0 && (i - 1) % 5 != 4 && buff[shift + i - 1] == '#')
				neighbor++;
			if (i + 5 < 19 && buff[shift + i + 5] == '#')
				neighbor++;
			if (i - 5 >= 0 && buff[shift + i - 5] == '#')
				neighbor++;
			hash++;
		}
		i++;
	}
	if (hash != 4 || (neighbor != 6 && neighbor != 8))
		return (0);
	return (1);
}

/*
**	ft_read reads and counts the number of bytes in the file to
**	..check if the tetriminos and files are valid.
*/

int	ft_read(int fd, char buff[])//params- file descriptor & char array
{
	//vars- one to shift bytes and other to store return val of read
	int shift;
	int read_ret;

	shift = 0;//initializing shift to 0
	ft_strclr(buff);//sets every char to \0 in char array buff
	//attempts to read BUFF_SIZE from the file associated with fd,
	//and places the characters read into buff.
	read_ret = read(fd, buff, BUFF_SIZE);
	if (read_ret <= 0)
		return (ft_bad_size());
	while (shift < read_ret)
	{
		if(!ft_check_file(buff, shift))//if file's empty/bad fmt return err
			return (ft_bad_format_file());
		if (!ft_check_tetrimino(buff, shift, 0))//if tet is empty/bad ret err
			return (ft_bad_format_tetriminos());
		shift += 21;//move to the nxt tetrimino
	}
	//shift should be greater than read_ret bc there shouldn't be a '\n' at eof
	if (shift == read_ret)
		return (ft_bad_format_file());
	return (read_ret);
}
