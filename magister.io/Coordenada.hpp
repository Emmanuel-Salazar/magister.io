#ifndef COORDENADA_HPP_
#define COORDENADA_HPP_

class Coordenada {
private:
    int x;
    int y;
public:
    Coordenada();
    Coordenada(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    ~Coordenada();
};

#endif