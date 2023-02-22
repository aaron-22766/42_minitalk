/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:31:44 by arabenst          #+#    #+#             */
/*   Updated: 2023/02/22 12:59:10 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_signal(int pid, int bit)
{
	kill(pid, SIGUSR1 + bit);
	usleep(100);
}

static void	ft_send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
		ft_send_signal(pid, (c >> i--) & 1);
}

static void	ft_send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
		ft_send_char(pid, message[i++]);
	ft_send_char(pid, 0);
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
	ft_send_message(server_pid, argv[2]);
	return (0);
}
