# picoHTTP
A pico-sized not-fully-featured HTTP server written in C++11. This program will run a server accepting TCP socket connections on port 80 from any IP address and return a static HTML response.

## Usage
First, clone the project: 

`$ git clone https://github.com/seanpianka/picoHTTP.git`

Then, compile the binary:

`$ make`

Afterwards, run the server:

`$ ./bin/pico-http`

And connect to the server address using your favorite web browser:

http://127.0.0.1:8000

Where the following webpage will be output:

`<html><body><p>It works!</p></body></html>`
