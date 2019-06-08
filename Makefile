
SRC =		main.cpp\
			SDL_manipulate.cpp\
			CP_manipulate.cpp\
			Game_logic.cpp\
			Game_object.cpp\
			Player_paddle.cpp\
			AI_paddle.cpp\
			Puck.cpp\
			cpMouse.cpp
SRC_DIR =	./src/
OBJ_DIR =	./obj/
OBJ = 		$(addprefix $(OBJ_DIR),$(SRC:.cpp=.o))
INC =		./includes/Air_hockey.hpp\
			./includes/SDL_manipulate.hpp\
			./includes/CP_manipulate.hpp\
			./includes/Game_logic.hpp\
			./includes/Game_object.hpp\
			./includes/Player_paddle.hpp\
			./includes/AI_paddle.hpp\
			./includes/Puck.hpp\
			./includes/cpMouse.hpp
NAME =		air_hockey
CHIPMUNK =	./Chipmunk2D/libchipmunk.a
CFLAG =		 -g
SDL_FLAGS =	-lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc\
			-Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit\
			-Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal
SDL2 =		./SDL2/libSDL2.a
CC =		clang++

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC)
	@$(CC) $(CFLAG) -I./includes -I./SDL2/include/ -I./Chipmunk2D/include/ -c $< -o $@

all:  $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAG) -lpthread $(SDL_FLAGS) -o $(NAME) $(OBJ) $(SDL2) $(CHIPMUNK)
		
$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

exe:
	./$(NAME)

re: $(REMAKE) fclean all

commit:
		make fclean
		git add -A
		git commit -m "$(MSG)"
		git push

vpath %.cpp $(SRC_DIR)