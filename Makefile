NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -g3 -Wuninitialized 

FILES = heredoc \
		init \
		io \
		main \
		pipex \
		safe \
		tools \


SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a


INCLUDES_DIR = inc
INCLUDES_FILES = pipex.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -o $@

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c $(INCLUDES)
	@mkdir -p $(OBJS_DIR)
	$(CC)  -o $@ -c $<


clean: cleanlibs
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all

$(LIBFT):
	make -C $(LIBFT_DIR)

cleanlibs:
	make fclean -C $(LIBFT_DIR)

.PHONY: all clean fclean re makelib cleanlib