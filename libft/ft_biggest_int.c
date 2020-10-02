/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_biggest_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:50:30 by avornane          #+#    #+#             */
/*   Updated: 2020/09/28 16:57:37 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_biggest_int(int *t, int size)
{
	int	biggest;
	int	i;

	i = 0;
	biggest = t[0];
	while (i < size)
	{
		biggest = (t[i] > biggest) ? t[i] : biggest;
		i++;
	}
	return (biggest);
}
