/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_for.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:43:40 by rojones           #+#    #+#             */
/*   Updated: 2016/10/14 08:26:03 by arnovan-         ###   ########.fr       */
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

static int	ft_eval_brackets(char *condition, int *solving)
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
	brace = ft_eval_condition(temp, solving);
	temp = ft_strnew(strlen(left) + strlen(right) + 1);
	temp = memcpy(temp, left, strlen(left));
	temp[strlen(left)] = brace + '0';
	temp = strcat(temp, right);
	free(left);
	free(right);
	return (ft_eval_condition(temp, solving));
}

int		ft_eval_condition(char *condition, int *solving)
{
	int 	neg1 = 0;
	int		neg2 = 0;
	int		t1;
	int		t2;
	int		op;
	char	*ncon;

	op = -2;
	if (condition[0] != '!' && condition[1] == '\0')
		op = ((isalpha(condition[0])) ? ft_solve_for(condition[0], solving) : condition[0] - '0');
	else if (condition[0] == '!' && condition[2] == '\0')
	{
		op = ((isalpha(condition[1])) ? ft_solve_for(condition[1], solving) : condition[1] - '0');
		op = ft_negate(op);
	}
	else{
		if (strchr(condition, '(') == NULL)
		{
			neg1 = (condition[0] == '!') ? 1 : 0;
			neg2 = (condition[2 + neg1] == '!')?1 : 0;
			t1 =(isalpha(condition[0 + neg1]))? ft_solve_for(condition[0 + neg1], solving) : condition[0 + neg1] - '0';
			t2 =(isalpha(condition[2 + neg1 + neg2]))? ft_solve_for(condition[2 + neg1 + neg2], solving) : 
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
				op = ft_eval_condition(ncon, solving);
			}
		}
		else
		{
			op = ft_eval_brackets(condition, solving);
		}
	}
	free (condition);
	return op;
}

static int	solving_term(char *condition, int *solving)
{
	int i = 0;

	while (condition[i] != '\0')
	{
		if (isupper(condition[i]) && solving[condition[i] - 'A'] == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_solve_for(char fact, int *solving)
{
	int i = 0;
	int pos;
	int	final = -1;
	int re;

	if (g_short == 0 || (g_facts[fact -'A'] == -1 && g_short == 1))
	{
		solving[fact - 'A'] = 1;
		while (i < g_num_rules)
		{
			if (solving_term(g_rules[i].condition, solving) == 0 && (pos = ft_check_rule(g_rules[i].conclusion, fact)) != -1)
			{
				if (strchr(g_rules[i].conclusion, '|') || strchr(g_rules[i].conclusion, '^'))
				{
					printf("\x1B[31mWarning OR type operand in conclusion, result is undefined\x1B[0m\n");
					re = -2;
				}
				else
				{
					re = ft_eval_condition(strdup(g_rules[i].condition), solving);
					if (pos != 0)
					{
						if (g_rules[i].conclusion[pos - 1] == '!')
							re = ft_negate(re);
					}
				}
				printf("Used rule [ \"%s => %s\" ] to solve %c - Result: %d\n", g_rules[i].condition, g_rules[i].conclusion, fact, re);
				if (final == -1)
					final = re;
				else if (re != final && re != -2 && final != -2)
					printf("\x1B[31mWarning contradicting results for %c - Previous Result: %d, Current Result: %d\x1B[0m\n", fact, final, re);
				else if (re != -2)
					final = re;
			}
			i++;
		}
		solving[fact - 'A'] = 0;
		if (final == -1)
		{
			printf("Solving %c from default value %d\n", fact, g_default[fact - 65]);
			return (g_default[fact - 65]);
		}
		else
		{
			printf("Collective result of %c : %d\n", fact, final);
			g_facts[fact - 'A'] = final;
			return (final);
		}
	}
	else
	{
			printf("\x1B[33mUsing previous result of %c: %d\n\x1B[0m", fact, g_facts[fact - 'A']);
			return (g_facts[fact - 'A']);
	}
}
