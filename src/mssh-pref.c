#include "mssh-pref.h"

static void mssh_pref_init(MSSHPref* pref);
static void mssh_pref_class_init(MSSHPrefClass *klass);

G_DEFINE_TYPE(MSSHPref, mssh_pref, GTK_TYPE_WINDOW)

GtkWidget* mssh_pref_new(void)
{
	return g_object_new(MSSH_TYPE_PREF, NULL);
}

static void mssh_pref_close(GtkWidget *widget, gpointer data)
{
	MSSHPref *pref = MSSH_PREF(data);

	gtk_widget_destroy(GTK_WIDGET(pref));
}

static void mssh_pref_init(MSSHPref* pref)
{
	GtkWidget *frame = gtk_vbox_new(FALSE, 5);
	GtkWidget *notebook = gtk_notebook_new();
	GtkWidget *content = gtk_vbox_new(FALSE, 4);

	GtkWidget *font_hbox = gtk_hbox_new(FALSE, 10);
	GtkWidget *font_label = gtk_label_new("Font:");
	GtkWidget *font_select = gtk_font_button_new();

	GtkWidget *colour_table = gtk_table_new(2, 2, FALSE);
	GtkWidget *bg_colour_label = gtk_label_new("Background:");
	GtkWidget *bg_colour_select = gtk_color_button_new();
	GtkWidget *fg_colour_label = gtk_label_new("Forground:");
	GtkWidget *fg_colour_select = gtk_color_button_new();

	GtkWidget *exit_check = gtk_check_button_new_with_label(
		"Enable Ctrl+W quit shortcut");
	GtkWidget *close_check = gtk_check_button_new_with_label(
		"Close ended sessions");

	GtkWidget *timeout_hbox = gtk_hbox_new(FALSE, 10);
	GtkWidget *timeout_label1 = gtk_label_new(
		"Closed ended sessions after");
	GtkObject *timeout_adj = gtk_adjustment_new(3, 0, 100, 1, 10, 0);
	GtkWidget *timeout_select = gtk_spin_button_new(
		GTK_ADJUSTMENT(timeout_adj), 1, 0);
	GtkWidget *timeout_label2 = gtk_label_new("seconds");

	GtkWidget *columns_hbox = gtk_hbox_new(FALSE, 10);
	GtkWidget *columns_label = gtk_label_new("Columns:");
	GtkObject *columns_adj = gtk_adjustment_new(2, 1, 10, 1, 10, 0);
	GtkWidget *columns_select = gtk_spin_button_new(
		GTK_ADJUSTMENT(columns_adj), 1, 0);

	GtkWidget *close_hbox = gtk_hbox_new(FALSE, 0);
	GtkWidget *close_button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);

	gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), FALSE);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), content, NULL);

	gtk_box_pack_start(GTK_BOX(font_hbox), font_label, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(font_hbox), font_select, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(content), font_hbox, FALSE, TRUE, 0);

	gtk_table_attach(GTK_TABLE(colour_table), bg_colour_label,
		0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(colour_table), bg_colour_select,
		1, 2, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(colour_table), fg_colour_label,
		0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(colour_table), fg_colour_select,
		1, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	gtk_box_pack_start(GTK_BOX(content), colour_table, FALSE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(content), exit_check, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(content), close_check, FALSE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(timeout_hbox), timeout_label1, FALSE,
		TRUE, 0);
	gtk_box_pack_start(GTK_BOX(timeout_hbox), timeout_select, FALSE,
		TRUE, 0);
	gtk_box_pack_start(GTK_BOX(timeout_hbox), timeout_label2, FALSE,
		TRUE, 0);
	gtk_box_pack_start(GTK_BOX(content), timeout_hbox, FALSE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(columns_hbox), columns_label, FALSE,
		TRUE, 0);
	gtk_box_pack_start(GTK_BOX(columns_hbox), columns_select, FALSE,
		TRUE, 0);
	gtk_box_pack_start(GTK_BOX(content), columns_hbox, FALSE, TRUE, 0);

	gtk_box_pack_end(GTK_BOX(close_hbox), close_button, FALSE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(frame), notebook, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(frame), close_hbox, FALSE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(pref), frame);

	g_signal_connect(G_OBJECT(close_button), "clicked",
		G_CALLBACK(mssh_pref_close), pref);

	gtk_container_set_border_width(GTK_CONTAINER(content), 6);
	gtk_container_set_border_width(GTK_CONTAINER(pref), 15);
	gtk_window_set_title(GTK_WINDOW(pref), "Preferences");
	gtk_window_set_resizable(GTK_WINDOW(pref), FALSE);
}

static void mssh_pref_class_init(MSSHPrefClass *klass)
{
}
