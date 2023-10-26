#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>


#define IP "127.0.0.1"
#define MY_ERROR 1
#define PORT 7777
#define MAX_SERVER_MSG_LEN 20000

int main()
{
    WSADATA wsa;
    SOCKET mySocket;
    struct sockaddr_in server;
    int sockAddrInLength = sizeof(struct sockaddr_in);
    char serverMessage[MAX_SERVER_MSG_LEN];
    int serverMessageLength;

    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        fprintf(stderr, "WSAStartup failed.\n");
        getchar();
        return MY_ERROR;
    }
    printf("WSASucceeded.\n");

    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

     //char* message = "A";
/*
     char* message = "A network socket is a software structure within a network node of a computer network that serves "
              "as an endpoint for sending and receiving data across the network. The structure and properties of "
              "a socket are defined by an application programming interface (API) for the networking architecture. "
              "Sockets are created only during the lifetime of a process of an application running in the node. "
              "Because of the standardization of the TCP/IP protocols in the development of the Internet, the term "
              "network socket is most commonly used in the context of the Internet protocol suite, and is therefore "
              "often also referred to as Internet socket. In this context, a socket is externally identified to other "
              "hosts by its socket address, which is the triad of transport protocol, IP address, and port number. "
              "The term socket is also used for the software endpoint of node-internal inter-process communication (IPC), "
              "which often uses the same API as a network socket. The use of the term socket in software is analogous "
              "to the function of an electrical female connector, a device in hardware for communication between nodes "
              "interconnected with an electrical cable. Similarly, the term port is used for external physical endpoints "
              "at a node or device. An application can communicate with a remote process by exchanging data with TCP/IP by "
              "knowing the combination of protocol type, IP address, and port number. This combination is often known as a "
              "socket address. It is the network-facing access handle to the network socket. The remote process establishes "
              "a network socket in its own instance of the protocol stack and uses the networking API to connect to the application, "
              "presenting its own socket address for use by the application. A protocol stack, usually provided by the operating system "
              "(rather than as a separate library, for instance), is a set of services that allow processes to communicate over a network "
              "using the protocols that the stack implements. The operating system forwards the payload of incoming IP packets to the "
              "corresponding application by extracting the socket address information from the IP and transport protocol headers and "
              "stripping the headers from the application data. The application programming interface (API) that programs use to "
              "communicate with the protocol stack, using network sockets, is called a socket API. Development of application "
              "programs that utilize this API is called socket programming or network programming. Internet socket APIs are "
              "usually based on the Berkeley sockets standard. In the Berkeley sockets standard, sockets are a form of file "
              "descriptor, due to the Unix philosophy that everything is a file, and the analogies between sockets and files. "
              "Both have functions to read, write, open, and close. In practice, the differences strain the analogy, and "
              "different interfaces (send and receive) are used on a socket. In inter-process communication, each end "
              "generally has its own socket. In the standard Internet protocols TCP and UDP, a socket address is the "
              "combination of an IP address and a port number, much like one end of a telephone connection is the "
              "combination of a phone number and a particular extension. Sockets need not have a source address, "
              "for example, for only sending data, but if a program binds a socket to a source address, the socket "
              "can be used to receive data sent to that address. Based on this address, Internet sockets deliver ";
*/

    char* message = "A network socket is a software structure within a network node of a computer network that serves "
              "as an endpoint for sending and receiving data across the network. The structure and properties of "
              "a socket are defined by an application programming interface (API) for the networking architecture. "
              "Sockets are created only during the lifetime of a process of an application running in the node. "
              "Because of the standardization of the TCP/IP protocols in the development of the Internet, the term "
              "network socket is most commonly used in the context of the Internet protocol suite, and is therefore "
              "often also referred to as Internet socket. In this context, a socket is externally identified to other "
              "hosts by its socket address, which is the triad of transport protocol, IP address, and port number. "
              "The term socket is also used for the software endpoint of node-internal inter-process communication (IPC), "
              "which often uses the same API as a network socket. The use of the term socket in software is analogous "
              "to the function of an electrical female connector, a device in hardware for communication between nodes "
              "interconnected with an electrical cable. Similarly, the term port is used for external physical endpoints "
              "at a node or device. An application can communicate with a remote process by exchanging data with TCP/IP by "
              "knowing the combination of protocol type, IP address, and port number. This combination is often known as a "
              "socket address. It is the network-facing access handle to the network socket. The remote process establishes "
              "a network socket in its own instance of the protocol stack and uses the networking API to connect to the application, "
              "presenting its own socket address for use by the application. A protocol stack, usually provided by the operating system "
              "(rather than as a separate library, for instance), is a set of services that allow processes to communicate over a network "
              "using the protocols that the stack implements. The operating system forwards the payload of incoming IP packets to the "
              "corresponding application by extracting the socket address information from the IP and transport protocol headers and "
              "stripping the headers from the application data. The application programming interface (API) that programs use to "
              "communicate with the protocol stack, using network sockets, is called a socket API. Development of application "
              "programs that utilize this API is called socket programming or network programming. Internet socket APIs are "
              "usually based on the Berkeley sockets standard. In the Berkeley sockets standard, sockets are a form of file "
              "descriptor, due to the Unix philosophy that everything is a file, and the analogies between sockets and files. "
              "Both have functions to read, write, open, and close. In practice, the differences strain the analogy, and "
              "different interfaces (send and receive) are used on a socket. In inter-process communication, each end "
              "generally has its own socket. In the standard Internet protocols TCP and UDP, a socket address is the "
              "combination of an IP address and a port number, much like one end of a telephone connection is the "
              "combination of a phone number and a particular extension. Sockets need not have a source address, "
              "for example, for only sending data, but if a program binds a socket to a source address, the socket "
              "can be used to receive data sent to that address. Based on this address, Internet sockets deliver "
              "incoming data packets to the appropriate application process."
              "A network socket is a software structure within a network node of a computer network that serves "
              "as an endpoint for sending and receiving data across the network. The structure and properties of "
              "a socket are defined by an application programming interface (API) for the networking architecture. "
              "Sockets are created only during the lifetime of a process of an application running in the node. "
              "Because of the standardization of the TCP/IP protocols in the development of the Internet, the term "
              "network socket is most commonly used in the context of the Internet protocol suite, and is therefore "
              "often also referred to as Internet socket. In this context, a socket is externally identified to other "
              "hosts by its socket address, which is the triad of transport protocol, IP address, and port number. "
              "The term socket is also used for the software endpoint of node-internal inter-process communication (IPC), "
              "which often uses the same API as a network socket. The use of the term socket in software is analogous "
              "to the function of an electrical female connector, a device in hardware for communication between nodes "
              "interconnected with an electrical cable. Similarly, the term port is used for external physical endpoints "
              "at a node or device. An application can communicate with a remote process by exchanging data with TCP/IP by "
              "knowing the combination of protocol type, IP address, and port number. This combination is often known as a "
              "socket address. It is the network-facing access handle to the network socket. The remote process establishes "
              "a network socket in its own instance of the protocol stack and uses the networking API to connect to the application, "
              "presenting its own socket address for use by the application. A protocol stack, usually provided by the operating system "
              "(rather than as a separate library, for instance), is a set of services that allow processes to communicate over a network "
              "using the protocols that the stack implements. The operating system forwards the payload of incoming IP packets to the "
              "corresponding application by extracting the socket address information from the IP and transport protocol headers and "
              "stripping the headers from the application data. The application programming interface (API) that programs use to "
              "communicate with the protocol stack, using network sockets, is called a socket API. Development of application "
              "programs that utilize this API is called socket programming or network programming. Internet socket APIs are "
              "usually based on the Berkeley sockets standard. In the Berkeley sockets standard, sockets are a form of file "
              "descriptor, due to the Unix philosophy that everything is a file, and the analogies between sockets and files. "
              "Both have functions to read, write, open, and close. In practice, the differences strain the analogy, and "
              "different interfaces (send and receive) are used on a socket. In inter-process communication, each end "
              "generally has its own socket. In the standard Internet protocols TCP and UDP, a socket address is the "
              "combination of an IP address and a port number, much like one end of a telephone connection is the "
              "combination of a phone number and a particular extension. Sockets need not have a source address, "
              "for example, for only sending data, but if a program binds a socket to a source address, the socket "
              "can be used to receive data sent to that address. Based on this address, Internet sockets deliver "
              "incoming data packets to the appropriate application process."
              "A network socket is a software structure within a network node of a computer network that serves "
              "as an endpoint for sending and receiving data across the network. The structure and properties of "
              "a socket are defined by an application programming interface (API) for the networking architecture. "
              "Sockets are created only during the lifetime of a process of an application running in the node. "
              "Because of the standardization of the TCP/IP protocols in the development of the Internet, the term "
              "network socket is most commonly used in the context of the Internet protocol suite, and is therefore "
              "often also referred to as Internet socket. In this context, a socket is externally identified to other "
              "hosts by its socket address, which is the triad of transport protocol, IP address, and port number. "
              "The term socket is also used for the software endpoint of node-internal inter-process communication (IPC), "
              "which often uses the same API as a network socket. The use of the term socket in software is analogous "
              "to the function of an electrical female connector, a device in hardware for communication between nodes "
              "interconnected with an electrical cable. Similarly, the term port is used for external physical endpoints "
              "at a node or device. An application can communicate with a remote process by exchanging data with TCP/IP by "
              "knowing the combination of protocol type, IP address, and port number. This combination is often known as a "
              "socket address. It is the network-facing access handle to the network socket. The remote process establishes "
              "a network socket in its own instance of the protocol stack and uses the networking API to connect to the application, "
              "presenting its own socket address for use by the application. A protocol stack, usually provided by the operating system "
              "(rather than as a separate library, for instance), is a set of services that allow processes to communicate over a network "
              "using the protocols that the stack implements. The operating system forwards the payload of incoming IP packets to the "
              "corresponding application by extracting the socket address information from the IP and transport protocol headers and "
              "stripping the headers from the application data. The application programming interface (API) that programs use to "
              "communicate with the protocol stack, using network sockets, is called a socket API. Development of application "
              "programs that utilize this API is called socket programming or network programming. Internet socket APIs are "
              "usually based on the Berkeley sockets standard. In the Berkeley sockets standard, sockets are a form of file "
              "descriptor, due to the Unix philosophy that everything is a file, and the analogies between sockets and files. "
              "Both have functions to read, write, open, and close. In practice, the differences strain the analogy, and "
              "different interfaces (send and receive) are used on a socket. In inter-process communication, each end "
              "generally has its own socket. In the standard Internet protocols TCP and UDP, a socket address is the "
              "combination of an IP address and a port number, much like one end of a t.";



/////////////////////////////////////////////////////////////////////////////////////////////
/*
    mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (mySocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket creation failed.\n");
        getchar();
        return MY_ERROR;
    }

    for (int i=0; i<100000; i++)
    {
        int clientResult = sendto(mySocket, message, strlen(message), 0, (struct sockaddr*) &server, sizeof server);

        /*int serverReceive = recvfrom(mySocket, serverMessage, MAX_SERVER_MSG_LEN, 0, (struct sockaddr*) &server, &sockAddrInLength);
        if (serverReceive == SOCKET_ERROR)
        {
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}*/

		//printf("%s\n", serverMessage);
        //printf("%d\n", serverReceive);
        //usleep(1000);
 /*   }

    printf("Finished");
*/

/////////////////////////////////////////////////////////////////////////////////////////////

    mySocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);

    if (mySocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket creation failed.\n");
        getchar();
        return MY_ERROR;
    }

    if (connect(mySocket, (struct sockaddr*) &server, sizeof server) < 0)
    {
        fprintf(stderr, "Connection failed. error: %d\n",WSAGetLastError());
        getchar();
        return MY_ERROR;
    }
    printf("Connection established.\n");

    for (int i=0; i<100000; i++)
    {
        if (send(mySocket, message, strlen(message), 0) < 0)
        {
            fprintf(stderr, "Sending failed.\n");
            return MY_ERROR;
        }
        //printf("Sending succeeded.\n");
/*
        if ((serverMessageLength = recv(mySocket, serverMessage, sizeof serverMessage, 0)) == SOCKET_ERROR)
        {
            fprintf(stderr, "Recv failed.\n");
            return MY_ERROR;
        }
        //printf("Recv succeeded.\n");

        serverMessage[serverMessageLength] = NULL;
        //printf("Server: %s\n\n", serverMessage);*/
    }

    closesocket(mySocket);
    getchar();
    return 0;
}
