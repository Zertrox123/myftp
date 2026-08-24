# MyFTP

Serveur de transfert de fichiers asynchrone conforme à la RFC 959 en C.

## Présentation

MyFTP (G-NWP-400) est une implémentation complète d'un serveur FTP supportant les connexions simultanées de multiples clients.

Caractéristiques techniques :
- Gestion de la connexion de contrôle (port 21) et des canaux de données dynamiques (modes `PASV` et `PORT`).
- Support des commandes standard : `USER`, `PASS`, `CWD`, `CDUP`, `QUIT`, `DELE`, `PWD`, `PASV`, `PORT`, `HELP`, `NOOP`, `RETR`, `STOR`, `LIST`.
- Isolation des répertoires et authentification anonyme ou utilisateur.

## Prérequis

- GCC
- Make

## Compilation et Lancement

```bash
# Compiler le serveur
make

# Lancer le serveur : ./myftp <port> <chemin_racine>
./myftp 4242 ./
```
