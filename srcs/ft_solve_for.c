/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_for.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:43:40 by rojones           #+#    #+#             */
/*   Updated: 2016/10/12 17:33:34 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_system.h"

static int	ft_check_rule(char *conclusion, char fact)
{
	int	i = -1;

	while(conclusion[++i] != '\0')
	{
		if (conclusion[i] == fact)
			return (i);
	}
	return (-1);
}

static int	ft_bracket_length(int start, char *condition)
{
	int i;
	int skip;

	i = 1;
	skip = 0;
	while (condition[start + i] != '\0')
	{
		if (condition[start + i] == '(')
			skip++;
		if (condition[start + i] == ')' && skip == 0)
			return (i);
		else if (condition[start + i] == ')')
			skip--;
		i++;
	}
	return (i);
}

static int	ft_eval_brackets(char *condition, int *rules_used, int num_rules_used)
{
	int		st;
	int		end;
	int		brace;
	char	*left;
	char	*right;
	char	*temp;

	st = (long)(strchr(condition, '(')) - (long)(condition);
	end = st + ft_bracket_length(st, condition);
	left = ft_strnew(st);
	right = ft_strnew(strlen(condition) - end);
	temp = ft_strnew(end - st - 1);
	left = memcpy(left, condition, st);
	temp = memcpy(temp, &condition[st + 1], end - st - 1);
	right = memcpy(right, &condition[end + 1], strlen(condition) - end);
	brace = ft_eval_condition(temp, rules_used, num_rules_used);
	temp = ft_strnew(strlen(left) + strlen(right) + 1);
	temp = memcpy(temp, left, strlen(left));
	temp[strlen(left)] = brace + '0';
	temp = strcat(temp, right);
	free(left);
	free(right);
	return (ft_eval_condition(temp, rules_used, num_rules_used));
}

int		ft_eval_condition(char *condition, int *rules_used, int num_rules_used)
{
	int 	neg1 = 0;
	int		neg2 = 0;
	int		t1;
	int		t2;
	int		op;
	char	*ncon;

	op = -2;
	if (condition[1] == '\0')
		return((isalpha(condition[0])) ? ft_solve_for(condition[0], rules_used, num_rules_used) : condition[0] - '0');

	if (strchr(condition, '(') == NULL)
	{
		neg1 = (condition[0] == '!') ? 1 : 0;
		neg2 = (condition[2 + neg1] == '!')?1 : 0;
		t1 =(isalpha(condition[0 + neg1]))? ft_solve_for(condition[0 + neg1], rules_used, num_rules_used) : condition[0 + neg1] - '0';
		t2 =(isalpha(condition[2 + neg1 + neg2]))? ft_solve_for(condition[2 + neg1 + neg2], rules_used, num_rules_used) : 
			condition[2 + neg1 + neg2] - '0';
		if (neg1)
			t1 = ft_negate(t1);
		if (neg2)
			t2 = ft_negate(t2);
		if (t1 == -2 || t2 == -2)
			return (-2);
		switch (condition[1 + neg1]) 
		{
			case '+':
				op = ft_and(t1, t2);
				break;
			case '|':
				op = ft_or(t1, t2);
				break;
			case '^':
					op = ft_xor(t1, t2);
				break;
		}
		if (condition[3 + neg1 + neg2] == '\0')
			return (op);
		else
		{
			ncon = ft_strnew(1 + (strlen(&condition[3 + neg1 + neg2])));
			ncon[0] = '0' + op;
			ncon = strcat(ncon, &condition[3 + neg1 + neg2]);
			op = ft_eval_condition(ncon, rules_used, num_rules_used);
		}
	}
	else
	{
		op = ft_eval_brackets(condition, rules_used, num_rules_used);
	}
	free (condition);

	return op;
}

static int	isused(int *rules_used, int num_rules_used, int check)
{
	int i = 0;

	while (i < num_rules_used)
	{
		if (rules_used[i] == check)
			return (1);
		i++;
	}
	return (0);
}

int	ft_solve_for(char fact, int *rules_used, int num_rules_used)
{
	int i = 0;
	int pos;
	int re;

	while (i < g_num_rules)
	{
		if (isused(rules_used, num_rules_used, i) == 0 && (pos = ft_check_rule(g_rules[i].conclusion, fact)) != -1)
		{
			rules_used[num_rules_used++] = i;
			if (strchr(g_rules[i].conclusion, '|') || strchr(g_rules[i].conclusion, '^')) 
				return (-2);
			re = ft_eval_condition(strdup(g_rules[i].condition), rules_used, num_rules_used);
			if (pos != 0)
			{
				if (g_rules[i].conclusion[pos - 1] == '!')
					re = ft_negate(re);
			}
			g_facts[fact - 'A'] = re;
			return(re);
		}
		i++;
	}
	return (g_facts[fact - 65]);
}
