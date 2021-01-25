/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:32:58 by ksharee           #+#    #+#             */
/*   Updated: 2021/01/21 14:00:40 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define ERR1 "Error: argument\n"
#define ERR2 "Error: file\n"

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

int check_pos(float x, float y, float id_w, float id_h, float w, float h)
{
	if (x < id_w || x > id_w + w || y < id_h || y > id_h + h)
		return (0);
	else if (x - id_w < 1.0000000 || (id_w + w) - x < 1.0000000 || y - id_h < 1.0000000 || (id_h + h) - y < 1.0000000)
		return (1);
	return (2);
}

int main(int agrc, char **agrv)
{
	FILE *fd;
	char b_c, color, type;
	int b_w, b_h, read, x, y, pos;
	char *str;
	float w, h, id_w, id_h;

	if (agrc != 2)
		return (ft_error(ERR1));
	if (!(fd = fopen(agrv[1], "r")) || fscanf(fd, "%d %d %c\n", &b_w, &b_h, &b_c) != 3 || !(b_w > 0 && b_w <= 300 && b_h > 0 && b_h <= 300) || !(str = (char *)malloc(sizeof(char) * (b_w * b_h))))
		return (ft_error(ERR2));
	memset(str, b_c, b_w * b_h);
	while ((read = fscanf(fd, "%c %f %f %f %f %c\n", &type, &id_w, &id_h, &w, &h, &color)) == 6)
	{
		if (!(w > 0 && h > 0) || !(type == 'r' || type == 'R'))
			break ;
		y = -1;
		while (++y < b_h)
		{
			x = -1;
			while (++x < b_w)
			{
				pos = check_pos((float)x, (float)y, id_w, id_h, w, h);
				if (pos == 1 || (pos == 2 && type == 'R'))
					str[y * b_w + x] = color;
			}
		}
	}
	if (read != -1)
	{
		free(str);
		return (ft_error(ERR2));
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
