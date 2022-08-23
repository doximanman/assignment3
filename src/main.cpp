#include "CLI.hpp"
#include "StandardIO.hpp"

int main(int argc, char *argv[]) {
    StandardIO sio{};
    CLI cli(sio);
    cli.start();
}
