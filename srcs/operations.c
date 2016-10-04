/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opperations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:16:01 by rojones           #+#    #+#             */
/*   Updated: 2016/10/04 14:01:40 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

int	ft_and(int t1, int t2)
{
	printf("and called with %d+%d",t1,t2);
	puts("");

	if (t1 && t2)
		return (1);
	return (0);
}

int	ft_or(int t1, int t2)
{
	printf("or called with %d+%d",t1,t2);
	puts("");

	if(t1 || t2)
		return (1);
	return (0);
}

int	ft_xor(int t1, int t2)
{
	printf("xor called with %d+%d",t1,t2);
	puts("");

	if ((t1 == 1 && t2 == 0) || (t1 == 0 && t2 == 1))
		return (1);
	return (0);
}

int	ft_negate(int term)
{
	return ((term == 1)? 0 : 1);
}
