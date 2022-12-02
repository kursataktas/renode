//
// Copyright (c) 2010-2022 Antmicro
//
// This file is licensed under the MIT License.
// Full license text is available in 'licenses/MIT.txt'.
//
#ifndef BaseBus_H
#define BaseBus_H

#include <cstdint>

class RenodeAgent;

class BaseBus
{
public:
    BaseBus() : agent(nullptr), tickCounter(0) {}
    virtual void prePosedgeTick() = 0;
    virtual void posedgeTick() = 0;
    virtual void negedgeTick() = 0;
    virtual void setClock(uint8_t value) = 0;
    virtual void setReset(uint8_t value) = 0;
    virtual void onResetAction() = 0;
    virtual void setAgent(RenodeAgent *newAgent)
    {
        agent = newAgent;
    }
    virtual void setWidth(int width)
    {
        busWidth = width;
    }
protected:
    friend class RenodeAgent;
    RenodeAgent *agent;
    int busWidth;
    uint64_t tickCounter;
    uint8_t clock_high = 1;
    uint8_t clock_low = 0;
    uint8_t reset_active = 1;
};

class BaseTargetBus : public BaseBus
{
public:
    virtual void write(int width, uint64_t addr, uint64_t value) = 0;
    virtual uint64_t read(int width, uint64_t addr) = 0;
};

class BaseInitiatorBus : public BaseBus
{
public:
    virtual void readWord(uint64_t addr, uint8_t sel) = 0;
    virtual void writeWord(uint64_t addr, uint64_t data, uint8_t sel) = 0;
    virtual void readHandler() = 0;
    virtual void writeHandler() = 0;
    virtual bool hasSpecifiedAdress() = 0;
    virtual uint64_t getSpecifiedAdress() = 0;
};
#endif
