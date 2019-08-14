NAME = FdF
WFLAGS = -Wall -Werror -Wextra
SRC = ./src/main.c ./src/draw_line.c ./src/choose_key.c ./src/init_read.c ./src/print.c ./src/transformation.c ./src/gradient.c ./src/draw_smooth_line.c ./src/splitted_pixels.c
OBJ = $(SRC:.c=.o)
INC = -I ./libft/includes -I ./includes
LIBFT = -L ./libft -lft
LIBS = -lmlx -lm -framework OpenGL -framework AppKit

all : make_libft $(NAME)

$(NAME) : $(OBJ)
	gcc $(WFLAGS) $(INC) $(OBJ) -o $(NAME) $(LIBS) $(LIBFT)

make_libft :
	make -C ./libft

%.o : %.c
	gcc -g $(WFLAGS) $(INC) -o $@ -c $<

clean :
	make -C ./libft clean
	rm $(OBJ)

fclean : clean
	make -C ./libft fclean
	rm $(NAME)

re : fclean all
