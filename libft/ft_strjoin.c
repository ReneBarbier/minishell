/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:52:55 by martorre          #+#    #+#             */
/*   Updated: 2024/02/14 19:40:50 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;


	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		str[len1] = s2[i];
		len1++;
	}
	str[len1] = '\0';
	return (str);
}
