/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebudak <ebudak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:13:51 by ebudak            #+#    #+#             */
/*   Updated: 2022/07/01 03:55:38 by ebudak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_itoa(int n)
{
	char	*r;
	int		tmp;
	int		a;

	a = 1;
	tmp = n;
	while (tmp && a++)
		tmp /= 10;
	r = (char *)malloc(sizeof(char) * ((n < 0) + a + (n == 0)));
	if (!r)
		return (NULL);
	r += (n < 0) + a - 1 + (n == 0);
	*r = '\0';
	if (n == 0)
		*(--r) = '0';
	a = (n >= 0) * 2 - 1;
	while (n)
	{
		*(--r) = (n % (10 * a)) * a + '0';
		n /= 10;
	}
	if (a < 0)
		*(--r) = '-';
	return (r);
}

void	signal_detect(int n, int client_pid)
{
	static char	value = 0;
	static int	a = 1;

	if (n == SIGUSR1)
		value = value << 1;
	if (n == SIGUSR2)
		value = (value << 1) | 1;
	if (a % 8 == 0 && a != 0)
	{
		write(1, &value, 1);
		if (value == 0)
			kill(client_pid, SIGUSR1);
		value = 0;
	}
	a++;
}

void	signal_detect1(int sign, siginfo_t *info, void *context)
{
	(void)*context;
	signal_detect(sign, info->si_pid);
}

int	main(void)
{
	struct sigaction	s_sig;
	int					pid;

	pid = getpid();
	write(1, ft_itoa(pid), 5);
	write(1, "\n", 1);
	s_sig.sa_sigaction = signal_detect1;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &s_sig, 0);
	sigaction (SIGUSR2, &s_sig, 0);
	while (1)
		pause();
}
