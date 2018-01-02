/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 02:28:04 by tadey             #+#    #+#             */
/*   Updated: 2018/01/02 02:28:06 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

/*
**	define
*/

#define BUFF_SIZE 524

/*
**	structs
*/

typedef	struct	s_tetris
{
    char				name;
    char				shape[5][5];
    char				min_row;
    char				min_col;
    struct	s_tetris	*next;
}						t_tetris;

typedef struct  s_board
{
	char		map[104][104];
	int			size;
}				t_board;


/*
**	reading inputs (read.c)
*/

int				ft_read(int fd, char buff[]);

/*
**	parsing tetriminos (parse.c)
*/

t_tetris		*ft_parse_tet(char buff[], int shift, int ret);

/*
**	(solution.c) solving
*/

int				ft_solution(t_tetris **alst, t_board *b);

/*
**	(errors.c) errors
*/

int				ft_nothing_to_read(void);
int				ft_bad_size(void);
int				ft_bad_format_file(void);
int				ft_bad_format_tetriminos(void);
t_tetris		*ft_null_err(void);

/*
**	(libft.c) libft functions
*/

void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_strclr(char *s);
void	ft_putendl(char const *s);
#endif
