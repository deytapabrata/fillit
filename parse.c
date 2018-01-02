/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 02:28:42 by tadey             #+#    #+#             */
/*   Updated: 2018/01/02 02:28:46 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	ft_new_link allocates space for a new t_tetris list element, sets
**	the initial values, and returns a pointer that points to this elmnt.
*/

static	t_tetris	*ft_new_link(void)
{
	//vars- i, j rows and col respectively. *link is a new link;
	int			i;
	int			j;
	t_tetris	*link;

	i = 0;
	if(!(link = (t_tetris *)malloc(sizeof(t_tetris))))
		return (NULL);
	//init struct- name to blank, min_row/min_col to 4 bc row/col will be less
	//than 4 always.
	link->name = '-';
	link->min_row = 4;
	link->min_col = 4;
	link->next = NULL;
	while (i < 4)//looping through coordinates
	{
		j = 0;
		while (j < 4)
			link->shape[i][j++] = '.';//empty slots created
		link->shape[i][j] = '\n';//creating \n at the end of the col.
		i++;
	}
	return (link);
}

/*
**	ft_link replaces the default values of the given t_tetris element
**	with information from the buffer.
*/

static	void	ft_fill_link(t_tetris **link, char buff[], int i, int shift)
{
	int			x;//counter var for tets
	t_tetris	*current;//the pointer points to current link
	char		*alphabets;//lists of names

	x = 0;//init x to 0
	alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//string of alphabets.
	current = *link;//pointing current to link.
	current->name = alphabets[i];//name our current tet based on the no. of its link
	//loop for 20 bytes
	while (x < 20)
	{
		//everytime we find a hash
		if (buff[shift + x] == '#')
		{
			//updating min_row/min_col
			if (x % 5 < current->min_col)
				current->min_col = x % 5;
			if (x / 5 < current->min_row)
				current->min_row = x / 5;
			//we're putting the hash in the link elem.
			current->shape[x / 5][x % 5] = '#';
		}
		x++;
	}
}

/*
**	func adds the t_tetris link passed through as an arg to the end of the list
*/

static	void	ft_add_link(t_tetris **alst, t_tetris **link)
{
	//vars- *current- points to the current elem(current is always going to change)
	//*previous- points to previous elem.
	t_tetris	*current;
	t_tetris	*previous;

	//when we first call ft_add_link, *alst will be empty, so we set it to the link.
	if(!(*alst))
		*alst = *link;
	//if it's not empty, the we set current to the head first.
	else
	{
		current = *alst;
		//while it's not null, then we set previous to current, and make
		//current point to the next link.
		while (current != NULL)
		{
			previous = current;
			current = current->next;
		}
		//at the end, link previous's next to the link we are passing.
		previous->next = (*link);
	}
}

/*
**	ft_parse_tetriminos reads through the character buffer buff[]
**  and creates t_tetris links for each tetrimino contained in it.
*/

t_tetris	*ft_parse_tet(char buff[], int shift, int ret)
{
	int			i;
	t_tetris	*alst;//pointer to head of the list.
	t_tetris	*current;//pointer to the current link.

	i = -1;
	alst = NULL;//setting it to NULL.
	while (shift < ret)
	{
		//protecting our malloc
		if (!(current = ft_new_link()))
			return (ft_null_err());
		//filling our new link passing add. of current/buffer
		//i iterates first before we call our func/shift
		ft_fill_link(&current, buff, ++i, shift);
		//add_links puts the current link at the end of the list.
		//add_link passes address of alst and current
		ft_add_link(&alst, &current);
		//shifts 21 bytes to move on to the next tet.
		shift += 21;
	}
	return (alst);
}
