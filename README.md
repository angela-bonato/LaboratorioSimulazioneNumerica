# Esercitazioni del corso Laboratorio di Simulazione Numerica
## Bonato Angela 30381A | a.a. 2023-2024 | prof. D. E. Galli 

La repository contiene tutto il codice prodotto durante il corso e lo svolgimento delle esercitazioni chieste in sede d'esame. 

Il lavoro riferito alle esercitazioni affrontate durante il corso è organizzato in cartelle numerate. Ognuna di esse contiene:
 - un file `es.cpp` che è il main del programma scritto in C++, corredato di un `Makefile` per compilarlo ed eseguirlo;
 - una o più librerie con tutte le funzioni e le classi usate nel main, organizzate in sottocartelle nel caso delle esercitazioni svolte con l'ausilio del simulatore di meccanica statistica fornito dal professore;
 - dei file `*.dat` con i risultati ottenuti, eventualmente organizzati in sottocartelle; 
 - un Jupyter Notebook fornito dal professore con la consegna dell'esercitazione;
 - un Jupyter Notebook `Esercitazione.ipynb` con l'esposizione dello svolgimento della consegna.

Tutti i file relativi al generatore di numeri casuali sono raccolti nella cartella `RandomGenerator/`, mentre i file `libGen.h` e `libGen.cpp` contengono alcune funzioni che ho utilizzato nel corso di più esercitazioni.