#include "health.h"

Health::Health() {
    health=100;
}
void Health::decrease(){
    health--;

}

int Health::getHealth(){
    return health;
}
