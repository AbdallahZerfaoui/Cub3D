/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 01:45:03 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/10 22:04:22 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>

int	iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	while (iswhitespace(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (str[i] != '\0' && (str[i] <= '9' && str[i] >= '0'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

// int	main(void)
// {
// 	// string to be converted
// 	char strToConvert[] = "-932as";

// 	// converting string using atoi()
// 	int ConvertedStr = ft_atoi(strToConvert);

// 	// printing the Converted String
// 	printf("String to be Converted: %s\n", strToConvert);
// 	printf("Converted to Integer: %d\n", ConvertedStr);

// 	return (0);
// }