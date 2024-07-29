# C-Chess-Server

Multiplayer chess game displayed using ascii characters

## Description

This is a chess game made in c that is displayed with ascii art. The game communicates over a udp connection between two peers. The game checks if moves are valid for a certain piece but does not have proper checkmate/stalemate checks (because that's too much work). But when a king of another player is taken it will produce a flashing win screen.
This is my second project ever written in c. There are probably bugs and if you find any let me know. I don't plan on adding checkmate/stalemate checks, it just isn't worth it to me.


## How to use
-run either "./main" host or "./main client" depending on if you want to be a client or a host<br />
-if you are a client you need to place the hosts ip addr in "Host IP Addr.txt" <br />
-When a connection is made the board will popup and the client gets to make its move first<br />
-moves are formatted as {letter}{number} and correspond to a piece on the board, e.g: (from: A2 to: A4)<br />
-Use CTRL+C to leave game<br />
