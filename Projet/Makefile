########################################################################################################################
#                                                       VARIABLE                                                       #
########################################################################################################################
SRCS		:=	\
				minishell.c\
				\
				builtins/cd.c\
				builtins/echo.c\
				builtins/env.c\
				builtins/exit.c\
				builtins/export.c\
				builtins/pwd.c\
				builtins/unset.c\
				\
				exec/execution.c\
				exec/fds_redirection.c\
				exec/fork_management.c\
				exec/get_access.c\
				exec/get_access_utils.c\
				exec/get_cmdtab.c\
				exec/mem_fds_management.c\
				exec/process_management.c\
				\
				fds/fds.c\
				fds/remove_quotes_filename.c\
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
				parsing/harmonize_spaces_utils.c\
				parsing/is_error_fct1.c\
				parsing/is_error_fct2.c\
				parsing/pars_in_minish.c\
				parsing/process_quotes.c\
				parsing/redir_is_valid.c\
				parsing/remove_quotes.c\
				parsing/unhandled_char.c\
				\
				redir/redir.c\
				redir/redir_utils.c\
				redir/heredoc.c\
				\
				signal/signal.c\
				signal/signal2.c\
				\
				utils/count_command.c\
				utils/expand_utils.c\
				utils/export_utils.c\
				utils/ft_atoi_custom.c\
				utils/ft_sort_str_arr.c\
				utils/ft_tabfree.c\
				utils/utils.c\
				utils/heredoc_utils.c\
				utils/export_error_management.c\
				utils/minish_utils.c\
				utils/minishell_routine_and_end.c\
				utils/more_expand_utils.c\
				utils/more_export_utils.c\
				utils/ft_malloc_utils.c\
				utils/unset_utils.c\

HEAD		:=	\
				minishell.h\
				error_msgs.h\
				colors.h\
				structures.h\

SRCS_D		:=	srcs/

HEAD_D		:=	incs/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD_A		:=	$(addprefix $(HEAD_D), $(HEAD))

NAME		:=	minishell

LIB			:=	libft.a

LIB_D		:=	libft/

LIB_H		:=	$(LIB_D)$(HEAD_D)

LIB_A		:=	$(LIB_D)$(LIB)

DEBUG		:=	no

########################################################################################################################
#                                                        FLAGS                                                         #
########################################################################################################################
CC			:=	cc

RM			:=	rm -rf

CFLAGS		:=	-Wall -Wextra -Werror -g3

RDL			:=	-lreadline

########################################################################################################################
#                                                        DEBUG                                                         #
########################################################################################################################

ifeq ($(DEBUG), yes)
ASAN_F 		:=	-fsanitize=address
endif

ENV			:=	env -i

IGN_LEAK	:=	valgrind_ignore_leaks.txt

VALGRIND	:=	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all\
				--track-fds=yes --show-mismatched-frees=yes --read-var-info=yes -s

########################################################################################################################
#                                                        COLORS                                                        #
########################################################################################################################
BLUE		:=	\001\033[34m\002

BOLD		:=	\001\033[1m\002

RESET		:=	\001\033[0m\002

########################################################################################################################
#                                                        RULES                                                         #
########################################################################################################################
all			:	$(NAME) banner

$(NAME)		:	$(OBJS_D) $(OBJS) $(LIB_A)
			$(CC) $(CFLAGS) $(ASAN_F) -o $(NAME) $(OBJS) $(LIB_A) $(RDL)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_A) $(LIB_H)libft.h
			$(CC) $(CFLAGS) $(ASAN_F) -I$(HEAD_D) -I$(LIB_H) -c $< -o $@

$(OBJS_D)	:
			@mkdir -p $(OBJS_D)
			@mkdir -p $(OBJS_D)builtins
			@mkdir -p $(OBJS_D)exec
			@mkdir -p $(OBJS_D)fds
			@mkdir -p $(OBJS_D)garbage
			@mkdir -p $(OBJS_D)list
			@mkdir -p $(OBJS_D)parsing
			@mkdir -p $(OBJS_D)redir
			@mkdir -p $(OBJS_D)signal
			@mkdir -p $(OBJS_D)utils

$(LIB_A)	:	$(LIB_D)
			$(MAKE) -C $(LIB_D)

$(IGN_LEAK)	:
			@echo "{"								> $(IGN_LEAK)
			@echo "	leak readline"					>> $(IGN_LEAK)
			@echo "		Memcheck:Leak"				>> $(IGN_LEAK)
			@echo "		..."						>> $(IGN_LEAK)
			@echo "		fun:readline" 				>> $(IGN_LEAK)
			@echo "}"								>> $(IGN_LEAK)
			@echo "{"								>> $(IGN_LEAK)
			@echo "	leak add_history"				>> $(IGN_LEAK)
			@echo "		Memcheck:Leak"				>> $(IGN_LEAK)
			@echo "		..."						>> $(IGN_LEAK)
			@echo "		fun:add_history"			>> $(IGN_LEAK)
			@echo "}"								>> $(IGN_LEAK)
			@echo "{"								>> $(IGN_LEAK)
			@echo "	leak readline_internal_char"	>> $(IGN_LEAK)
			@echo "		Memcheck:Leak"				>> $(IGN_LEAK)
			@echo "		..."						>> $(IGN_LEAK)
			@echo "		fun:readline_internal_char"	>> $(IGN_LEAK)
			@echo "}"								>> $(IGN_LEAK)

leaks		:	all $(IGN_LEAK)
			$(VALGRIND) ./$(NAME)

env_leaks	:	all $(IGN_LEAK)
			 $(ENV) $(LEAKS) ./$(NAME)

fsan		:
			$(MAKE) re DEBUG=yes

banner		:
			@echo -e '$(BLUE)'
			@echo -e '.___________..______       __  .__   __.  __       _______. __    __   _______  __       __      '
			@echo -e '|           ||   _  \     |  | |  \ |  | |  |     /       ||  |  |  | |   ____||  |     |  |     '
			@echo -e '`---|  |----`|  |_)  |    |  | |   \|  | |  |    |   (----`|  |__|  | |  |__   |  |     |  |     '
			@echo -e '    |  |     |      /     |  | |  . `  | |  |     \   \    |   __   | |   __|  |  |     |  |     '
			@echo -e '    |  |     |  |\  \----.|  | |  |\   | |  | .----)   |   |  |  |  | |  |____ |  `----.|  `----.'
			@echo -e '    |__|     | _| `._____||__| |__| \__| |__| |_______/    |__|  |__| |_______||_______||_______|'
			@echo -e '$(BOLD)'
			@echo -e '                                                              🍦    by nfaust, syluiset & xcharra'
			@echo -e '$(RESET)'

clean		:
			$(RM) $(OBJS) $(OBJS_D) $(OBJSB_D)
			$(MAKE) clean -C $(LIB_D)

fclean		:	clean
			$(RM) $(NAME) $(BONUS)
			$(MAKE) fclean -C $(LIB_D)
			$(RM) $(IGN_LEAK)

re			:	fclean all

.PHONY		:	all leaks env_leaks fsan banner clean fclean re
