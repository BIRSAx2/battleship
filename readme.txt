
Battaglia navale

Note prima dell'esecuzione:
- I file di log si trovano nella cartella game_logs
- I file che iniziano per cc, sono quelli computer vs computer, mentre quelli che iniziano per pc sono quelli player vs
computer.
- Come richiesto dal progetto abbiamo generato due file di log per i due tipi differenti di partite, rispettivamente:
cc_game_20230116194828.txt e pc_game_20230116195426.txt

Compilazione

Per compilare il progetto eseguire i seguenti comandi

# Creare la cartella build se non esite
mkdir -p build

# Spostarsi nella cartella build

cd build

# Compilare il progetto con cmake
cmake ../

cmake --build .

# Per lanciare l'eseguibile battaglia_navale eseguire
./battaglia_navale


# Per effettuare il replay di un file con visualizzazione a schermo eseguire:
./replay v ../game_logs/cc_game_20230116194828.txt

# Per effettuare il replay di un file con stampa output su file utilizzare:

./replay f ../game_logs/cc_game_20230116194828.txt output.txt


Documentazione

Oltre alla documentazione presente all'interno del codice del progetto. Abbiamo generato un PDF con la documentazione
delle classi principali del progetto e i diagrammi delle interazioni tra le varie classi. Il file si trova in in
docs/docs.pdf
Inoltre è disponibile anche un digramma UML delle classi e si trova in docs/uml.svg.

Note riguardo la progettazione

Il progetto si articola in diverse classe, che possono essere raggruppate come segue:
- Gestione delle navi: Classi Ship, Battleship, Submarine e SupportShip.
= Gestione delle posizioni delle navi e del loro movimento: Classi Board, FiringBoard, GameBoard e Coordinates.
- Gestione del gameplay: Classi Player, Game
= Gestione della funzionalità di replay: Classe GameRecorder
- Gestione dei comandi dell'utente: Classi UserCommand e Game.

Per come abbiamo progettato il programma, avrebbe avuto poco senso rendere la classe Ship virtuale pura e derivarne gli
altri tipi di nave, principalmente perché le navi non hanno alcuna conoscenza del loro contesto.  Quindi azioni come
MoveShip non sarebbero potute essere implementate dentro una derivata di Ship, poiché la classe stessa non ha
conoscenza di quali altre navi sono posizionate nella GameBoard, e nemmeno ha accesso alla GameBoard. Il problema
si poteva aggirare passando come parametro un riferimento a GameBoard, tutta via così facendo non si sta realmente
sfruttando il polimorfismo ricevuto dall'essere una classe astratta. Questo e altri motivi ci hanno portato ad
utilizzare le derivate di Ship semplicemente come strumento per differenziare i vari tipi di navi e rendere la loro
esistenza più esplicita. Qualora avesse senso abbiamo inserite dei metodi statici dentro le derivate per effettuare
azioni strettamente legate al tipo di nave (Es. SupportShip e Submarine).
Invece le funzionalità principali, come la gestione dei colpi ricevuti, sono state implementate direttamente nella
classe Ship.

Come si denota dal codice abbiamo cercato il più possibile di non esporre nè FireBoard nè GameBoard all'utilizzatore
della classe Player, e questo ha portato alla creazione di vari helper method nella classe Player con gli stessi nomi
dei metodi associati presenti in GameBoard/FireBoard. Secondo noi questo è un buon compromesso per garantire un certo
livello di information hiding.

Qualora fossero presenti funzioni di utilità generale e utilizzate in più contesti ma non strettamente legate a nessuna
classe li abbiamo posti in Utility.h.