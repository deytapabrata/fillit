/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 02:28:31 by tadey             #+#    #+#             */
/*   Updated: 2018/01/02 02:28:35 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**  func creates a t_board element board that places the tetriminos.
*/

static void		ft_init_board(t_board *board)
{
	//two vars- coordinates, row and col respectively
	int			i;
	int			j;

	i = -1;//init i to -1.
	//looping through max row size of max 26 tets.
	while (++i < 104)
	{
		j = 0;//init j to 0;
		//looping through max col size of max 26 tets.
		while (j < 104)
			board->map[i][j++] = '.';//places empty slots
	}
	board->size = 4;//initializing board size to 4, getsize will upgrd if needed
}

/*
**  func gets the initial minimum dimensions for the board.
*/

static int		ft_getsize(t_tetris *alst, int i)
{
	//two vars
	int			count;//counter
	t_tetris	*current;//points to current link

	count = 0;//init count
	current = alst;//setting current to head.
	//looping until current points to the end of the list.
	while (current)
	{
		current = current->next;//setting current to point to the next link.
		count++;//iterate counter.
	}
	//looking for smallest square whose val is greater than 4 * no. of tets.
	while ((i * i) < 4 * count)
		i++;//iterate to check the next square
	return (i);//return the min dimensions
}

/*
**  func prints the solution to standard output.
*/

static void		ft_print(t_board *board)
{
	int		i;//index

	i = -1;//init i
	//printing board->size + 1 (1 for \n) times board->size
	while (++i < (board->size + 1) * board->size)
		if (i % (board->size + 1) == board->size)
			ft_putchar('\n');
		else
			ft_putchar(board->map[i / (board->size + 1)][i % (board->size + 1)]);
}

int	main(int argc, char **argv)
{
	char *file;//pointer that points to the file
	int fd;//fd
	char buff[BUFF_SIZE];
	t_tetris *alst;
	t_board *board;

	//if the number of argc is not 2 then return an error cuz there's
	//..nothing to read.
	if (argc != 2)
		return(ft_nothing_to_read());//return an error.
	alst = NULL;//set alst to NULL.
	if (!(board = (t_board*)malloc(sizeof(t_board))))//malloc
		return ((int)ft_null_err());//ret error if it's null.
	file = argv[1];//reads the 2nd argument that is the file name
	fd = open(file, O_RDONLY);//opens the file with readonly access.
	if (!(fd = ft_read(fd, buff)))//calls ft_read to read/check if the file's val
		return (0);//if fd is 0 i.e end of the file then return 0.
	if (!(alst = ft_parse_tet(buff, 0, fd)))//expecting list to be ret
			return (0);
	ft_init_board(board);//setting up the board.
	board->size = ft_getsize(alst, 2);//setting the board. passing the min size.
	ft_solution(&alst, board);//solving
	ft_print(board);//pringting the sol.
	return (1);
}
