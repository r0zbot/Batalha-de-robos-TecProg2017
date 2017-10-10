#ifndef VIRTUALMACHINE_ENTITY_H
#define VIRTUALMACHINE_ENTITY_H

class Entity {
    private:
        int id;
        int posX, posY;
    public:
        Entity(int id, int posX, int posY);

        int get_id() const;
        int get_posX() const;
        int get_posY() const;
        int set_posX(int x);
        int set_posY(int y);
        virtual void update()=0;
};

#endif
