/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_system.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:55:21 by rojones           #+#    #+#             */
/*   Updated: 2016/09/26 17:00:01 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX_SYSTEM_H
# define EX_SYSTEM_H

# include <libc.h>

typedef struct	s_rule
{
	char	*condition;
	char	*conclusion;
}				t_rule;

int ft_and(int t1, int t2);

int ft_or(int t1, int t2);

int ft_xor(int t1, int t2);

int ft_negate(int t);

#endif
