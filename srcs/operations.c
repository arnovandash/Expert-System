/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opperations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:16:01 by rojones           #+#    #+#             */
/*   Updated: 2016/10/12 15:06:05 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

int	ft_and(int t1, int t2)
{
	printf("Operation: AND called with %d + %d",t1,t2);
	puts("");

	if (t1 && t2)
		return (1);
	return (0);
}

int	ft_or(int t1, int t2)
{
	printf("Operation: OR called with %d + %d",t1,t2);
	puts("");

	if(t1 || t2)
		return (1);
	return (0);
}

int	ft_xor(int t1, int t2)
{
	printf("Operation: XOR called with %d + %d",t1,t2);
	puts("");

	if ((t1 == 1 && t2 == 0) || (t1 == 0 && t2 == 1))
		return (1);
	return (0);
}

int	ft_negate(int term)
{
	printf("Operation: NOT called with %d", term);
	puts("");
	return ((term == 1)? 0 : 1);
}
