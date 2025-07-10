#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H
#include "main.h"
#include <cstring>

class CommInterface {
public:
	virtual void transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout) = 0;
	virtual void receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) = 0;
	virtual void test() = 0;
	virtual ~CommInterface() = default;

};

class UART : public CommInterface{
public:
	UART(UART_HandleTypeDef* huart);
	void transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout) override;
	void receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) override;
	void test() override;
private:
	UART_HandleTypeDef* huart;
};

class SPI : public CommInterface{
public:
	SPI(SPI_HandleTypeDef* handle);
	void transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout) override;
	void receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) override;
	void test() override;

private:
	SPI_HandleTypeDef* hspi;
};

class CAN : public CommInterface{
public:
    CAN(FDCAN_HandleTypeDef* handle);
    void transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout) override;
    void receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) override;
    void test() override;

private:
    FDCAN_HandleTypeDef* hfdcan;

};



#endif
