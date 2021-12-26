# Chess_C
Szachy w języku C w konsoli
* nie obejmują*
  - Sprawdzenia czy jest pat
  - Sprawdzenia zasady 50 ruchów 
  - Sprawdzenia zasady 3 powtórzeń

1. Ruchy
Ruchy odbywają się przy pomocy dłuższej notacji szachowej przy zachowaniu angielskich oznaczeń figur tzn.
- Aby poruszyć pionkiem należy podać pole na kórym obecnie się znajduje i gdzie ma przejść (np. aby ruszyć pionkiem z e2 na e4 należy wpisać e2 e4)
- Aby poruszyć się figurą należy wpisać odpowiadającą jej literę (wielką dla figur białych, a małą dla figur czarnych) pole na którym obecnie się znajduje i gdzie ma przejść 
(np. aby ruszyć białym hetmanem z d1 na f3 należy wpisać Q d1 f3, analogicznie dla czarnego skoczka z b8 na c6 napiszemy n b8 c6)
- Bicie w przelocie wykonujemy jak zwykły ruch pionkiem
- Krótka roszada jest oznaczona O-O, a długa O-O-O
- Aby awansować pionka po dotarciu na skrajne linie należy wpisać literę odpowiadającej figurze na którą chcemy awansować pionka
- Każdy legalny ruch wykonany w partii jest zapisywany w pliku PrzebiegPartii.txt

2. Komendy 
- Aby poddać partję należy wpisać "ABANDON"
- Aby zremisować partję obaj gracze w dwóch następujących po sobie ruchach muszą wpisać "DRAW" 

3. Wizualizacja 
- ChessBezUnicode.c wyświetlają szachownicę i figury przy pomocy liter i znaków ascii 
- ChessUnicode.c wyświetlają szachownicę i figury przy pomocy znaków unicode 
