# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2018/06/13 12:19:25 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	RT

CC			=	gcc

OS			=	$(shell uname)

ifeq ($(OS), Linux)
	CFLAGS		=	-Wextra -Wall -O3 -g3
else
	CFLAGS		=	-Wextra -Werror -Wall -O2 -flto=thin -g3
endif

HDRSDIR		=	./includes

HDRS		=	$(addprefix $(HDRSDIR)/, rt.h structures.h)

SRCSDIR		=	./sources

SRCS		=	main.c events.c stats.c utils_1.c utils_2.c render.c opencl.c	\
				sys_handler.c movement.c vec.c scene_1.c scene_2.c scene_3.c	\
				obj_info.c utils_3.c obj_parser_1.c obj_parser_2.c save.c		\
				obj_parser_3.c obj_parser_4.c async_read.c add_figure_1.c		\
				add_figure_2.c add_figure_3.c

SRCS		+= $(addprefix design/, design_1.c design_2.c design_3.c design_4.c	\
									design_5.c design_6.c design_7.c design_8.c	\
									design_9.c design_10.c design_11.c			\
									design_12.c design_13.c design_14.c			\
									design_15.c design_16.c design_17.c			\
									design_18.c design_19.c design_20.c)

OBJDIR		=	./obj

DIRS		=	./obj ./obj/design

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFOLDER	=	./libraries

LIBSDEPS	=	$(addprefix $(LIBFOLDER)/, libft/libft.a sgl/libsgl.a)

INCLUDES	=	-I./includes
INCLUDES	+=	$(addprefix -I$(LIBFOLDER)/, libft sgl)

ifeq ($(OS), Linux)
	FRAMEWORKS	=	`sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer
					-lSDL2_ttf -lm -lOpenCL
else
	INCLUDES	+=	-I./frameworks/SDL2.framework/Headers
	INCLUDES	+=	-I./frameworks/SDL2_ttf.framework/Headers
	INCLUDES	+=	-I./frameworks/SDL2_image.framework/Headers
	INCLUDES	+=	-F./frameworks

	FRAMEWDIR	=	frameworks

	FRAMEWORKS	=	$(addprefix -F./, $(FRAMEWDIR))
	FRAMEWORKS	+=	$(addprefix -rpath @executable_path/, $(FRAMEWDIR))
	FRAMEWORKS	+=	-framework OpenGL -framework AppKit -framework OpenCl		\
					-framework SDL2 -framework SDL2_ttf -framework SDL2_image
endif

LIBRARIES	=	$(addprefix -L$(LIBFOLDER)/, libft sgl) -lft -lsgl

all: lib $(NAME)

$(NAME): $(DIRS) $(OBJ) $(HDRS) $(LIBSDEPS)
	@printf "\n\033[32m[Creating $(NAME)].......\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBRARIES) $(FRAMEWORKS)
	@printf "\033[32m[DONE]\033[0m\n"

$(DIRS):
	@printf "\n\033[32m[Creating folder $@].......\033[0m"
	@mkdir $@
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : $(SRCSDIR)/%.c $(HDRS)
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "\033[32m[DONE]\033[0m\n"

$(LIBSDEPS): lib

lib:
	@printf "\033[33m[Creating libft.a].......[START]\033[0m\n"
	@make -j3 -C $(LIBFOLDER)/libft
	@printf "\033[33m[Creating libft.a].......[END]\033[0m\n\n"
	@printf "\033[33m[Creating libsgl.a].......[START]\033[0m\n"
	@make -j3 -C $(LIBFOLDER)/sgl
	@printf "\033[33m[Creating libsgl.a].......[END]\033[0m\n"

clean:
	@printf "\n\033[31m[Cleaning $(NAME) object files].......\033[0m"
	@rm -rf $(OBJDIR)
	@printf "\033[31m[DONE]\033[0m\n"

clean_%:
	@make -j3 -C $(LIBFOLDER)/$(subst clean_,,$@) clean

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[31m[Removing $(NAME)].......[DONE]\033[0m\n"

fclean_%:
	@make -j3 -C $(LIBFOLDER)/$(subst fclean_,,$@) fclean

fclean_all:
	@make -j3 -C $(LIBFOLDER)/libft fclean
	@make -j3 -C $(LIBFOLDER)/sgl fclean
	@make fclean

rebuild_message:
	@printf "\033[33m[Rebuild $(NAME)].......[START]\033[0m\n"

re:	rebuild_message fclean all
	@printf "\033[33m[Rebuild $(NAME)].......[END]\033[0m\n"

re_all:	rebuild_message
	@make -j3 -C $(LIBFOLDER)/libft re
	@make -j3 -C $(LIBFOLDER)/sgl re
	@make fclean
	@make all
	@printf "\033[33m[Rebuild $(NAME)].......[END]\033[0m\n"

re_%:
	@make -j3 -C $(LIBFOLDER)/$(subst re_,,$@) re

.NOTPARALLEL: all $(NAME) re
