#include "Funkcje.h"

GtkWidget *window, *szachownica, *button;
GtkWidget *win, *szach, *butt;
GtkButton *Plansza[8][8];

int CzyjRuch = 1, enRank = -1, enFile = -1, prevRank = -1, prevFile = -1, wKR = 7, wKF = 4, bKR = 0, bKF = 4;
char kto, selectedPiece = '.';

bool enPas = false, Checked = false, didPass = false, prom = false;

Position cords[8][8];
Position Choice;


//Przypisuje obraz do pola
char *getPiece(char piece)
{
    if(piece == '.')    return NULL;

    char *name = malloc(sizeof(char) * 25);

         if (piece == 'P') sprintf(name,"Pieces//pawnw.svg");
    else if (piece == 'p') sprintf(name,"Pieces//pawnb.svg");
    else if (piece == 'N') sprintf(name,"Pieces//knightw.svg");
    else if (piece == 'n') sprintf(name,"Pieces//knightb.svg");
    else if (piece == 'B') sprintf(name,"Pieces//bishopw.svg");
    else if (piece == 'b') sprintf(name,"Pieces//bishopb.svg");
    else if (piece == 'R') sprintf(name,"Pieces//rookw.svg");
    else if (piece == 'r') sprintf(name,"Pieces//rookb.svg");
    else if (piece == 'Q') sprintf(name,"Pieces//queenw.svg");
    else if (piece == 'q') sprintf(name,"Pieces//queenb.svg");
    else if (piece == 'K') sprintf(name,"Pieces//kingw.svg");
    else if (piece == 'k') sprintf(name,"Pieces//kingb.svg");

    return name;
}
//Daje obraz
void GiveImage(char piece, int x, int y)
{
    char *path = getPiece(piece);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(path, 100, 100, NULL);
    GtkImage *image = (GtkImage *)gtk_image_new_from_pixbuf(pixbuf);
    gtk_button_set_image((GtkButton *)Plansza[x][y], (GtkWidget *)image);

    free(path);
}
//Usunięcie obrazu z pola
void TakeImage(int x, int y)
{
    gtk_button_set_image((GtkButton *)Plansza[x][y], NULL);
}
void placePiece(Position from, Position to)
{
    TakeImage(from.x, from.y);
    CopyBoard2To1();
    GiveImage(Board[to.y][to.x]->Figure, to.x, to.y);
    selectedPiece = '.';
}
void Show_Communicate(char message[])
{
    GtkWidget *dialog;
    dialog=gtk_message_dialog_new (GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"%s",message);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
    gtk_window_close(GTK_WINDOW(window));

    CreateNew();
}
void drawMoves(Position pos, char piece)
{
    if(CzyjRuch%2 == 0) kto = 'W' ;
    else                kto = 'B';
    if(piece == 'P' || piece == 'p')
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                GtkWidget *button = (GtkWidget *)Plansza[j][i];
                if(CanPawn(pos.y, pos.x, i, j, CzyjRuch, enPas, enFile, enRank))
                {
                    Ruch(pos.y, pos.x, i, j);
                    FindAttacked();
                    if((!IsCheck(kto, wKR, wKF, bKR, bKF)))gtk_widget_set_name(button, "Selected");
                    ResetAttacked();
                    CopyBoard1To2();
                }
            }
        }
    }
    if(piece == 'R' || piece == 'r')
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                GtkWidget *button = (GtkWidget *)Plansza[j][i];
                if(CanRook(pos.y, pos.x, i, j, CzyjRuch))
                {
                    Ruch(pos.y, pos.x, i, j);
                    FindAttacked();
                    if((!IsCheck(kto, wKR, wKF, bKR, bKF)))gtk_widget_set_name(button, "Selected");
                    ResetAttacked();
                    CopyBoard1To2();
                }
            }
        }
    }
    if(piece == 'N' || piece == 'n')
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                GtkWidget *button = (GtkWidget *)Plansza[j][i];
                if(CanKnight(pos.y, pos.x, i, j, CzyjRuch))
                {
                    Ruch(pos.y, pos.x, i, j);
                    FindAttacked();
                    if((!IsCheck(kto, wKR, wKF, bKR, bKF)))gtk_widget_set_name(button, "Selected");
                    ResetAttacked();
                    CopyBoard1To2();
                }
            }
        }
    }
    if(piece == 'B' || piece == 'b')
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                GtkWidget *button = (GtkWidget *)Plansza[j][i];
                if(CanBishop(pos.y, pos.x, i, j, CzyjRuch))
                {
                    Ruch(pos.y, pos.x, i, j);
                    FindAttacked();
                    if((!IsCheck(kto, wKR, wKF, bKR, bKF)))gtk_widget_set_name(button, "Selected");
                    ResetAttacked();
                    CopyBoard1To2();
                }
            }
        }
    }
    if(piece == 'Q' || piece == 'q')
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                GtkWidget *button = (GtkWidget *)Plansza[j][i];
                if(CanQueen(pos.y, pos.x, i, j, CzyjRuch))
                {
                    Ruch(pos.y, pos.x, i, j);
                    FindAttacked();
                    if((!IsCheck(kto, wKR, wKF, bKR, bKF)))gtk_widget_set_name(button, "Selected");
                    ResetAttacked();
                    CopyBoard1To2();
                }
            }
        }
    }
    if(piece == 'K' || piece == 'k')
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                GtkWidget *button = (GtkWidget *)Plansza[j][i];
                if(CanKing(pos.y, pos.x, i, j, CzyjRuch, wKR, wKF, bKR, bKF))
                {
                    int trank, tfile;
                    Ruch(pos.y, pos.x, i, j);
                    if(CzyjRuch%2 == 1)
                    {
                        trank = wKR;
                        tfile = wKF;
                        wKR = i;
                        wKF = j;
                    }
                    else
                    {
                        trank = bKR;
                        tfile = bKF;
                        bKR = i;
                        bKF = j;
                    }
                    FindAttacked();
                    if((!IsCheck(kto, wKR, wKF, bKR, bKF)))gtk_widget_set_name(button, "Selected");
                    if(CzyjRuch%2 == 1)
                    {
                        wKR = trank;
                        wKF = tfile;
                    }
                    else
                    {
                        bKR = trank;
                        bKF = tfile;
                    }
                    ResetAttacked();
                    CopyBoard1To2();
                }
            }
        }
    }

}
void ResetDraw()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            GtkWidget *button = (GtkWidget *)Plansza[j][i];
            if ((i + j) % 2 == 1) gtk_widget_set_name(button, "dark");
            else                  gtk_widget_set_name(button, "bright");
        }
    }
}
void setCheck(int x, int y, bool czy)
{
    GtkWidget *button = (GtkWidget *)Plansza[x][y];

    if(czy)
    {
        Checked = true;
        gtk_widget_set_name(button, "Check");
    }
    else
    {
        Checked = false;
        if ((x + y) % 2 == 1) gtk_widget_set_name(button, "dark");
        else                  gtk_widget_set_name(button, "bright");
    }
}
void setSelected(int x, int y, bool czy)
{
    GtkWidget *button = (GtkWidget *)Plansza[x][y];

    if(czy) gtk_widget_set_name(button, "Selected");
    else
    {
            if ((x + y) % 2 == 1) gtk_widget_set_name(button, "dark");
            else                  gtk_widget_set_name(button, "bright");
    }
}
//Ogarnięcie kliknięcia
void handleClick(Position pos)
{
    char piece = Board[pos.y][pos.x]->Figure;

    if((CzyjRuch%2 == 1 && Board[pos.y][pos.x]->Kolor == 'W') || (CzyjRuch%2 == 0 && Board[pos.y][pos.x]->Kolor == 'B')) //sprawdzenie czy gracz kliknął na swoją bierkę
    {
        if(Choice.x != -1 && Choice.y != -1)    //Sprawdza czy coś było wybrane wcześniej
        {
            setSelected(Choice.x, Choice.y, false);
            ResetDraw();
            if(Checked)
            {
                if(CzyjRuch%2 == 1) setCheck(wKF, wKR, true);
                else                setCheck(bKF, bKR, true);
            }
        }
        setSelected(pos.x, pos.y, true);

        if(pos.x == Choice.x && pos.y == Choice.y) //sprawdzenie czy to samo pole
        {
            selectedPiece = '.';
            setSelected(Choice.x, Choice.y, false);
            ResetDraw();
            if(Checked)
            {
                if(CzyjRuch%2 == 1) setCheck(wKF, wKR, true);
                else                setCheck(bKF, bKR, true);
            }
            Choice.x = -1;
            Choice.y = -1;
            return;
        }

        //Przypisanie danych pierwszego kliknięcia
        Choice = pos;
        selectedPiece = piece;

        if(selectedPiece != '.') drawMoves(pos, selectedPiece);
    }


    else if (selectedPiece != '.')  //Jeśli wybrano wcześniej bierkę a teraz pole o innym kolorze
    {
        ResetAttacked();
        bool correctMove = false;
        int t_rank2 = pos.y, t_file2 = pos.x, t_rank1 = Choice.y, t_file1 = Choice.x;

             if((Board[Choice.y][Choice.x]->Figure == 'P' || Board[Choice.y][Choice.x]->Figure == 'p') && CanPawn(Choice.y, Choice.x, pos.y, pos.x, CzyjRuch, enPas, enFile, enRank))
             {
                 Ruch(Choice.y, Choice.x, pos.y, pos.x);
			
                 //Ify to sprawdzenia enPas
                 if(t_rank1-t_rank2 == 2)
                 {
                     enPas = true;
                     didPass = false;
                     enRank = t_rank2+1;
                     enFile = t_file2;
                 }
                 else if(t_rank1-t_rank2 == -2)
                 {
                     enPas = true;
                     didPass = false;
                     enRank = t_rank2-1;
                     enFile = t_file2;
                 }
                 else
                 {
                     enPas = false;
                     if(t_file2 == enFile && t_rank2 == enRank) didPass = true;
                     enRank = -1;
                     enFile = -1;
                 }
                 if(t_rank2 == 0 || t_rank2 == 7) prom = true;
                 FindAttacked();
                 if(CzyjRuch%2 == 0) kto = 'W';
                 else                kto = 'B';
                 if(!IsCheck(kto, wKR, wKF, bKR, bKF))   correctMove = true;
             }
        else if((Board[Choice.y][Choice.x]->Figure == 'R' || Board[Choice.y][Choice.x]->Figure == 'r') && CanRook(Choice.y, Choice.x, pos.y, pos.x, CzyjRuch))
        {
            Ruch(Choice.y, Choice.x, pos.y, pos.x);
            FindAttacked();
            if(CzyjRuch%2 == 0) kto = 'W' ;
            else                kto = 'B';
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
            {
                enPas = false;
                correctMove = true;
            }
        }
        else if((Board[Choice.y][Choice.x]->Figure == 'N' || Board[Choice.y][Choice.x]->Figure == 'n') && CanKnight(Choice.y, Choice.x, pos.y, pos.x, CzyjRuch))
        {
            Ruch(Choice.y, Choice.x, pos.y, pos.x);
            FindAttacked();
            if(CzyjRuch%2 == 0) kto = 'W' ;
            else                kto = 'B';
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
            {
                enPas = false;
                correctMove = true;
            }
        }
        else if((Board[Choice.y][Choice.x]->Figure == 'B' || Board[Choice.y][Choice.x]->Figure == 'b') && CanBishop(Choice.y, Choice.x, pos.y, pos.x, CzyjRuch))
        {
            Ruch(Choice.y, Choice.x, pos.y, pos.x);
            FindAttacked();
            if(CzyjRuch%2 == 0) kto = 'W' ;
            else                kto = 'B';
            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
            {
                enPas = false;
                correctMove = true;
            }
        }
        else if((Board[Choice.y][Choice.x]->Figure == 'Q' || Board[Choice.y][Choice.x]->Figure == 'q') && CanQueen(Choice.y, Choice.x, pos.y, pos.x, CzyjRuch))
        {
            Ruch(Choice.y, Choice.x, pos.y, pos.x);
            FindAttacked();
            if(CzyjRuch%2 == 0) kto = 'W' ;
            else                kto = 'B';
            if((!IsCheck(kto, wKR, wKF, bKR, bKF)))
            {
                enPas = false;
                correctMove = true;
            }
        }
        else if((Board[Choice.y][Choice.x]->Figure == 'K' || Board[Choice.y][Choice.x]->Figure == 'k') && CanKing(Choice.y, Choice.x, pos.y, pos.x, CzyjRuch, wKR, wKF, bKR, bKF))
        {
            bool cas = (false);
            //Roszady
            if((CzyjRuch%2 == 1))
            {
                if(t_rank1 == t_rank2 && t_rank1 == 7)
                {
                         if((t_file1 = 4 && t_file2 == 6 && ShortW(wKR, wKF, bKR, bKF)))
                         {
                                DoShortW(wKF);
                                cas = (true);
                         }
                    else if((t_file1 = 4 && t_file2 == 2 && LongW(wKR, wKF, bKR, bKF)))
                    {
                        DoLongW(wKF);
                        cas = (true);
                    }
                }
            }
            else
            {
                 if(t_rank1 == t_rank2 && t_rank1 == 0)
                 {
                         if((t_file1 = 4 && t_file2 == 6 && ShortB(wKR, wKF, bKR, bKF)))
                         {
                            DoShortB(bKF);
                            cas = true;
                         }
                    else if((t_file1 = 4 && t_file2 == 2 && LongB(wKR, wKF, bKR, bKF)))
                    {

                        DoLongB(bKF);
                        cas = true;
                    }
                 }
            }
            ///Po roszadzie


            if(!cas)
                Ruch(Choice.y, Choice.x, pos.y, pos.x);

            FindAttacked();
            if(CzyjRuch%2 == 0)
            {
                kto = 'W' ;
                prevRank = bKR;
                prevFile = bKF;

                bKR = pos.y;
                bKF = pos.x;
            }
            else
            {
                kto = 'B';

                prevRank = wKR;
                prevFile = wKF;

                wKR = pos.y;
                wKF = pos.x;
            }

            if(!IsCheck(kto, wKR, wKF, bKR, bKF))
            {
                enPas = false;
                correctMove = true;
            }
            else
            {
                 if(CzyjRuch%2 == 0)
                {
                    bKR = prevRank;
                    bKF = prevFile;
                }
                else
                {
                    wKR = prevRank;
                    wKF = prevFile;
                }
            }
        }


        if (!correctMove)
        {

            CopyBoard1To2();
            setSelected(Choice.x, Choice.y, false);
            ResetDraw();
            if(Checked)
            {
                if(CzyjRuch%2 == 1) setCheck(wKF, wKR, true);
                else                setCheck(bKF, bKR, true);
            }
            selectedPiece = '.';
            return;
        }

        //Wykonianie ruchu
        if(didPass)
        {
            Position temp;
            if(CzyjRuch%2 == 1)
            {
                temp.x = pos.x;
                temp.y = pos.y+1;
            }
            else
            {
                temp.x = pos.x;
                temp.y = pos.y-1;
            }
            
            placePiece(Choice, temp);  //Sprawia że znika                  
            Ruch(Choice.x, Choice.y, temp.y, temp.x);
            placePiece(temp, pos);   //sprawia że zsię pojawia
            Ruch(temp.x, temp.y, pos.x, pos.y);
            
            Square *P1 = malloc(sizeof(Square));
            P1->Figure = '.';
            P1->IsFree = true;
            P1->IsFirst = true;
            P1->Kolor = 'N';
            Board[temp.y][temp.x] = P1;
            Board2[temp.y][temp.x] = P1;
        }
        else
            placePiece(Choice, pos);

        if(prom)
        {
            ResetAttacked();
            //Promocja(t_rank2, t_file2, CzyjRuch);
            OknoPromocji(CzyjRuch, t_rank2, t_file2);
            //printf("%c\n", Board[t_rank2][t_file2]->Figure);
            FindAttacked();
        }
            //OknoPromocji(CzyjRuch, t_rank2, t_file2);

        setSelected(Choice.x, Choice.y, false);
        ResetDraw();
        if(CzyjRuch%2==1)
        {
            if(prevFile == -1)
                setCheck(wKF, wKR, false);
            else
                setCheck(prevFile, prevRank, false);
        }
        else
        {
            if(prevFile == -1)
                setCheck(bKF, bKR, false);
            else
                setCheck(prevFile, prevRank, false);
        }




        CzyjRuch++;
        prevFile = -1;
        prevRank = -1;
        didPass = false;
        prom = false;
        selectedPiece = '.';


        if(CzyjRuch%2 == 0) kto = 'W' ;
        else                kto = 'B';
        if((IsCheck(kto, wKR, wKF, bKR, bKF)))
        {
            if(CzyjRuch%2==1) setCheck(wKF, wKR, true);
            else              setCheck(bKF, bKR, true);

            if(CheckMate(kto, prevRank, prevFile, wKR, wKF, bKR, bKF, enRank, enFile, CzyjRuch, enPas))
            {
                    if(CzyjRuch%2 == 0) Show_Communicate("Szach mat! Wygrał Biały");
                    else Show_Communicate("Szach mat! Wygrał Czarny");
            }
        }
    }
}
//Sprawdzenie kliknięcia
void button_clicked(GtkWidget *widget, gpointer data)
{
    Position *a = (Position *)data;
    handleClick(*a);
}


void button_clicked1(GtkWidget *widget, gpointer data)
{
    ResetDraw();
    Extra *a = (Extra *)data;
    Promocja(*a, CzyjRuch);

    g_signal_connect (win, "destroy"     , G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (win, "delete-event", G_CALLBACK (gtk_main_quit), NULL);
    gtk_window_close(GTK_WINDOW(win));
}
void OknoPromocji(int CzyjRuch, int t_rank2, int t_file2)
{
        GtkButton *Pola[5];
        Extra where[5];

        win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(win), 420, 105);

        gtk_window_set_title((GtkWindow *)win, "Promocja");
        gtk_window_set_default_size(GTK_WINDOW(win), 420, 105);
        gtk_window_set_position (GTK_WINDOW(win), GTK_WIN_POS_CENTER);
        gtk_window_set_resizable((GtkWindow *)win, FALSE);

        szach = gtk_grid_new();

        for(int i = 0; i < 4; i++)
        {
            butt = gtk_button_new();
            gtk_widget_set_size_request(butt, 122, 122);
            gtk_widget_set_name(butt, "dark");

            where[i].f = t_file2;
            where[i].r = t_rank2;
            where[i].x = 0;
            where[i].y = i;

            g_signal_connect(butt, "clicked", G_CALLBACK(button_clicked1), &where[i]);

            Pola[i] = (GtkButton *)butt;
            gtk_grid_attach((GtkGrid *)szach, butt, i, 0, 1, 1);
        }


        for(int i = 0; i < 4; i++)
        {
            char *name = malloc(sizeof(char) * 25);

            if(CzyjRuch%2 == 1)
            {
                if(i == 0) sprintf(name,"Pieces//rookw.svg");
                if(i == 1) sprintf(name,"Pieces//knightw.svg");
                if(i == 2) sprintf(name,"Pieces//bishopw.svg");
                if(i == 3) sprintf(name,"Pieces//queenw.svg");
            }
            else
            {
                if(i == 0) sprintf(name,"Pieces//rookb.svg");
                if(i == 1) sprintf(name,"Pieces//knightb.svg");
                if(i == 2) sprintf(name,"Pieces//bishopb.svg");
                if(i == 3) sprintf(name,"Pieces//queenb.svg");
            }

            GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(name, 100, 100, NULL);
            GtkImage *image = (GtkImage *)gtk_image_new_from_pixbuf(pixbuf);
            gtk_button_set_image((GtkButton *)Pola[i], (GtkWidget *)image);

            free(name);
        }

    gtk_container_add(GTK_CONTAINER(win), szach);
    gtk_widget_show_all(win);

    gtk_main();

}

//Tworzy pola o danych kolorach
void MakeBoard()
{
    szachownica = gtk_grid_new();

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            button = gtk_button_new();
            gtk_widget_set_size_request(button, 122, 122);

            if ((i + j) % 2 == 1) gtk_widget_set_name(button, "dark");
            else                  gtk_widget_set_name(button, "bright");


            cords[j][i].x = j;
            cords[j][i].y = i;

            g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), &cords[j][i]);

            Plansza[j][i] = (GtkButton *)button;
            gtk_grid_attach((GtkGrid *)szachownica, button, j, i, 1, 1);
        }
    }
}
//Ustawia bierki
void MakePieces()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            GiveImage(Board[j][i]->Figure, i, j);
        }
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 6; j < 8; j++)
        {
            GiveImage(Board[j][i]->Figure, i, j);
        }
    }
}
//Ustawia planszę
void StartGame()
{
    MakeBoard();
    MakePieces();

    gtk_container_add(GTK_CONTAINER(window), szachownica);
    gtk_widget_show_all(window);
}
//Obsługa CSS na kolorowanie pól
void myCSS(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "myCSS.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

void CreateNew()
{

    selectedPiece = '.';
    CzyjRuch = 1, enRank = -1, enFile = -1, prevRank = -1, prevFile = -1, wKR = 7, wKF = 4, bKR = 0, bKF = 4;
    enPas = false, Checked = false, didPass = false, prom = false;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 840, 840);

    gtk_window_set_title((GtkWindow *)window, "Chess");
    gtk_window_set_default_size(GTK_WINDOW(window), 840, 840);
    gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable((GtkWindow *)window, FALSE);

    SetBoard();
    ResetAttacked();

    StartGame();

    g_signal_connect (window, "destroy"     , G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (window, "delete-event", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main();
}


//Głowna funkcja
//Bicie w przelocie nie usuwa pionka z pionka w tablicy board

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    myCSS();

    CreateNew();
    return 0;
}
