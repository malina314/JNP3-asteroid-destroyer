#include "Explosion.h"

#include "common/Singleton.h"
#include "MainWindow.h"

void Explosion::Draw() const  {
    Singleton<MainWindow>::getInstance().DrawExplosionPath(position, getScale());
}
