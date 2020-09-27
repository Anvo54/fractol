int	ft_biggest_int(int *t, int size)
{
	int biggest;
	int i;

	i = 0;
	biggest = t[0];
	while (i < size)
	{
		biggest = (t[i] > biggest) ? t[i] : biggest;
		i++;
	}
	return(biggest);	
}