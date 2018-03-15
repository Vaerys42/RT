/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 10:09:38 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/19 10:39:38 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *nptr)
{
	int		i;
	int		neg;
	int		nbr;

	i = 0;
	nbr = 0;
	neg = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'\
			|| nptr[i] == '\f' || nptr[i] == '\v' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
		neg = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57 && nptr[i] != '\0')
	{
		nbr = nbr * 10;
		nbr = nbr + (nptr[i] - 48);
		i++;
	}
	if (neg == 1)
		return (-nbr);
	return (nbr);
}
