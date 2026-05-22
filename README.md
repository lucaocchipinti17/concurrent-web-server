# concurrent-web-server
a concurrent web server in c++
start with HTTP requests, circular ring buffer, one listener, multiple consumers
## measure
reqwuests/sec, p50/95/99 latency, queue wait time, DB/write latency, rejected requests under load

## backpressure
block producer, drop request, HTTP 503, bounded queue size

## thread pool
DB/logging workers, use logging threads
### compare performance with different worker count

## memory allocation
reuse request objects, buffer pool, preallocated ring buffer slots, unneccesary string copies

## db connection pool
fixed size pool, timeout if unavailable, measure DB bottleneck separately