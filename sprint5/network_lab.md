# Basic Socket Programming

## Introduction
Let's learn a bit more about C socket programming by starting with a really basic setup: one client connecting to one server.  A very basic client will send a string to the server and the server will echo back the same string with a time stamp added to it.

Take a look at the flow chart we used to discuss client-server interactions via sockets:

![client-server architecture](.guides/img/socket_client_server.png)

In this lab, you'll be using all of these function calls.  Let's get started with the server.

## Server
Save the following code into a file named `server.c`

Starting code:
```
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
  //char *response; 
  char request[100];
  char response[100];
  time_t ticks; 
  
  //turns out socket descriptors are just like file descriptors
  int listen_fd, send_fd;
 
  struct sockaddr_in servaddr;
 
  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
  memset(&servaddr, 0, sizeof(servaddr));
 
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);
  servaddr.sin_port = htons(22000);
 
  bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
  listen(listen_fd, 10);
 
  send_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
 
  while(1) {
    memset(request, 0, sizeof(request));
    memset(response, 0, sizeof(response)); 
    
    //get original request from client
    int numBytes = read(send_fd, request, sizeof(request));
    
    if(numBytes != 0) {  //make sure request had something in it
      //get current timestamp
      ticks = time(NULL);
    
      //string version of timestamp info
      char* ts = ctime(&ticks);
        
      //glue together the original client request, a separator, and the 
      //time stamp info into a single string
      strcpy(response, request);
      strcat(response, " - ");
      strcat(response, ts);
      
      printf("Sending back: %s\n", response);
      
      //write server's response to socket file descriptor
      write(send_fd, response, strlen(response)+1);
    }
  }
  close(send_fd);
  close(listen_fd);
}
```

We have created a server!  It lives!!

Compile the code and make sure you don't have any typos: `gcc -Wall -Werror -o server server.c`

## A Deep Dive
Now let's take a deep dive and see what we actually did.  In the code :

1. The call to the function `socket()` creates an **unnamed** socket inside the kernel and returns an integer known as socket descriptor.  This is basically a file descriptor and can be used the same way.
  * This function takes the family as its first argument. For the Internet family of IPv4 addresses, we use the constant `AF_INET`.
  * The second argument `SOCK_STREAM` specifies that the transport layer protocol that we want should be reliable (ie it should have acknowledgment techniques), 2-way communication. For example: TCP
  * The third argument is generally set to zero to let the kernel decide the default protocol to use for this connection. For connection-oriented reliable connections, the kernel will choose TCP as the default protocol.
  
2. You'll see the function `memset` used a lot throughout both the server and the client.  This function takes 3 arguments: an address in memory, a value to fill memory with, and a length (number of bytes).  It will fill in the specified number of bytes with the specified value starting at the specified address.  Think of it as a way of cleaning out memory before using it.  When buffers get reused repeatedly (as they do for sending and receiving repeatedly in socket programming), it's considered good practice to start with a "clean slate".

3. The call to the function `bind()` assigns the details specified in the structure `servaddr` to the socket created in the step above. The details include: the family, the interface to listen on (in case the system has multiple interfaces to the network) and the port on which the server will wait for the client requests to come.

4. The call to the function `listen()` with second argument as `10` specifies maximum number of client connections that server will queue for this listening socket.

5. After the call to `listen()`, this socket becomes a fully functional listening socket.

6. In the call to `accept()`, the server is blocked (put to sleep) and when an incoming client request (the three way TCP handshake) is complete, the function `accept()` wakes up and returns the socket descriptor representing the client socket.  At this point, we have a file descriptor specifically for this server-client communication link, and all communication should now use that fd.  *Side note: A three way handshake is the procedure that is followed to establish a TCP connection between two remote hosts.*

7. As soon as server gets a request from a client, it prepares the date and time and writes on the client socket through the descriptor returned by `accept()`.

## A Basic Client
Now let's get a basic client.  Save the following code in a file named `client.c`

```
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
 
int main(int argc,char **argv) {
  if(argc != 2) {
    printf("\n Usage: %s <ip of server> \n",argv[0]);
    return 1;
  } 
  
  int socket_fd;
  char question[100];
  char recvline[100];
  struct sockaddr_in servaddr;
 
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  
  memset(&servaddr, 0, sizeof(servaddr));
 
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(22000);
 
  inet_pton(AF_INET, argv[1], &(servaddr.sin_addr));
 
  connect(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
 
  memset(question, 0, sizeof(question));
  memset(recvline, 0, sizeof(recvline));
      
  //prompt the user
  printf("Request: ");

  fgets(question, sizeof(question), stdin); /*stdin = 0 , for standard input */
  question[strcspn(question, "\n")] = 0; //replace newline just for readability
       
  write(socket_fd, question, strlen(question)+1);
  read(socket_fd,recvline,100);
  printf("%s",recvline);

  close(socket_fd);
  return 0;
}
```

Compile the client and make sure there are no typos: 
`gcc -Wall -Werror -o client client.c`

## A Second Deep Dive
We've created a client which will connect to the server and receive its original request plus the server's date/time. Taking a closer look at our client code:

0. We pass the IP address of the server as a command line argument to the client.  We immediately check to make sure the user supplied it before bothering to continue.

1. We see that, just like in `server.c`, a socket is created through call to `socket()` function.

2. Information like IP address of the remote host and its port is bundled up in a structure and a call to the function `connect()` is This function tries to connect this local socket with the socket (IP address and port) of the remote host.

3. Note that here we do not bind our client socket on a particular port as clients generally use a port assigned by kernel.  Thus a client can have its socket associated with any port.  However, the server has to use a well known socket, so known servers bind to a specific port.  For example, most web servers using HTTP run on a specific port (usually 80 for insecure connections and 443 for secure connections) while there are no such restrictions on clients.

5. `inet_pton` converts our IP address from text (specified as a command line argument when we run our program) to the binary form needed to connect.

4. Once the sockets are connected, the client prompts the user for a request.  This request is sent by writing to the file descriptor which specifies the socket. The server receives this request, formats a response (using the original client request and a date/time), and returns it by writing to the client's socket (using the client's socket descriptor).  

5. The client can then read the response through a normal `read` call on the its socket descriptor.


So you see, reading and writing to/from files is very similar to reading/writing from sockets.  The tricky part is getting the sockets set up.  Once you have the socket/file descriptors, you can just use `read` and `write`. 

## Roger That
Now let's hook our client and server up and get them communicating.  Open up **TWO** terminal tabs.  In one, execute the server program:
```
./server
```

Observe that it just sits there (you know this, because you don't see your prompt).  That's because the server is waiting for a client to make a request to it.  Ok, let's do that.

Leave the server running and switch to the other terminal tab you opened.  In that tab, execute the client:
```
$ ./client 127.0.0.1
```
The client will pause after prompting you for a request.  Type anything you want and press enter.

You should see a response with the original request string plus the current date/time, similar to `Mon Apr 22 17:40:43 2019`.  *Huh?* you might be thinking. *That's not the time right now...*. Or you might just be thinking, *I can't wait for this class to end*.  I can never be sure. Remember that the platform we're using (Codio) is hosted elsewhere.  Their machines are in a different time zone!  

No matter what you're thinking, we successfully gotten a response to the client request from the server!

We needed to specify the IP address of the server as a command line argument when we started up the client.  Since we are running both the server and the client on the same (local) machine for testing purpose, we used the **loop back** IP address.  The loop back address is an easy way to tell our code that the server is right here, and we don't need to access the Internet to find it.  *Side note: this is similar to horror movies when the crucial phone call comes from inside the house and everyone realizes that both the victim(s) and murderer(s) are in the same location!*

Useless trivia: 127.0.0.1 is a reserved IP address that always indicates the local machine.  For this reason, is also referred to as "home" and leads to things such as t-shirts which just reinforce the idea that computer scientists are elitist snobs:

![](https://i2.wp.com/www.supergraphictees.com/wp-content/uploads/there-is-no-place-like-home-navy-blue.jpg?fit=932%2C1100&ssl=1)

## The Ultimate Answer to Life and Everything
Ok, this is (somewhat) cool.  We have a server which can accept client requests and respond with a date/time.  But a date/time isn't really that interesting.  Let's kick it up a notch and make a [Magic 8-Ball](https://en.wikipedia.org/wiki/Magic_8-Ball) server.  When a client asks a question, the server will respond with one of twenty canned responses.

So let's make some modifications to the server.

It's always a good idea to structure code for reuse.  We'll write a function which returns a single, randomly generated, Magic 8-Ball response.  Add this function as the first function (before `main`) in `server.c`.

```
//selects a random response and writes it into
//the buffer supplied as an argument
void getFortune(char buff[]) {
  //could alter this to add more responses!

  char *responses[] = {
    //positive response
    "It is certain.\n", 
    "It is decidedly so.\n", 
    "Without a doubt.\n",
    "Yes, definitely.\n", 
    "You may rely on it.\n", 
    "As I see it, yes.\n",
    "Most likely.\n", 
    "Outlook good.\n", 
    "Signs point to yes.\n", 
    "Yes.\n",
        
    //neutral responses
    "Reply hazy, try again.\n", 
    "Ask again later.\n",
    "Better not tell you now.\n",
    "Cannot predict now.\n",
    "Concentrate and ask again.\n", 
        
    //negative responses
    "Don't bet on it.\n",
    "My reply is no.\n", 
    "My sources say no.\n", 
    "Outlook not so good.\n",
    "Very doubtful.\n"
  };
  
  //select entry from array at random
  
  //figure out maximum index:
  int high = sizeof(responses)/sizeof(responses[0]) - 1; 
  
  int low = 0; //min index to responses array
   
  //seed our random number generator with a different starting
  //point each time we run the code
  srand(time(0));
   
  //select random entry in array
  int rnd = rand() % (high - low + 1) + low;

  //format selected random response into buff
  strcpy(buff, "A: ");
  strcat(buff, responses[rnd]);
}
```

Now change the server's response to be a random Magic 8-ball reply instead of just the date/time.

1. Comment out the region in `main` which gets the time/date and formats it as a string.
2. Comment out the region which uses `strcat` and `strcpy` to concatenate the original request with the time/date.
3. Add a call to the function:
```
getFortune(response);
```

Also, let's change our client code to make it more evident what the user should do.  Replace the generic "Request: " prompt with:
```
      //prompt the user
      printf("Ask the magical, mysterious 8-ball a question, o' puny human:\nQ: ");

```

Recompile your server and client, run the server, run the client, and try out a question on the client.

Awesome!  But we can only ask one question!  And we have to restart the server each time!  Turns out, we have a lot of questions at this point in the semester.  Seems like we should be able to ask the Magic 8-Ball many questions.  

## All the Answers!
Let's add an infinite loop so that we can ask multiple questions.  

*Geez, you spend all this time learning **NOT** to write infinite loops and now your professors **WANT** you to use infinite loops. #irony*

Modify your client so that an infinite loop surrounds the following block of code:

```
    memset(question, 0, sizeof(question));
    memset(recvline, 0, sizeof(recvline));
      
    //prompt the user
    printf("Request: ");

    fgets(question, sizeof(question), stdin); /*stdin = 0 , for standard input */
    question[strcspn(question, "\n")] = 0; //replace newline just for readability
       
    write(socket_fd, question, strlen(question)+1);
    read(socket_fd,recvline,100);
    printf("%s",recvline);
```

Recompile the client, start the server, start the client, and ask as many questions as you want:

```
Ask the magical, mysterious 8-ball a question, o' puny human:
Q: Will I pass my CMS33 final?
A: Cannot predict now.

Ask the magical, mysterious 8-ball a question, o' puny human:
Q: Is Dr. Summet awesome?
A: Yes, definitely.
```

## On a Serious Note
It's worth noting that this code isn't particularly safe.  In the interest of readability, I've omitted many of the checks you would need to include when writing code that was going to be used anywhere outside of a learning exercise in lab.

For example, you should check just about any call to any socket function and make sure it succeeded.  I should have used code like:

```
if (bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) { 
  perror("ERROR on binding");
  exit(1);
}
```
and (structured slightly differently)
```
send_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
if (send_fd < 0) {
  perror("ERROR on accept");
  exit(1);
}
```

Checking for errors is extremely important in network programming when a multitude of things (many of them outside your control!) can go wrong.







