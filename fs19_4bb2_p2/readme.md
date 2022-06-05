# Prüfung
## Threads & Synchronisation
### 1) Beschreiben Sie die Funktionsweise und Mechanismen dieses Programms.
Was simuliert das Programm, wie funktioniert es, und wie heisst das allgemeine Pattern?
```c
#define OVEN_MAX_PIZZAS 3
pthread_mutex_t oven_mutex = PTHREAD_MUTEX_INITIALIZER;
void *baker_start(void *arg) {
    while (1) {
        pthread_mutex_lock(&oven_mutex);
        if (oven_n_pizzas() < OVEN_MAX_PIZZAS) {
            int p = create_pizza();
            oven_insert_pizza(p);
        }
        pthread_mutex_unlock(&oven_mutex);
    }
}

void *waiter_start(void *arg) {
    while (1) {
        pthread_mutex_lock(&oven_mutex);
        if (oven_n_pizzas() > 0) {
            int q = oven_remove_pizza();
            serve_pizza(q);
        }
        pthread_mutex_unlock(&oven_mutex);
    }
}
​// implementations of application specific functions, oven_…, etc.
int main () // calls baker_start, waiter_start in separate Threads
```

Producer & Consumer Pattern.
Es simuliert eine Pizzaofen, die einen "Buffer" vom maximal 3 Pizzen bereitstellt.
Wenn 3 Pizzas im Ofen sind, produziert der Ofen nicht weiter, solang der "Waiter" nicht die Pizzen abholt.

### 2) Thread safe Stack push
Schreiben Sie den folgenden Code um, so dass ​stack_push()​ Thread-safe ist.
Thread-safe heisst hier "ohne Race Conditions" falls mehrere Threads die Funktion aufrufen.

Code als File: [aufgabe2_stackmutex.c](aufgabe2_stackmutex.c)

## IPC mit Pipes
### 3) Schreiben Sie ein Programm, das seine Child Prozesse per Pipe verbindet.
Child Prozess Nr. 2 soll die Nachricht "hi" an Child Prozess Nr. 1 senden, über diese Pipe

Code als File: [aufgabe3_childrenpipe.c](aufgabe3_childrenpipe.c)

### 4) Vergleichen Sie Internet Stream Sockets mit Internet Datagram Sockets.
| Stream Sockets (TCP) | Datagram Sockets (UDP) |
| ------------- | -----|
| Zuverlässige (Bytes kommen an oder es gibt einen Fehler | Unzuverlässig (Übertragung und Reihenfolge ist nicht garaniert, Mehrfachübertragung möglich |
| Verbindungsorientiert (Verbunden mit einem Peer) | Verbindungslos |
| Langsamer | Schneller |
| Fehlererkennung | Fehler werden ignoriert |

### 5) Wenn Sie ​http://fhnw.ch/​ im Browser öffnen, wer ruft ​write​ auf, und wozu?
```c
ssize_t ​ write​(int fd, const void *buf, size_t count); // write to socket
```

Zuerst der Client, um einen Request in den Stream zu schreiben. Kann aber von beiden Seiten initiiert werden.

### 6) Welche Reihenfolge haben die folgenden Calls bei einem UDP Server?
```c
int ​ bind​ (int sock_fd, const struct sockaddr *addr, socklen_t addrlen);
ssize_t ​ recvfrom​ (int fd, void *buf, size_t len, int flags,
struct sockaddr *addr, socklen_t *addr_len);
ssize_t ​ sendto​ (int fd, const void *buf, size_t len, int flags,
const struct sockaddr *dest_addr, socklen_t addrlen);
int ​ socket​ (int domain, int type, int protocol);
```
Eine Antwort ankreuzen:
[*] ​ socket(); bind(); recvfrom(); sendto(); **(Laut Folien auch mehrfach)**

## Terminals
### 7) Welcher Terminal Mode wird für Text-Editoren verwendet, und wieso?
Der Non-Canonical Mode, da zeichenweise gelesen werden kann und Terminal-Zeichen vom Editor selbst
gehandled werden können statt fvon der Shell.

## POSIX IPC
### 8) Ticket-Vendor

Code als File: [aufgabe8_vendors.c](aufgabe8_vendors.c)

Wohl bessere Alternative: [aufgabe8_vendors_alternative.c](aufgabe8_vendors_alternative.c)

## Zeitmessung
### 9) Zeimessung Signal
Schreiben Sie ein Programm, das misst, wie lange (Echtzeit) ein Signal hat.
Die Messung soll beim Senden von ​SIGUSR1​ starten und direkt nach dem Eintreffen stoppen.
```
$ ./my_signal_time
Sending signal ...
... handling done.
real: 67999 10^-9s
```

Code als File: [aufgabe9_signaltimer.c](aufgabe9_signaltimer.c)

### 10) Schreiben Sie ein Programm, das "morgen", 00:00:00 als Datum ausgibt.
Der Output des Programms soll so aussehen, mit dem aktuellen Datum, im Default-Format:
```c
$ ./tomorrow
today is: Sun Jun 2 16:40:44 2019
tomorrow: Mon Jun 3 ​ 00:00:00​2019
```

Code als File: [aufgabe10_tomorrow.c](aufgabe10_tomorrow.c)