/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:31:04 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/22 12:56:41 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t	g_pid;

static void	ft_handle_usr(int sig, siginfo_t *info, void *context)
{
	static char	message[M_BUFFER_SIZE];
	static int	i;
	static int	bit;

	if (info->si_pid != g_pid)
	{
		g_pid = info->si_pid;
		i = 0;
		message[i] = 0;
		bit = 7;
	}
	message[i] = message[i] | ((sig - SIGUSR1) << (bit));
	if (--bit >= 0)
		return ;
	bit = 7;
	if ((i == M_BUFFER_SIZE - 1) || message[i] == 0)
	{
		write(1, message, i + 1);
		g_pid = 0;
		return ;
	}
	message[++i] = 0;
	(void)context;
}

int	main(void)
{
	struct sigaction	sa_usr;

	ft_printf("Server PID: %i\n", getpid());
	sa_usr.sa_flags = SA_SIGINFO;
	sa_usr.sa_sigaction = &ft_handle_usr;
	sigaction(SIGUSR1, &sa_usr, NULL);
	sigaction(SIGUSR2, &sa_usr, NULL);
	g_pid = 0;
	while (1)
		pause();
	return (1);
}
