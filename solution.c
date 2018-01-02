/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 02:28:58 by tadey             #+#    #+#             */
/*   Updated: 2018/01/02 02:29:01 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**  func determines whether the tetrimino pointed to by
**  alst can fit at the position specified by row and col.
*/

static	int	ft_check(t_tetris *alst, t_board *board, int row, int col)
{
	//vars- i is index, x and y holds the translated coordinates
	int	i;
	int	x;
	int	y;

	//init to i to coordinates directly before the first hash.
	i = 5 * alst->min_row + alst->min_col - 1;
	//so we increment to move to the first hash.
	while (++i < 20)
	{
		//if we find a hash at that coordinate.
		if (alst->shape[i / 5][i % 5] == '#')
		{
			//then we translate coordinate
			x = (i / 5) - alst->min_row;
			y = (i % 5) - alst->min_col;
			//we check if the translated coordinate fits in the board.
			if (!(0 <= row + x && row + x < board->size))
				return (0);
			if (!(0 <= col + y && col + y < board->size))
				return (0);
			//making sure that coordinate is empty so that
			//we can place the translated hash.
			if (board->map[row + x][col + y] != '.')
				return (0);
		}
	}
	return (1);
}

/*
**  func places the tetrimino pointed to by alst at the
**  position specified by row and col.
*/

static void		ft_place_piece(t_tetris *alst, t_board *board, int row, int col)
{
	int		i;
	int		x;
	int		y;

	i = 5 * alst->min_row + alst->min_col - 1;
	while (++i < 20)
		if (alst->shape[i / 5][i % 5] == '#')
		{
			x = (i / 5) - alst->min_row;
			y = (i % 5) - alst->min_col;
			board->map[row + x][col + y] = alst->name;
		}
}

/*
**  func removes the tetrimino pointed to by alst from
**  the position specified by row and col.
*/

static void		ft_remove_piece(t_tetris *alst, t_board *board, int row, int col)
{
	int		i;
	int		x;
	int		y;

	i = 5 * alst->min_row + alst->min_col - 1;
	while (++i < 20)
		if (alst->shape[i / 5][i % 5] == '#')
		{
			x = (i / 5) - alst->min_row;
			y = (i % 5) - alst->min_col;
			board->map[row + x][col + y] = '.';
		}
}

/*
**  func determines where the tetrimino pointed to by alst
**  can be placed on the board and sets it down.
**
**  If there is no solution to the problem for a given placement,
**  the function deletes the placement and moves to the next one.
*/

//deciding algorithm. try to fit the piece anywhere possible.
static int		ft_decision(t_tetris *alst, t_board *board)
{
	//two vars- row and col.
	int		row;
	int		col;

	//checks if the tetrimino is null, it will be empty if we're at the end
	//of the list.
	if (!alst)
		return (1);
	row = 0;//init row
	//loop while row is less that board's size
	while (row < board->size)
	{
		col = 0;
		//loop while col is less that board's size
		while (col < board->size)
		{
			//checks each and every position of the tetrimino
			//to see if it fits at (row, col) of the board of that particular
			//link.
			if (ft_check(alst, board, row, col))
			{
				//places this tet at position (row, col)
				ft_place_piece(alst, board, row, col);
				//calling the same func for the next piece. if this returns 1
				//then we found the sol and we return 1. if this returns 0
				//then we remove the piece and iterate col.
				if (ft_decision(alst->next, board))
					return (1);
				else
					ft_remove_piece(alst, board, row, col);
			}
			col++;
		}
		row++;//iterate row if you can't place it on any col. on the previos row
	}
	//return 0 if you can't place it anywhere on the map.
	return (0);
}

/*
**  func initiates the recursive backtracking algorithm.
*/

//wrapper func. that executes the sol algorithm.
int				ft_solution(t_tetris **alst, t_board *board)
{
	//if ft_decision returns 0 we increment board size
	//if it returns true then we ret 1. that means we
	//found a sol.
	while (!ft_decision(*alst, board))
		(board->size)++;
	return (1);
}
