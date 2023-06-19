#===========================VARIABLE===============================#
SRCS			:=	minishell.c\
					\
					builtins/cd.c\
					builtins/echo.c\
					builtins/env.c\
					builtins/exit.c\
					builtins/export.c\
					builtins/pwd.c\
					builtins/unset.c\
					\
					exec/builtin.c\
					exec/check_access.c\
					exec/exec.c\
					\
					fds/fds.c\
					fds/fds_utils.c\
					\
					garbage/ft_free.c\
					garbage/ft_malloc.c\
					garbage/ft_gbcalloc.c\
					garbage/ft_gbsplit.c\
					garbage/ft_gbstrdup.c\
					garbage/ft_gbstrjoin.c\
					garbage/ft_gbstrtrim.c\
					garbage/ft_gbsubstr.c\
					garbage/ft_gbtabdup.c\
					garbage/ft_gbtabfree.c\
					garbage/ft_gbtabjoin.c\
					garbage/ft_gbitoa.c\
					\
					list/find_type.c\
					list/lst.c\
					list/lst_char.c\
					list/lst_cmd.c\
					list/lst_word.c\
					list/lst_word_utils.c\
					\
					parsing/expand.c\
					parsing/harmonize_spaces.c\
					parsing/is_error_fct1.c\
					parsing/is_error_fct2.c\
					parsing/pars_in_minish.c\
					parsing/process_quotes.c\
					parsing/redir_is_valid.c\
					parsing/remove_quotes.c\
					parsing/unhandled_char.c\
					\
					print_things/print_1.c\
					\
					redir/redir.c\
					redir/redir_utils.c\
					redir/heredoc.c\
					\
					signal/signal.c\
					signal/signal2.c\
					\
					utils/expand_utils.c\
					utils/export_utils.c\
					utils/ft_sort_str_arr.c\
					utils/ft_tabfree.c\
					utils/reforme_d_tab_cmd.c\
					utils/utils.c\
					utils/heredoc_utils.c\
					utils/minish_utils.c\

SRCS_D			:=	srcs/

OBJS_D			:=	objs/

OBJS			:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD			:=	minishell.h\
					error_msgs.h\
					colors.h\
					structures.h\

HEAD_D			:=	incs/

HEAD_A			:=	$(addprefix $(HEAD_D), $(HEAD))

NAME			:=	minishell

LIB				:=	libft.a

LIB_D			:=	libft/

LIB_H			:=	$(LIB_D)$(HEAD_D)

LIB_A			:=	$(LIB_D)$(LIB)

#=========================FLAG===============================#
CC				:=	cc

RM				:=	rm -rf

CFLAGS			:=	-Wall -Wextra -Werror

RDL				:=	-lreadline

ASAN_F			:=	-g3 #-fsanitize=address

#========================EXEC===============================#
all				:	$(NAME)
				@echo
				@echo -e '\001\033[34m\002.___________..______       __  .__   __.  __       _______. __    __   _______  __       __      \001\033[0m\002'
				@echo -e '\001\033[34m\002|           ||   _  \     |  | |  \ |  | |  |     /       ||  |  |  | |   ____||  |     |  |     \001\033[0m\002'
				@echo -e '\001\033[34m\002`---|  |----`|  |_)  |    |  | |   \|  | |  |    |   (----`|  |__|  | |  |__   |  |     |  |     \001\033[0m\002'
				@echo -e '\001\033[34m\002    |  |     |      /     |  | |  . `  | |  |     \   \    |   __   | |   __|  |  |     |  |     \001\033[0m\002'
				@echo -e '\001\033[34m\002    |  |     |  |\  \----.|  | |  |\   | |  | .----)   |   |  |  |  | |  |____ |  `----.|  `----.\001\033[0m\002'
				@echo -e '\001\033[34m\002    |__|     | _| `._____||__| |__| \__| |__| |_______/    |__|  |__| |_______||_______||_______|\001\033[0m\002'
				@echo -e '\001\033[34m\002                                                                                                 \001\033[0m\002'
				@echo -e '\001\033[1;34m\002                                                               🍦    by nfaust, syluiset & xcharra\001\033[0m\002'
$(NAME)			:	$(OBJS_D) $(OBJS)
				$(CC) $(CFLAGS) $(ASAN_F) -o $(NAME) $(OBJS) $(LIB_A) $(RDL)

$(OBJS)			:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_A) $(LIB_A)
				$(CC) $(CFLAGS) $(ASAN_F) -I$(HEAD_D) -I$(LIB_H) -c $< -o $@

$(OBJS_D)		:
				mkdir -p $(OBJS_D)
				mkdir -p $(OBJS_D)builtins
				mkdir -p $(OBJS_D)exec
				mkdir -p $(OBJS_D)fds
				mkdir -p $(OBJS_D)garbage
				mkdir -p $(OBJS_D)list
				mkdir -p $(OBJS_D)parsing
				mkdir -p $(OBJS_D)print_things
				mkdir -p $(OBJS_D)redir
				mkdir -p $(OBJS_D)signal
				mkdir -p $(OBJS_D)utils

$(LIB_A)		:	FORCE
				make -j -C $(LIB_D)

leaks			:	all
				echo "{" > valgrind_ignore_leaks.txt
				echo "leak readline" >> valgrind_ignore_leaks.txt
				echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
				echo "    ..." >> valgrind_ignore_leaks.txt
				echo "    fun:readline" >> valgrind_ignore_leaks.txt
				echo "}" >> valgrind_ignore_leaks.txt
				echo "{" >> valgrind_ignore_leaks.txt
				echo "    leak add_history" >> valgrind_ignore_leaks.txt
				echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
				echo "    ..." >> valgrind_ignore_leaks.txt
				echo "    fun:add_history" >> valgrind_ignore_leaks.txt
				echo "}" >> valgrind_ignore_leaks.txt
				valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
					--show-leak-kinds=all --track-fds=yes \
					--show-mismatched-frees=yes --read-var-info=yes \
					-s ./${NAME}
					#--log-file=valgrind.txt \

FORCE			:

clean			:
				$(RM) $(OBJS) $(OBJS_D) $(OBJSB_D)
				make clean -C $(LIB_D)

fclean			:	clean
				$(RM) $(NAME) $(BONUS)
				make fclean -C $(LIB_D)

re				:	fclean all

.PHONY			:	all clean fclean re FORCE
