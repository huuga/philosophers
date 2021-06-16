/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlacresh <rlacresh@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:29:14 by rlacresh          #+#    #+#             */
/*   Updated: 2021/04/17 20:15:45 by rlacresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ident(int str)
{
	if ((str >= 7 && str <= 13) || str == 32)
		return (1);
	else if (str == 43 || str == 45)
		return (2);
	else if (str >= 48 && str <= 57)
		return (3);
	else
		return (4);
}

static	const char	*signs(const char *str, int *neg)
{
	if (*str == 45)
	{
		*neg = -(*neg);
		str++;
	}
	else
		str++;
	return (str);
}

static	long	numbers(const char *str, int *neg)
{
	long	res;

	res = 0;
	if (*neg > 0)
	{
		while (ident(*str) == 3)
		{
			res = (res * 10) + (*str - 48);
			str++;
			if (res > 2147483647)
				return (3000000000);
		}
	}
	else
	{
		while (ident(*str) == 3)
		{			
			res = (res * 10) - (*str - 48);
			str++;
			if (res < -2147483648)
				return (3000000000);
		}
	}
	return (res);
}

long	ft_atoi(const	char *str)
{
	int		neg;
	long	res;

	res = 0;
	neg = 1;
	while (ident(*str) == 1)
		str++;
	if (ident(*str) == 2)
		str = signs(str, &neg);
	if (ident(*str) == 3)
		res = numbers(str, &neg);
	return (res);
}
