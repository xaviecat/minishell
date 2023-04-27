#===========================VARIABLE===============================#
SRCS			:= minishell.c\
					\
					\
					\
					\
					\
					\

SRCS_D			:=	srcs/

OBJS_D			:=	objs/

OBJS			:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD			:=	minishell.h

HEAD_D			:=	incs/

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

ASAN_F			:=	-g3 ##-fsanitize=address

#========================EXEC===============================#
all				:	$(NAME)

$(NAME)			:	$(OBJS_D) $(OBJS) $(HEAD_D)$(HEAD)
				$(CC) $(CFLAGS) $(ASAN_F) -o $(NAME) $(OBJS) $(LIB_A) $(RDL)

$(OBJS)			:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_D)$(HEAD) $(LIB_A)
				$(CC) $(CFLAGS) $(ASAN_F) -I$(HEAD_D) -I$(LIB_H) -c $< -o $@

$(OBJS_D)		:
				mkdir -p $(OBJS_D)

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
