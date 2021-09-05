INC		= /usr/X11/include
INCLIB	= $(INC)/../lib
CC		= gcc
#CFLAGS = -I$(INC) -O3 -I.. -g
#CFLAG	= -Wall -Wextra -Werror
NAME	= fractol
SRC    	= main.c draw.c
#OBJDIR = ./obj
#OBJ    = $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))
OBJ		= $(SRC:%.c=%.o)
MLX		= minilibx
LIBFT	= libft
INCLUDE	= fdf.h

LFLAGS = -L$(MLX) -lmlx -L$(LIBFT) -lft -L$(INCLIB) -lXext -lX11 -lm

#LIBS 	= -framework OpenGL -framework AppKit

all: $(NAME) run

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAG) -o $@ -c $<

#$(OBJDIR)/%.o: %.c
#	@-mkdir -p $(OBJDIR)
#	@$(CC) $(CFLAG) $(INCLUDE) -o $@ -c $<

clean:
	rm -f $(OBJ) *~ core *.core
	@rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: clean all

run:
	./$(NAME)
