#===========================VARIABLE===============================#
SRCS			:=	minishell.c\
					parsing/pars.c\
					builtins/pwd.c\
					builtins/cd.c\
					builtins/echo.c\
					builtins/exit.c\
					parsing/process_quotes.c\
					parsing/expand.c\
					parsing/unhandled_char.c\
					parsing/pars_in_minish.c\
					parsing/harmonize_spaces.c\
					parsing/redir_is_valid.c\
					utils/expand_utils.c\
					utils/utils.c\
					utils/libftgarbage.c\
					utils/ft_dbtab_dup_gb.c\
					utils/free_char_tab.c\
					list/lst.c\
					list/lst_char.c\
					list/lst_word.c\
					list/lst_w_cmd.c\
					list/find_type.c\
					redir/redir.c\
					fds/fds.c\
					garbage/ft_free.c\
					garbage/ft_malloc.c\
					utils/ft_gb_strdup.c\
					utils/ft_gbstrjoin.c\
					exec/builtin.c\
					utils/ft_gbstrtrim.c\
					utils/ft_gbcalloc.c\
					exec/exec.c\


SRCS_D			:=	srcs/

OBJS_D			:=	objs/

OBJS			:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD			:=	minishell.h\
					colors.h

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
				mkdir -p $(OBJS_D)/parsing
				mkdir -p $(OBJS_D)/builtins
				mkdir -p $(OBJS_D)/utils
				mkdir -p $(OBJS_D)/list
				mkdir -p $(OBJS_D)/fds
				mkdir -p $(OBJS_D)/redir
				mkdir -p $(OBJS_D)/garbage
				mkdir -p $(OBJS_D)/exec

$(LIB_A)		:	FORCE
				make -j -C $(LIB_D)

FORCE			:

clean			:
				$(RM) $(OBJS) $(OBJS_D) $(OBJSB_D)
				make clean -C $(LIB_D)

fclean			:	clean
				$(RM) $(NAME) $(BONUS)
				make fclean -C $(LIB_D)

re				:	fclean all

.PHONY			:	all clean fclean re FORCE
