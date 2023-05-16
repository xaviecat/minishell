void	is_quote_alone(t_char_lst *lst)
{
	t_char_lst	*tmp;

	tmp = char_lst_last(lst);
	while (tmp)
	{
		if (tmp->s_quote && tmp->c == '\'' && !tmp->prev->s_quote)
		{
			tmp->s_quote = false;
			tmp->a_quote = true;
			return ;
		}
		else if (tmp->d_quote && tmp->c == '\"' && !tmp->prev->d_quote)
		{
			tmp->d_quote = false;
			tmp->a_quote = true;
			return ;
		}
		else if (tmp->s_quote && tmp->c == '\'')
		{
			while (tmp && tmp->s_quote)
				tmp = tmp->prev;
		}
		else if (tmp->d_quote && tmp->c == '\"')
		{
			while (tmp && tmp->d_quote)
				tmp = tmp->prev;
		}
		else if (tmp->s_quote && tmp->c != '\'')
		{
			while (tmp && tmp->s_quote)
			{
				if (tmp->s_quote && tmp->c == '\'')
				{
					tmp->s_quote = false;
					tmp->a_quote = true;
					return ;
				}
				tmp->s_quote = false;
				tmp = tmp->prev;
			}
			tmp->s_quote = false;
		}
		else if (tmp->d_quote && tmp->c != '\"')
		{
			while (tmp && tmp->d_quote)
			{
				if (tmp->d_quote && tmp->c == '\"')
				{
					tmp->d_quote = false;
					tmp->a_quote = true;
					return ;
				}
				tmp->d_quote = false;
				tmp = tmp->prev;
			}
			tmp->d_quote = false;
		}
		else
			tmp = tmp->prev;
	}
}
