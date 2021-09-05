INC		= /usr/X11/include
INCLIB	= $(INC)/../lib
CC		= gcc
#CFLAGS = -I$(INC) -O3 -I.. -g
#CFLAG	= -Wall -Wextra -Werror
NAME	= fractol
SRC    	= main.c

OBJDIR 			= ./obj
OBJ		= $(addprefix $(OBJDIR)/, $(SRC:%.c=%.o))
#OBJ				= $(SRC:%.c=%.o)

MLX		= minilibx-linux
LIBFT	= libft
INCLUDE	= fractol.h

LFLAGS = -L$(MLX) -lmlx -L$(LIBFT) -lft -L$(INCLIB) -lXext -lX11 -lm

#LIBS 	= -framework OpenGL -framework AppKit

all: $(NAME) run

ifeq ($(UNAME), Linux)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -Lgnl -lgnl -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lbsd -o $(NAME)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJDIR)

else

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

#%.o: %.c
#	$(CC) $(CFLAG) -o $@ -c $<

$(OBJDIR)/%.o: %.c
	@-mkdir -p $(OBJDIR)
	@$(CC) $(CFLAG) -o $@ -c $<

clean:
	@make clean -C $(LIBFT)
	rm -f $(OBJ) *~ core *.core

endif

fclean: clean
	@make fclean -C $(LIBFT)
	rm -f $(NAME)

re: clean all

run:
	./$(NAME)
