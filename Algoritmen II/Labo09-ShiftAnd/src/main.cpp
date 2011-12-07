#include <ostream>
#include "bitpatroon.h";
#include <string>;
#include "shiftand.h";

int main(){
    uchar var[] = "een";
    Shiftand sa(var,3);

    std::queue<const uchar*> plaats;
    const uchar hooiberg[] = "een Hallo dit eeneen is test een";

    sa.zoek(plaats,hooiberg,32);
        std::cout<<plaats.size();
    return 0;
}
