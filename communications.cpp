#include <communications.h>

extern UART_HandleTypeDef huart3;
extern FDCAN_HandleTypeDef hfdcan1;
extern ADC_HandleTypeDef hadc1;
extern SPI_HandleTypeDef hspi1;


UART::UART(UART_HandleTypeDef* handle) : huart(handle) {}


void UART:: transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout){
    HAL_UART_Transmit(huart, pData, Size, Timeout);
};

void UART:: receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) {
    HAL_UART_Receive(huart, pData, Size, Timeout);
};

void UART:: test(){
	const char* msg = "UART test message\r\n";
	transmit((const uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
};

SPI::SPI(SPI_HandleTypeDef* handle) : hspi(handle) {}

void SPI:: transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout){
    HAL_SPI_Transmit(hspi, pData, Size, Timeout);
};

void SPI:: receive(uint8_t *pData, uint16_t Size, uint32_t Timeout){
    HAL_SPI_Receive(hspi, pData, Size, Timeout);
};

void SPI:: test(){
	 uint8_t tx[] = {0xAB, 0xCD};
	 uint8_t rx[2];
	 HAL_SPI_TransmitReceive(hspi, tx, rx, 2, HAL_MAX_DELAY);
};

CAN::CAN(FDCAN_HandleTypeDef* handle) : hfdcan(handle) {}

void CAN:: transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout){
	 FDCAN_TxHeaderTypeDef header = {};
	 header.Identifier = 0x321;
	 header.IdType = FDCAN_STANDARD_ID;
	 header.TxFrameType = FDCAN_DATA_FRAME;
	 header.DataLength = FDCAN_DLC_BYTES_8;
	 header.BitRateSwitch = FDCAN_BRS_ON;
	 header.FDFormat = FDCAN_FD_CAN;
	 header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	 header.MessageMarker = 0;
	 HAL_FDCAN_AddMessageToTxBuffer(hfdcan, &header, pData, FDCAN_TX_BUFFER0);
	 HAL_FDCAN_EnableTxBufferRequest(hfdcan, FDCAN_TX_BUFFER0);
};

void CAN:: receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) {
	FDCAN_RxHeaderTypeDef rxHeader;
	HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_BUFFER0, &rxHeader, pData);
};

void CAN:: test() {
	uint8_t msg[] = {0xDE, 0xAD, 0xBE, 0xEF};
	transmit(msg, sizeof(msg), HAL_MAX_DELAY);
};


