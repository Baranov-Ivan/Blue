 #ifndef COLLECTIONS_H
#define COLLECTIONS_H

enum Actions
{
    LOGIN = 1,
    LOGOUT = 2,
    MOVE = 3,
    UPGRADE = 4,
    TURN = 5,
    PLAYER = 6,
    GAMES = 7,
    MAP = 10
};

enum Result
{
    OKEY = 0,
    BAD_COMMAND = 1,
    RESOURCE_NOT_FOUND = 2,
    ACCESS_DENIED = 3,
    INAPPROPRIATE_GAME_STATE = 4,
    TIMEOUT = 5,
    INTERNAL_SERVER_ERROR = 500
};

enum PostType
{
    TOWN = 1,
    MARKET = 2,
    STORAGE = 3
};

enum GameState
{
    INIT = 1,
    RUN = 2,
    FINISHED = 3
};

enum EventType
{
    TRAIN_COLLISION = 1,
    HIJACKERS_ASSAULT = 2,
    PARASITES_ASSAULT = 3,
    REFUGEES_ARRIVAL = 4,
    RESOURCE_OVERFLOW = 5,
    RESOURCE_LACK = 6,
    GAME_OVER = 100
};

enum GoodsType
{
    NO_GOODS = 0,
    PRODUCTS = 1,
    ARMOR = 2
};


#endif // COLLECTIONS_H
