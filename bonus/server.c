/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:31:04 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/22 12:49:14 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_receive	g_receive;

static void	ft_handle_usr(int sig, siginfo_t *info, void *context)
{
	static char	message[M_BUFFER_SIZE];
	static int	i;
	static int	bit;

	if (g_receive.client_pid != info->si_pid || i == M_BUFFER_SIZE)
	{
		g_receive.client_pid = info->si_pid;
		i = 0;
		message[i] = 0;
		bit = 7;
	}
	message[i] = message[i] | ((sig - SIGUSR1) << (bit));
	g_receive.acknowledge = SIGUSR1 * (--bit >= 0);
	if (bit >= 0 && (context || !context))
		return ;
	bit = 7;
	if ((i == M_BUFFER_SIZE - 1) || message[i] == 0)
	{
		g_receive.acknowledge = SIGUSR1 + !message[i];
		if (write(1, message, ++i) == -1)
			g_receive.acknowledge = -1;
		return ;
	}
	message[++i] = 0;
	g_receive.acknowledge = SIGUSR1;
}

int	main(void)
{
	struct sigaction	sa_usr;
	int					sig_temp;

	ft_printf("Server PID: %i\n", getpid());
	sa_usr.sa_flags = SA_SIGINFO | SA_RESTART;
	sa_usr.sa_sigaction = &ft_handle_usr;
	if (sigaction(SIGUSR1, &sa_usr, NULL) == -1
		|| sigaction(SIGUSR2, &sa_usr, NULL) == -1)
		return (ft_printf("\nERROR!\nFailed to set up signal handler\n\n"), 1);
	g_receive.client_pid = 0;
	g_receive.acknowledge = 0;
	while (1)
	{
		while (!g_receive.acknowledge)
			;
		if (g_receive.acknowledge == -1)
			return (ft_printf("\nERROR!\nFailed to write to STDOUT!\n\n"), 1);
		sig_temp = g_receive.acknowledge;
		g_receive.acknowledge = 0;
		if (kill(g_receive.client_pid, sig_temp))
			return (ft_printf("\nERROR!\nSignal sending failed!\n\n"), 1);
	}
	return (1);
}
