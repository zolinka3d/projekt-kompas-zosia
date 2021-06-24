WSTĘP : Mieliśmy za zadanie zrobić projekt, który pobiera dane kątowe z pierwszych dwóch kolumn - pitch i roll - z pliku "outputCatapult01". Funckcja odpowiedzialna za pobranie danych :
![11](https://user-images.githubusercontent.com/84075025/123258869-2a329980-d4f4-11eb-99d4-9b9e99980d60.png)


Przedstawić te dane na wykresie w stworzonej przeze nas aplikacji w Win Api w języku programowania cpp. Program pokazuje również kompas. 
![kom](https://user-images.githubusercontent.com/84075025/123258933-3a4a7900-d4f4-11eb-9d76-b6aa3af44257.png)


Pobrane dane zapisuje i podstawia do wzoru matematycznego, który określa położenie wskazówki na kompasie. 
![122968128-7f9f6700-d38b-11eb-9468-ac333ec65049](https://user-images.githubusercontent.com/84075025/123258977-46ced180-d4f4-11eb-8d7a-b0ad579def39.png)


Funckja, która oblicza położenie kątowe wskazówki: 
![122968486-e15fd100-d38b-11eb-8964-2671f4285bf5](https://user-images.githubusercontent.com/84075025/123259091-636b0980-d4f4-11eb-805f-39d531462d6e.png)


Oraz funckja, która rysuje wykres i kompas: 
![122968625-07857100-d38c-11eb-90bb-05a525b70c73](https://user-images.githubusercontent.com/84075025/123259129-6bc34480-d4f4-11eb-8ea2-1e8d12abf0fe.png)


JAK KORZYSTAĆ Z PROGRAMU? Program pozwala na ominięcie pierwszych możliwie błędnych linijek danych kątowych z pliku "outputCatapult01". Zatem musimy wpisać, ile linijek chcemy odrzucić wpisując to w białą przestrzeń oraz nacisnąć przycisk "WYGENERUJ" (jeśli uważamy, że wszystkie linijki są poprawne, możemy jedynie wcisnąć guzik bez wcześniejszego wpisywania liczb). ![122969258-bb86fc00-d38c-11eb-8ab8-2ab68b1e89c8](https://user-images.githubusercontent.com/84075025/123259179-7aa9f700-d4f4-11eb-892a-365fc494a770.png)


Po wciśnięciu przycisku generuje się powoli wykres. W danym czasie jak pokazane są dane na wykresie, takie dane wykorzystuje program do obliczania, w jakim położeniu powinna być wskazówka na kompasie. Jest równiez możliwość skalowania wykresu na bieżąco w osi X i Y. Wystarczy nacisnąć jeden z przycisków "+" bądź "-".
![122969835-68fa0f80-d38d-11eb-8f7f-e243e815cc43](https://user-images.githubusercontent.com/84075025/123259225-8695b900-d4f4-11eb-9c0b-cb4c193cd5b0.png)


NAJWAŻNIESZE CZĘŚCI KODU: Tekst edit jest odpowiedzialny za wczytanie liczb wpisanych przez użytkownika. Po naciśnięciu przycisku "WYGENERUJ" tekst jest przekazywany do zmiennej char "hile".
![122970216-e9b90b80-d38d-11eb-98dc-db3ab4977b3b](https://user-images.githubusercontent.com/84075025/123259256-901f2100-d4f4-11eb-84e2-5d4866401871.png)


W tym momencie program pobiera tekst i przerabia go z "chara" na "inta", by móc odjąć go od pierwszych linijek pobranych z pliku. Również odpalany jest timer zaczynający rysowanie kompasu i wykresów. 
![122970471-461c2b00-d38e-11eb-806d-1779f9161c61](https://user-images.githubusercontent.com/84075025/123259334-a3ca8780-d4f4-11eb-831b-38282eefbc9c.png)


Naszą wisienką na torcie jest funckja, która odpala się po odpaleniu timera. Wczytuje ona funkcje rysowania: 
![image](https://user-images.githubusercontent.com/84075025/123259836-3834ea00-d4f5-11eb-8911-72f4c768cbcd.png)
![image](https://user-images.githubusercontent.com/84075025/123259870-3ff48e80-d4f5-11eb-9ba4-9e4b1df75207.png)


Ważnym elementem jest też druga funckja rysująca. Jej zadaniem jest wymazywanie pierwszego narysowanego wykresu, by móc do woli skalować nowo postałe
![122971016-d9556080-d38e-11eb-9ad7-3f74819a38db](https://user-images.githubusercontent.com/84075025/123259406-b644c100-d4f4-11eb-9a1a-93ec69dda05e.png)
