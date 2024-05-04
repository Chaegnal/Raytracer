##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## compiles program
##

CC		=	g++

SRC		=	main.cpp					\
			src/Camera.cpp				\
			src/Ray.cpp					\
			src/Vector3D.cpp			\
			src/Interval.cpp			\
			src/shapes/Scene.cpp		\
			src/shapes/AShape.cpp		\
			src/shapes/Sphere.cpp		\
			src/shapes/HitRecord.cpp	\
			src/materials/AMaterial.cpp	\
			src/materials/Matte.cpp		\
			src/materials/Dielectric.cpp\
			src/materials/Metal.cpp		\
			src/parsing/Parsing.cpp		\
			src/factory/Factory.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	raytracer

CPPFLAGS	=	-std=c++20 -iquote ./interfaces -iquote ./src -iquote ./src/shapes -iquote ./include -iquote ./src/materials -iquote ./src/factory

LIBS	=	-lsfml-window -lsfml-system -lsfml-graphics -lconfig++

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
