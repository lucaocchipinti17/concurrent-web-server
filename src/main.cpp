#include "Socket.h"

// Acceptor thread: 1 thread running this loop
void acceptor_loop(Socket& sock, RingBuffer<int>& ring) {
    while (true) {
        int clientfd = sock.accept_client();
        if (clientfd < 0) continue;

        // Block if buffer is full (or drop/close fd based on your policy)
        ring.push(clientfd);
    }
}

// Worker threads: N threads running this loop
void worker_loop(RingBuffer<int>& ring) {
    while (true) {
        int clientfd = ring.pop();   // blocks until work available

        char buffer[1024];
        ssize_t n = recv(clientfd, buffer, sizeof(buffer) - 1, 0);
        if (n > 0) {
            buffer[n] = '\0';        // null-terminate before any string ops
            send(clientfd, buffer, n, 0);
        }
        close(clientfd);
    }
}


int main() {
    Socket sock(8080);
    RingBuffer<int> ring(100); // buffer size of 100

    std::thread acceptor_thread(acceptor_loop, std::ref(sock), std::ref(ring));

    const int num_workers = 4; // or based on hardware concurrency
    std::vector<std::thread> worker_threads;
    for (int i = 0; i < num_workers; ++i) {
        worker_threads.emplace_back(worker_loop, std::ref(ring));
    }

    acceptor_thread.join();
    for (auto& t : worker_threads) {
        t.join();
    }

    return 0;
}
