# 🌐 ft_irc: Internet Relay Chat Server en C++ 98
Evaluation : 125/100

## 📌 Description
Ce projet est une implémentation simple d'un serveur IRC en C++ 98. Le serveur est capable de gérer plusieurs clients simultanément sans jamais se bloquer.

## 🎯 Fonctionnalités
🔄 Gère de multiples clients simultanément.

🔒 Authentification avec mot de passe.

📜 Soutien pour différentes commandes IRC pour les opérateurs de canal et les utilisateurs réguliers.

🌐 Communication via TCP/IP (v4 ou v6).


## 🚀 Utilisation
Pour exécuter le serveur IRC, utilisez la commande suivante :
```
./ircserv <port> <password>
```
## 📖 Commandes supportées
Commande	Description
PASS    Mot de passe du serveur
NICK    Surnom d'utilisateur
USER    Nom d'utilisateur
JOIN    Rejoins un channel
NAMES   Donne les noms des users du channel
LIST    Liste les channels
PRIVMSG Envoie un message privé à l'utilisateur
NOTICE  Notifie l'utilisateur d'un message
PING    Affiche Pong
OP      Donne les droits d'opérateur à un utilisateur
KICK	  Éjecte un client du canal
PART    Quitte un channel
BOT     Invite le bot dans le channel
FILE    Transfert de fichier

## 🧪 Tests
Utilisez nc pour tester le serveur :
```
nc 127.0.0.1 6667
```
