#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Tictactoe{
	const char *player_x;
	const char *player_y;
	int player_x_score;
	int player_y_score;
	int turn; 
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *buttons[9];
	void (*config_window)(GtkWidget*);
	void (*attacher_buttons)(struct Tictactoe* self);
	void (*buttons_onclick)(GtkWidget*, struct Tictactoe* self);
	void (*check_winner)(struct Tictactoe* self);
	void (*reset)(struct Tictactoe* self);
	void (*congrats_winner)(struct Tictactoe* self, char*);
	void (*detect_tie) (struct Tictactoe* self, const char**);
} Tictactoe;

void config_window(GtkWidget* window);
void attacher_buttons(struct Tictactoe *self);
void buttons_onclick(GtkWidget* button, struct Tictactoe* self);
void check_winner(struct Tictactoe* self);
void reset(struct Tictactoe *self);
void congrats_winner(struct Tictactoe *self, char* winner);
void detect_tie(struct Tictactoe *self, const char** buttons_labels);
