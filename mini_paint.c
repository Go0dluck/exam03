/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:12:12 by ksharee           #+#    #+#             */
/*   Updated: 2021/01/21 15:02:31 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ERR1 "Error : arg\n"
#define ERR2 "Error\n"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int check_pos(float x, float y, float w, float h, float r)
{
	float dist;

	dist = sqrtf(pow(x - w, 2.) + pow(y - h, 2.));
	if (dist <= r)
	{
		if ((r - dist) < 1.0000000)
			return (0);
		return (1);
	}
	return (2);
}

int main(int agrc, char **agrv)
{
	FILE *fd;
	char b_c, color, type;
	int b_w, b_h, read, pos, x, y;
	char *str;
	float w, h, r;

	if (agrc != 2)
		return (ft_error(ERR1));
	if (!(fd = fopen(agrv[1], "r")) || fscanf(fd, "%d %d %c\n", &b_w, &b_h, &b_c) != 3 || !(b_w > 0 && b_w <= 300 && b_h > 0 && b_h <= 300) || !(str = (char *)malloc(sizeof(char) * (b_w * b_h))))
		return (ft_error(ERR2));
	memset(str, b_c, b_w * b_h);
	while ((read = fscanf(fd, "%c %f %f %f %c\n", &type, &w, &h, &r, &color)) == 5)
	{
		if (!(r > 0) || !(type == 'c' || type == 'C'))
			break ;
		y = -1;
		while (++y < b_h)
		{
			x = -1;
			while (++x < b_w)
			{
				pos = check_pos((float)x, (float)y, w, h, r);
				if (pos == 0 || (pos == 1 && type == 'C'))
					str[y * b_w + x] = color;
			}
		}
	}
	if (read != -1)
	{
		free(str);
		return(ft_error(ERR2));
	}
	y = -1;
	while (++y < b_h)
	{
		write(1, str + y * b_w, b_w);
		write(1, "\n", 1);
	}
	free(str);
	fclose(fd);
	return (0);
}
