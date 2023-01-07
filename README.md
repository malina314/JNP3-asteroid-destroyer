# Asteroid destroyer

Projekt zaliczeniowy Direct2D z przedmiotu JNP3.

## Sterowanie

Sterowanie odbywa się za pomocą klawiatury. Gracz porusza się za pomocą
strzałek, a strzela za pomocą spacji.

## Opis rozgrywki

Gra polega na zestrzeleniu jak największej liczby asteroid. Za każde
zestrzelenie gracz otrzymuje punkt. Gracz ma 3 życia. Po zderzeniu się
z asteroidą gracz traci jedno życie i wraca na początkową pozycję, otrzymując
nieśmiertelność na 3 sekundy. Po utracie wszystkich żyć gra się kończy.

## Opis wykonania

Gra wyświetla się w trybie pełnoekranowym. W grze zostały zawarte wszystkie
obowiązkowe elementy:

* własne mapy bitowe:
  - tło oraz asteroidy wykonałem w programie GIMP na podstawie tutorialu z
    internetu
  - statek gracza oraz pociski wykonałem w programie GIMP na podstawie
    grafik dostępnych w internecie
  - pociski wykonałem w programie GIMP według własnego pomysłu
* napisy:
  - aktualny wynik i liczba żyć wyświetlane są w lewym górnym rogu
  - napis "GAME OVER" wyświetlany na koniec gry
* gradienty:
  - dwa gradienty liniowe do wypełnienia napisów
  - gradient promienisty do wypełnienia ścieżki eksplozji
* ścieżki:
  - ścieżka eksplozji wyświetlana po zestrzeleniu asteroidy, kształt ścieżki
    opakowałem na podstawie grafiki z internetu
