
#include <stdlib.h>

#include <lib/debug.hpp>

#include <app/transmit/integrity.hpp>

int main()
{
    debug::initialize();
    Integrity integrity;

    const char* splitPart1 = "<je> mange une= ,belle ";

    integrity.update(splitPart1);

    const char* splitPart2 = "pomme avec un yaourt.";

    integrity.update(splitPart2);

    char result[9];
    ultoa(integrity.get(), result, 16);

    debug::send(result);
    debug::send("\n");
    debug::send(strcmp(result, "e6b3b7dc") == 0 ? "PASSED" : "FAILED");
    debug::send("\n");
}
