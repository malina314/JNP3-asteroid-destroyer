#include "Explosion.h"

#include "common/Singleton.h"
#include "MainWindow.h"

void Explosion::Draw() const  {
    float s = getScale();
    LOG("Explosion scale: %f", s);
    Singleton<MainWindow>::getInstance().DrawExplosionPath(position, s);
}
