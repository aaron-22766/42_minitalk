/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:31:44 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/22 13:42:39 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_send	g_send;

static void	ft_get_ack(int sig)
{
	g_send.timeout = 0;
	g_send.received = sig;
}

static void	ft_send_message(pid_t server_pid, char *message, int i, int bit)
{
	while (g_send.timeout < TIMEOUT)
	{
		if (g_send.received && (!i || message[i - 1]))
		{
			if (g_send.received == SIGUSR2)
				break ;
			g_send.received = 0;
			i += (bit < 0);
			bit = 7 * (bit < 0) + bit * (bit >= 0);
			if (kill(server_pid, SIGUSR1 + ((message[i] >> bit--) & 1)))
			{
				ft_printf("\nERROR!\nSignal sending failed!\n\n");
				exit(1);
			}
		}
		usleep(1);
		g_send.timeout++;
	}
	if (i && !message[i - 1])
		ft_printf("\nALERT!\nMessage sent but server did not acknowledge!\n\n");
	else if (g_send.received == SIGUSR2)
		ft_printf("\nSent message of %d characters!\n\n", ft_strlen(message));
	else
		return ;
	exit(0);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
		return (ft_printf("\nERROR!\nExpected 2 parameters!\n\n"), 1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 2 || server_pid > 99998)
		return (ft_printf("\nERROR!\nPID out of range! [2, 99998]\n\n"), 1);
	if (kill(server_pid, 0) == -1)
		return (ft_printf("\nERROR!\nNo process for the given PID!\n\n"), 1);
	if (ft_strlen(argv[2]) == 0)
		return (ft_printf("\nALERT!\nEmpty message, nothing to sent!\n\n"), 0);
	signal(SIGUSR1, &ft_get_ack);
	signal(SIGUSR2, &ft_get_ack);
	g_send.timeout = 0;
	g_send.received = 1;
	ft_send_message(server_pid, argv[2], 0, 7);
	ft_printf("\nTIMEOUT!\nServer not responding!\n\n");
	return (1);
}
