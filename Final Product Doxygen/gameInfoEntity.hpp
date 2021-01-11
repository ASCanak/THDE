/// This file contains Doxygen lines
/// \brief
/// gamInfoEntity class 
/// \details
/// This class saves data into a struct
#ifndef GAMEINFOENTITY_HPP
#define GAMEINFOENTITY_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

struct info{unsigned int plrID; unsigned int data;};

class gameInfoEntity{

private:
    int time;
    info player;
    rtos::pool <int> currentinfoPool;

public:
    gameInfoEntity();

    /// \brief
    /// Sets the player ID
    /// \details
    /// Puts player ID into a pool and then reads player ID from a pool and saves it into a struct
    void set_plrID(unsigned int plrID);

    /// \brief
    /// Sets weaponpower
    /// \details
    /// Puts weaponpower into a pool and then reads weaponpower from a pool and saves it into a struct
    void set_wpnPwr(unsigned int wpnPwr);

    /// \brief
    /// Sets gametime
    /// \details
    /// Puts gametime into a pool and then reads gametime from a pool and saves it into a struct
    void set_gameTime(unsigned int gameTime);

    /// \brief
    /// Sends data to a different class
    /// \details
    /// Returns player ID from a struct
    unsigned int get_plrID();

    /// \brief
    /// Sends data to a different class
    /// \details
    /// Returns weaponpower from a struct
    unsigned int get_wpnPwr();

    /// \brief
    /// Sends data to a different class
    /// \details
    /// Returns gametime from a struct
    unsigned int get_gameTime();
};

#endif 
