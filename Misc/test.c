#include "../minishell/incs/minishell.h"

typedef struct s_list_test
{
	char c;
	struct s_list_test *next;
}				t_list_test;

void print_lst(t_list_test *lst)
{
	while (lst)
	{
		printf("%c", lst->c);
		lst = lst->next;
	}
}

int main()
{
	t_list_test **test;
	t_list_test *new;
	t_list_test *new2;
	t_list_test *new3;
	t_list_test *new4;

	test = malloc(sizeof(t_list_test *) * 2);
	new = malloc(sizeof(t_list_test));
	new->c = 'c';
	new->next = NULL;
	test[0] = new;
	new2 = malloc(sizeof(t_list_test));
	new2->c = 'd';
	new2->next = NULL;
	test[0]->next = new2;
	test[1] = new2;
	new3 = malloc(sizeof(t_list_test));
	new3->c = 'e';
	new3->next = NULL;
	test[1]->next = new3;
	test[1] = new3;
	new4 = malloc(sizeof(t_list_test));
	new4->c = 'f';
	new4->next = NULL;
	test[1]->next = new4;
	test[1] = new4;
	print_lst(test[0]);
	printf("%c", test[0]->c);
}