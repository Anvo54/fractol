int		ft_smallest_int(int *t, int size)
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
	return(smallest);	
}