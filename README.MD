w main tworze 7 watkow wg wytycznych z zadania.
3 dla klienta, 2 dla serwera, 1 dla alokatora pamieci, 1 dla funkcji watchdog.

W funkcji client 3 watki co okreslony czas dodaja wylosowana liczbe do:
	-kontenerow w swoich obiektach
	-kontenera w obiekcie thrHandler (wspolny dla wszystkich watkow)

W funkcji server 2 watki:
	-raportuja swoja dzialalnosc dla watku watchdod - wysyla swoj id procesu
	-oczekuja na losowanie liczby przez klienta
	-oczekuja na przyznanie buforu przez watak alokatora
	-wyswietlaja liczbe na ekran
	-zwalniaja przyznana pamiec
	
W funkcji alloc mem watek przyznaje pamiec dla serwerow - komunikacja poprzez zmienne warunkowe i muteksy
	w obiekcie thrHandler
	
Funkcja watchdog co okreslony czas usuwa ze swojego obiektu id watkow serwera (a serwer dodaje swoje id,
raportujac, ze dziala) Funkcja check sprawdza czy id watku znajduje sie w obiekcie Watcher.

Funkcja sigHand oczekuje na sygnal SIGINT, jesli go otrzyma ustawia zmienna globalna run na false, przez
co pętle w funkcjach się kończą.

Uzylem funkcji sleep zamiast usleep, poniewaz u mnie nie dzialala.