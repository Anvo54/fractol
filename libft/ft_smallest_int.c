/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smallest_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:50:30 by avornane          #+#    #+#             */
/*   Updated: 2020/09/28 16:57:37 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int 	ft_smallest_int(int *t, int size)
{
	int	smallest;
	int	i;

	i = 0;
	smallest = t[0];
	while (i < size)
	{
		smallest = (t[i] < smallest) ? t[i] : smallest;
		i++;
	}
	return (smallest);
}
