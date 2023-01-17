
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

Note riguardo la progettazione



