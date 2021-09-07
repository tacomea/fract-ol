INC		= /usr/X11/include
INCLIB	= $(INC)/../lib
CC		= gcc
#CFLAGS = -I$(INC) -O3 -I.. -g
#CFLAG	= -Wall -Wextra -Werror
NAME	= fractol
SRC    	= fractol.c hook.c calculate.c color.c simple_atof.c misc.c

OBJDIR 	= ./obj
OBJ		= $(addprefix $(OBJDIR)/, $(SRC:%.c=%.o))

MLX		= minilibx-linux
LIBFT	= libft
INCLUDE	= fractol.h

LFLAGS = -L$(MLX) -lmlx -L$(LIBFT) -lft -L$(INCLIB) -lXext -lX11 -lm

#LIBS 	= -framework OpenGL -framework AppKit

all: $(NAME) m

ifeq ($(UNAME), Linux)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@make -C $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -Lgnl -lgnl -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lbsd -o $(NAME)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

else

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@make -C $(MLX)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

#%.o: %.c
#	$(CC) $(CFLAG) -o $@ -c $<

$(OBJDIR)/%.o: %.c
	@-mkdir -p $(OBJDIR)
	@$(CC) $(CFLAG) -o $@ -c $<

endif

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)
	@rm -rf $(OBJDIR)

m: $(NAME)
	./$(NAME) M

j: $(NAME)
	./$(NAME) J -0.3 -0.63

b: $(NAME)
	./$(NAME) B

fclean: clean
	@make fclean -C $(LIBFT)
	@make fclean -C $(MLX)
	rm -f $(NAME)

re: clean all

