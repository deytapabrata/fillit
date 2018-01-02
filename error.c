/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 02:27:55 by tadey             #+#    #+#             */
/*   Updated: 2018/01/02 02:27:58 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	error func when there's nothing to read from stdin
*/

int	ft_nothing_to_read(void)
{
	ft_putendl("Usage error: ./fillit sample");
	return (0);
}

/*
**	error func when the file is either empty/has more than 26 tetriminos.
*/

int ft_bad_size(void)
{
	ft_putendl("error");
	return (0);
}

/*
**	error func when the file is not formatted well.
*/

int	ft_bad_format_file(void)
{
	ft_putendl("error");
	return (0);
}

/*
**	error func when the tetriminos are not formatted well.
*/

int	ft_bad_format_tetriminos(void)
{
	ft_putendl("error");
	return (0);
}

/*
**	error func called when the malloc ret null during checking
**	ft_parse_tet
*/

t_tetris	*ft_null_err(void)
{
	ft_putendl("error");
	return (NULL);
}
