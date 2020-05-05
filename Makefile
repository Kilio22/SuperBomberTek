##
## EPITECH PROJECT, 2018
## Fairefichier
## File description:
## This is a fairefichier, made by HeyShafty
##

NAME	=	build
ROOT_PATH	=	./
SRC_NAME	=	src
TESTS_NAME	=	tests
INCL_NAME	=	include
SRC_PATH	=	$(ROOT_PATH)$(SRC_NAME)
INCL_PATH	=	$(ROOT_PATH)$(INCL_NAME)
TESTS_PATH	=	$(ROOT_PATH)$(TESTS_NAME)
COLOR_THEME	=	$(BLUE_C)
DEBUG_THEME	=	$(CYAN_C)
TESTS_THEME	=	$(RED_C)

SRC	=

SRCS	=	$(SRC:%=$(SRC_PATH)/%) $(SRC_PATH)/main.c
OBJ	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I $(INCL_PATH)
LDFLAGS	=
LDLIBS	=
DEBUG_FLAGS	=	-g3 -gdwarf-4

all: message $(NAME)

message:
	@$(LINE_RETURN)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"BUILD"$(DEFAULT)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

clean:
	@make fclean -C $(TESTS_PATH) -s SRC="$(SRC)" COLOR_THEME="$(RED_C)"
	@$(RM) $(OBJ) && \
		$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.* && \
		$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"Valgrind files"$(DEFAULT)

fclean:	clean
	@$(RM) results.html && \
		$(ECHO) $(RED_C)$(DIM_T)"[fclean] "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"results.html"$(DEFAULT)
	@$(RM) $(NAME) && \
		$(ECHO) $(RED_C)$(DIM_T)"[fclean] "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"Binary $(NAME)"$(DEFAULT)

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: COLOR_THEME = $(DEBUG_THEME)
debug: re
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"⚠ DEBUG MODE ACTIVATED ⚠\n"$(DEFAULT)

tests_run:
	@make -C $(TESTS_PATH) re -s \
		SRC="$(SRC)" \
		COLOR_THEME="$(TESTS_THEME)"
	@$(ECHO) $(TESTS_THEME)""
	@gcovr --exclude tests/ --sort-percentage --branches
	@$(ECHO) $(BOLD_T)""
	@gcovr --exclude tests/ --sort-percentage --print-summary
	@$(ECHO) $(DEFAULT)
	@gcovr --exclude tests/ --sort-percentage --html-details --html-title "Unit tests" --html-medium-threshold 40 --html-high-threshold 75 > results.html

%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $< && \
		$(ECHO) $(DIM_T) "cc $(CFLAGS) -c "$<$(COLOR_THEME)" -o "$@ $(DEFAULT) || \
		$(ECHO) "\n"$(MAGEN_C) $(UNDLN_T)$(BOLD_T)"cc $(CFLAGS) -c "$<" -o "$@$(DEFAULT)"\n"

.PHONY: all message clean fclean re debug tests_run

ECHO	=	/bin/echo -e
DEFAULT	=	"\e[0m"
BOLD_T	=	"\e[1m"
DIM_T	=	"\e[2m"
UNDLN_T	=	"\e[4m"
BLACK_C	=	"\e[30m"
RED_C	=	"\e[31m"
GREEN_C	=	"\e[32m"
YELLO_C	=	"\e[33m"
BLUE_C	=	"\e[34m"
MAGEN_C	=	"\e[35m"
CYAN_C	=	"\e[36m"
WHITE_C	=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LIGHT_GREY	=	"\e[37m"
DARK_GREY	=	"\e[90m"
LIGHT_RED	=	"\e[91m"
LIGHT_GREEN	=	"\e[92m"
LIGHT_YELLO	=	"\e[93m"
LIGHT_BLUE	=	"\e[94m"
LIGHT_MAGEN	=	"\e[95m"
LIGHT_CYAN	=	"\e[96m"
LINE_RETURN	=	$(ECHO) ""
