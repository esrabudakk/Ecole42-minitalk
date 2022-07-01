/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebudak <ebudak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:13:57 by ebudak            #+#    #+#             */
/*   Updated: 2022/06/30 23:20:11 by ebudak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	sum;
	int	sign;
	int	found;

	sum = 0;
	sign = 1;
	found = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' \
	|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && found)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 10 + *str - '0';
		else
			found = 0;
		str++;
	}
	return (sign * sum);
}

void	message(int a)
{
	(void)a;
	write(1, "SUCCESS", 8);
}

int	ft_isalpha(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if ((c[i] >= 97 && c[i] <= 122) || (c[i] >= 65 && c[i] <= 97))
			return (0);
		i++;
	}
	return (1);
}

void	process(int pid, t_argv_str arg_str )
{
	int	bit;
	int	send_bit;
	int	tmp_strlen;

	tmp_strlen = arg_str.strlen;
	while (tmp_strlen--)
	{
		bit = 7;
		while (0 <= bit)
		{
			send_bit = (arg_str.chr >> bit) & 1;
			if (send_bit == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			if (bit == 0)
			{
				arg_str.index++;
				arg_str.chr = arg_str.input[arg_str.index];
			}
			bit--;
		}
		signal(SIGUSR1, message);
	}
}

int	main(int args, char **argv)
{
	t_argv_str	arg_str;
	int			pid;
	int			i;

	i = 0;
	if (args != 3 || !ft_isalpha(argv[1]))
	{
		write(1, "ERROR: SOMETHINGS GET WRONG", 28);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "ERROR: SOMETHINGS GET WRONG", 28);
		return (0);
	}
	arg_str.input = argv[2];
	arg_str.chr = arg_str.input[arg_str.index];
	while (arg_str.input[i] != 0)
		i++;
	arg_str.strlen = i + 1;
	process(pid, arg_str);
}
