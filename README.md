# MyFTP

Un serveur FTP complet codé en C conforme à la RFC 959

Gère la connexion de contrôle sur le port 21, les transferts de données en mode PASV et PORT, l'authentification et les commandes de base (LIST, RETR, STOR, CWD, etc.)

## Build et lancement

```bash
make
./myftp 4242 ./
```
