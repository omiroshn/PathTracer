# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 13:50:42 by pgritsen          #+#    #+#              #
#    Updated: 2018/06/13 12:19:26 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	libft.a

CC			= 	gcc

OS			=	$(shell uname)

ifeq ($(OS), Linux)
	CFLAGS		=	-Wextra -Wall -O3 -g3
else
	CFLAGS		=	-Wextra -Werror -Wall -O3 -flto=thin -g3
endif

SRCS		= 	ft_lstnew.c ft_strcat.c ft_strncpy.c ft_memalloc.c ft_strchr.c		\
				ft_strnequ.c ft_memccpy.c ft_strclr.c ft_strnew.c ft_atoi.c			\
				ft_memchr.c ft_strcmp.c ft_strclen.c ft_bzero.c ft_memcmp.c			\
				ft_strcpy.c ft_strnstr.c ft_isalnum.c ft_memcpy.c ft_strdel.c		\
				ft_strntrim.c ft_isalpha.c ft_memdel.c ft_strdup.c ft_strrchr.c		\
				ft_isascii.c ft_memmove.c ft_strequ.c ft_strrev.c ft_isdigit.c		\
				ft_memset.c ft_striter.c ft_strsplit.c ft_isprint.c ft_putchar.c	\
				ft_striteri.c ft_strsplit_lst.c ft_itoa.c ft_putchar_fd.c			\
				ft_strjoin.c ft_strnjoin.c ft_strstr.c ft_lstadd.c ft_putendl.c		\
				ft_strlcat.c ft_strsub.c ft_lstadd_back.c ft_putendl_fd.c			\
				ft_strlen.c ft_strtrim.c ft_lstdel.c ft_putnbr.c ft_strmap.c		\
				ft_tolower.c ft_lstdelone.c ft_putnbr_fd.c ft_strmapi.c ft_toupper.c\
				ft_lstiter.c ft_putstr.c ft_strncat.c ft_lstmap.c ft_putstr_fd.c	\
				ft_strncmp.c ft_string_push_back.c ft_strshift.c ft_get_next_line.c	\
				ft_printf.c ft_printfh.c ft_pow.c ft_nbrlen.c ft_strnchr.c			\
				ft_puthex.c	ft_hexlen.c ft_putoct.c ft_octlen.c ft_skipdigits.c		\
				ft_exp.c ft_abs.c ft_nbrlen_fp.c ft_putnbr_fp.c ft_putbinary.c		\
				ft_nbrblen.c ft_putnp.c ft_strnplen.c ft_degtorad.c ft_atol_base.c	\
				ft_swap.c ft_dlstnew.c ft_dlstpush.c ft_dlstpush_back.c				\
				ft_dlstdelelem.c ft_dlstsize.c ft_dlstpop.c ft_dlstpop_back.c		\
				ft_dlstclear.c ft_get_fractional.c ft_get_content.c ft_atof.c		\
				ft_memjoin.c ft_dlstindex.c

HDRS		=	ftprintf.h libft.h ftstring.h

OBJFOLDER	= 	obj

OBJECTS 	= 	$(addprefix $(OBJFOLDER)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJFOLDER) $(HDRS) $(OBJECTS) libft.h
	@printf "\033[32m[Creating $(NAME)].......\033[0m"
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJFOLDER):
	@printf "\033[32m[Creating folder $(OBJFOLDER)].......\033[0m"
	@mkdir $(OBJFOLDER)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJECTS): $(OBJFOLDER)/%.o : %.c $(HDRS)
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[32m[DONE]\033[0m\n"

clean:
	@printf "\033[31m[Cleaning $(NAME) object files].......\033[0m"
	@rm -rf $(OBJFOLDER)
	@printf "\033[31m[DONE]\033[0m\n"

fclean: clean
	@printf "\033[31m[Removing $(NAME)].......\033[0m"
	@rm -f $(NAME)
	@printf "\033[31m[DONE]\033[0m\n"

re: fclean all
	@printf "\033[33m[Rebuild].......[END]\033[0m\n"

.NOTPARALLEL: all $(NAME) re
