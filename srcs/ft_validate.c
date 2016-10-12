/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 10:25:39 by rojones           #+#    #+#             */
/*   Updated: 2016/10/12 14:45:44 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

static int	ft_validate_str(char *con, int line_no)
{
	printf("\x1B[0mValidating term [%s] on line %d\n", con, line_no);
	int i;
	int	f;
	int	op;
	int	brace;

	i = 0;
	brace = 0;
	op = 0;
	f = 0;

	if (con[0] == '+' || con[0] == '^' || con[0] == '|')
	{
		puts ("\x1B[31mERROR: Illegal start of expression\x1B[0m");
		return (0);
	}
	if (con[0] == '\0')
	{
		puts("\x1B[31mERROR: No term defined\x1B[0m");
		return (0);
	}
	while (con[i] != '\0')
	{
		if (con[i] == '(')
			brace++;
		else if (con[i] == ')')
		{
			if (brace == 0)
			{
				puts("\x1B[31mERROR: Extraneous closing brace\x1B[0m");
				return (0);
			}
			else
				brace--;
		}
		else if (isupper(con[i]))
		{
			if ((op == 1 && f == 0) || (op == 0 && f == 0))
			{
				f = 1;
				op = 0;
			}
			else
			{
				printf("\x1B[31mERROR: Multiple facts not seperated by an opperator %s at index %d\n\x1B[0m",con ,i);
				return (0);
			}
		}
		else if (con[i] == '+' || con[i] == '^' || con[i] == '|')
		{
			if (f == 1 && op == 0)
			{
				f = 0;
				op = 1;
			}
			else
			{
				puts("\x1B[31mERROR: Multiple operators not seperated by a fact\x1B[0m");
				return (0);
			}
		}
		else if (con[i] != '!')
		{
			printf("\x1B[31mERROR: Symbol[%c] not recognised\n\x1B[0m", con[i]);
			return (0);
		}
		i++;
	}
	if (op == 0 && brace == 0)
	{
		puts("\x1B[32mSuccessfully validated\x1B[0m");
		return (1);
	}
	else
	{
		if (op != 0)
			puts("\x1B[31mERROR: ends with an open term add fact after the last operator\x1B[0m");
		if (brace != 0)
			puts("\x1B[31mERROR: Extraneous opening brace\x1B[0m");
		return (0);
	}
}

void	ft_validate_rule(int rulenum, int line_no)
{
	//	printf("validate passed line %s\n",line);
	if (ft_validate_str(g_rules[rulenum].condition, line_no) == 0)
	{
		g_rules[rulenum].condition[0] = '\0';
		g_rules[rulenum].conclusion[0] = '\0';
		//		printf("Error in rule |%s|\n",line);
	}
	else if (ft_validate_str(g_rules[rulenum].conclusion, line_no) == 0)
	{
		g_rules[rulenum].condition[0] = '\0';
		g_rules[rulenum].conclusion[0] = '\0';
		//		printf("Error in rule |%s|\n", line);
	}
}
