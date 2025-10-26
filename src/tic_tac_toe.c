#include "tic_tac_toe.h"


int main() {
	gtk_init(NULL, NULL);
	Tictactoe game = {"❎","⭕", 0, 0, 0, gtk_window_new(GTK_WINDOW_TOPLEVEL), gtk_grid_new(),
	{  gtk_button_new_with_label(""), gtk_button_new_with_label(""),gtk_button_new_with_label(""),
	gtk_button_new_with_label(""),gtk_button_new_with_label(""),gtk_button_new_with_label(""),
	gtk_button_new_with_label(""), gtk_button_new_with_label(""), gtk_button_new_with_label("") },
	config_window, attacher_buttons, buttons_onclick, check_winner, reset, congrats_winner, detect_tie};
	game.config_window(game.window);
	game.attacher_buttons(&game);
	gtk_container_add(GTK_CONTAINER(game.window), game.grid);
	gtk_widget_show_all(game.window);
	gtk_main();
	return 0;
}


// methods
void config_window(GtkWidget* window) {
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	gtk_window_set_title(GTK_WINDOW(window), "Tic-tac-toe");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}
void attacher_buttons(struct Tictactoe *self) {
	int k = 0;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			gtk_grid_attach(GTK_GRID(self->grid), self->buttons[k], j, i, 1, 1);
			g_signal_connect_data(self->buttons[k], "clicked", G_CALLBACK(self->buttons_onclick), self, NULL, 1);
			k++;
		}
	}
	gtk_grid_set_row_homogeneous(GTK_GRID(self->grid), TRUE);
	gtk_grid_set_column_homogeneous(GTK_GRID(self->grid), TRUE);
}
void buttons_onclick(GtkWidget* button, struct Tictactoe* self) {
	bool label_is_empty = strcmp(gtk_button_get_label(GTK_BUTTON(button)), "") == 0 ? true : false;
	char player_turn[28];
	if(label_is_empty) {
		if(self->turn == 0) {
			gtk_button_set_label(GTK_BUTTON(button), self->player_x);
			snprintf(player_turn, sizeof(player_turn), "C'est le tour du joueur %s", self->player_y);
			gtk_window_set_title(GTK_WINDOW(self->window), player_turn);
		}else {
			gtk_button_set_label(GTK_BUTTON(button), self->player_y);
			snprintf(player_turn, sizeof(player_turn), "C'est le tour du joueur %s", self->player_x);
			gtk_window_set_title(GTK_WINDOW(self->window), player_turn);
		} 
		self->turn = self->turn == 0 ? 1 : 0;
		self->check_winner(self);
	}
}
void check_winner(struct Tictactoe* self) {
	const char *buttons_labels[9] = {
		gtk_button_get_label(GTK_BUTTON(self->buttons[0])), gtk_button_get_label(GTK_BUTTON(self->buttons[1])),gtk_button_get_label(GTK_BUTTON(self->buttons[2])),
		gtk_button_get_label(GTK_BUTTON(self->buttons[3])), gtk_button_get_label(GTK_BUTTON(self->buttons[4])), gtk_button_get_label(GTK_BUTTON(self->buttons[5])),
		gtk_button_get_label(GTK_BUTTON(self->buttons[6])),gtk_button_get_label(GTK_BUTTON(self->buttons[7])), gtk_button_get_label(GTK_BUTTON(self->buttons[8]))
	};
	char *winner = (char*)calloc(4, sizeof(char));
	const int wins[8][3] = {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6}
	};
	for(int i = 0; i < 8; i++) {
		if( strcmp(buttons_labels[wins[i][0]], "") != 0 
		&& strcmp(buttons_labels[ wins[i][0] ], buttons_labels[ wins[i][1] ]) == 0
		&& strcmp(buttons_labels[ wins[i][1] ], buttons_labels[ wins[i][2] ] ) == 0 ) {
			self->congrats_winner(self, (char*)buttons_labels[ wins[i][0] ]);
		}
	}
	 
	if(strcmp(winner, "\0\0\0\0") != 0) {
		self->congrats_winner(self, winner);
		sleep(0.7);
		self->reset(self);
	}
	self->detect_tie(self, buttons_labels);
}
void reset(struct Tictactoe *self) {
	for(int i = 0; i < sizeof(self->buttons)/sizeof(self->buttons[0]); i++) {
		gtk_button_set_label(GTK_BUTTON(self->buttons[i]), "");
	}
}
void congrats_winner(struct Tictactoe *self, char* winner) {
	size_t longueur = strlen(winner) + 26;
	char *buffer = (char*)calloc(longueur, sizeof(char));
	sprintf(buffer, "The player %s won 🎉!", winner);
	gtk_window_set_title(GTK_WINDOW(self->window), buffer);
}
void detect_tie(struct Tictactoe *self, const char** buttons_labels) {
	bool is_there_tie = true;
	for (int i = 0; i < 9; i++) {
		if (strcmp(buttons_labels[i], "") == 0) {
			is_there_tie = false;
			break;
		}
	}
	if( is_there_tie ) {
		gtk_window_set_title(GTK_WINDOW(self->window), "It's a tie 😥!");
		sleep(0.7);
		self->reset(self);
	}
}


