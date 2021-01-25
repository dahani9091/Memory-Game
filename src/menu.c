#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "menu.h"

GtkBuilder* builder;
GtkWidget* username;
GtkWidget* password;
GtkWidget* usernameLogin;
GtkWidget* passwordLogin;

GtkWidget* window;
GtkWidget* window2;
GtkWidget* window3;
GtkWidget* button6;
GtkWidget* button1;
GtkWidget* button2;
GtkWidget* button3;
GtkWidget* button4;
GtkWidget* button5;
GtkWidget* button7;

FILE *fp;


void SIGNUP(GtkButton *button, gpointer data)
{
  
  // gtk_widget_destroy (window);
  gtk_widget_hide (window);
  gtk_widget_show_all(window2);

}


int empty(char *filename, char *mode)
{
	FILE *f = fopen(filename, mode);
	fseek(f, 0L, SEEK_END);
	int vide = (ftell(f) == 0L);
	fclose(f);
	return vide;
}
// a utility function we figured we might need it to factcheck the data

bool exist(login player,char* filename,char* mode)
{

    FILE *f=fopen(filename,mode);
    login u;
	while (1)
	{
		fread(&u, sizeof(u), 1, f);
		if (feof(f))
			break;
		if (strcmp(u.username, player.username) == 0)
			return true;
	}
	fclose(f);
	return false;
}


 void SignUpp(GtkWidget *Widget, gpointer data)// we are going to pass signup user as apointer data in the callback
{
  signup *user=(signup *)malloc(sizeof(signup));
  fp=fopen("user.bin","ab");
  user->score=0;
  strcpy(user->username, gtk_entry_get_text(GTK_ENTRY(username)));
  strcpy(user->password, gtk_entry_get_text(GTK_ENTRY(password)));
  printf("%s\n",user->username);
  printf("%s\n",user->password);
  
  if(fp!=NULL)
  {
    if (empty("user.bin", "ab+") == 1)
	  {
		  fwrite(&user, sizeof(user), 1, fp);
	  }
	  else
	  {
		  login user2;
		  strcpy(user2.username, user->username);
		  strcpy(user2.password, user->password);
		  user2.score = 0;
		  if (exist(user2,"user.bin","ab+") == false)
		  {
			  fwrite(&user, sizeof(user), 1, fp);
			
      }
      fclose(fp);
    }
  }
}


void LOGin(GtkWidget *Widget, gpointer data)//pass login struct ppointer as data and extract from it login
{
  login *userr=(login *)malloc(sizeof(login));
  fp=fopen("user.bin","ab");

  userr->score=0;
  strcpy(userr->username, gtk_entry_get_text(GTK_ENTRY(usernameLogin)));
  strcpy(userr->password, gtk_entry_get_text(GTK_ENTRY(passwordLogin)));
  printf("%s\n",userr->username);
  printf("%s\n",userr->password);
  // fp=fopen("user.bin","wb");
  if(isSigned(*userr))
  {
    printf("he is signed comfirmed");
    fclose(fp);
  }  
  else
  {
    printf("he is not signed in");
    fclose(fp);
  }
}


bool isSigned(login player)
{
	fp = fopen("user.bin", "rb");
	if (!fp)
	{
		printf("Erreur 404 XD\n");
		exit(0);
	}
	else
  {
    player.getAcessToPlay=true;
		return exist(player,"user.bin","rb");
  }
}

void LOGIN(GtkButton *button, gpointer data)
{
    gtk_widget_hide (window);
    gtk_widget_hide (window2);
    gtk_widget_show_all(window3);
}



void menu(void)
{

builder=gtk_builder_new_from_file ("./src/memorygame.glade");

window=GTK_WIDGET(gtk_builder_get_object(builder,"window"));

window2=GTK_WIDGET(gtk_builder_get_object(builder,"window2"));
window3=GTK_WIDGET(gtk_builder_get_object(builder,"window4"));


button1=GTK_WIDGET(gtk_builder_get_object(builder,"Login"));

button2=GTK_WIDGET(gtk_builder_get_object(builder,"Sign Up"));

button3=GTK_WIDGET(gtk_builder_get_object(builder,"Top Players"));

button4=GTK_WIDGET(gtk_builder_get_object(builder,"About Us"));

button5=GTK_WIDGET(gtk_builder_get_object(builder,"signup"));

button6=GTK_WIDGET(gtk_builder_get_object(builder,"LOGIN"));

button7=GTK_WIDGET(gtk_builder_get_object(builder,"GOBACK"));


username=GTK_WIDGET(gtk_builder_get_object(builder,"entryusername"));
password=GTK_WIDGET(gtk_builder_get_object(builder,"entrypassword"));
usernameLogin=GTK_WIDGET(gtk_builder_get_object(builder,"ENTRYUSERNAMELOGIN"));
passwordLogin=GTK_WIDGET(gtk_builder_get_object(builder,"ENTRYPASSWORDPASSWORD"));


g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

g_signal_connect(window2,"destroy",G_CALLBACK(gtk_main_quit),NULL);
g_signal_connect(window3,"destroy",G_CALLBACK(gtk_main_quit),NULL);

gtk_entry_set_visibility (GTK_ENTRY(password),FALSE);
gtk_entry_set_visibility (GTK_ENTRY(passwordLogin),FALSE);
gtk_entry_set_invisible_char (GTK_ENTRY(passwordLogin),G_UNICODE_ENCLOSING_MARK);
gtk_entry_set_invisible_char (GTK_ENTRY(password),G_UNICODE_ENCLOSING_MARK);
g_signal_connect(button2,"clicked",G_CALLBACK(SIGNUP),NULL);
g_signal_connect(button5,"clicked",G_CALLBACK(SignUpp),NULL);
g_signal_connect(button1,"clicked",G_CALLBACK(LOGIN),NULL);
g_signal_connect(button6,"clicked",G_CALLBACK(LOGin),NULL);
g_signal_connect(button7,"clicked",G_CALLBACK(MENU),NULL);

gtk_widget_show_all (window);

}

void MENU(GtkButton *button, gpointer data)
{
    gtk_widget_hide (window2);
    gtk_widget_hide (window3);
    gtk_widget_show_all(window);
}
