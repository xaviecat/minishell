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

# OBJSB_D			:=	objs_b/

OBJS			:=	$(SRCS:%.c=$(OBJS_D)%.o)

# OBJS_B			:=	$(SRCS:%.c=$(OBJSB_D)%.o)

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

# BFLAGS			:=	-DBONUS=bonus

ASAN_F			:=	-g3 ##-fsanitize=address

#========================EXEC===============================#
all				:	$(NAME)

# bonus			:	$(BONUS)

$(NAME)			:	$(OBJS_D) $(OBJS) $(HEAD_D)$(HEAD)
				$(CC) $(CFLAGS) $(ASAN_F) -o $(NAME) $(OBJS) $(LIB_A) $(RDL)

$(OBJS)			:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_D)$(HEAD) $(LIB_A)
				$(CC) $(CFLAGS) $(ASAN_F) -I$(HEAD_D) -I$(LIB_H) -c $< -o $@

# $(BONUS)		:	$(OBJSB_D) $(OBJS_B) $(HEAD_D)$(HEAD)
# 				$(CC) $(CFLAGS) $(ASAN_F) $(BFLAGS) -o $(BONUS) $(OBJS_B) $(LIB_A)

# $(OBJS_B)		:	$(OBJSB_D)%.o: $(SRCS_D)%.c $(HEAD_D)$(HEAD) $(LIB_A)
# 				$(CC) $(CFLAGS) $(ASAN_F) $(BFLAGS) -I$(HEAD_D) -I$(LIB_H) -c $< -o $@

$(OBJS_D)		:
				mkdir -p $(OBJS_D)

# $(OBJSB_D)		:
# 				mkdir -p $(OBJSB_D)

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

.PHONY			:	all clean fclean re FORCE #bonus
