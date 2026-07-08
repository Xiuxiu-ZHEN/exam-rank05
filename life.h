/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhen <xzhen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 03:20:24 by fbetul            #+#    #+#             */
/*   Updated: 2026/07/08 18:32:01 by xzhen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE
#define LIFE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



typedef struct s_game
{
	int width;
	int height;
	int iterations;
	char alive;
	char dead;//死活
	int i;
	int j;//遍历
	int draw;
	char** board;//画 棋盘//board是一个行指针, 里边的每一行都是char*,是可以用char[]遍历的一维数组
} t_game;//9个参数

int init_game(t_game* game, char** av);
void fill_board(t_game* game);
int play(t_game* game);
void print_board(t_game* game);
void free_board(t_game* game);


#endif