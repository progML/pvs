#include "main.h"

#ifndef PCA9538_H_
#define PCA9538_H_

#define DIP_RD_ADDR 0xE1
#define DIP_WR_ADDR 0xE0

typedef enum{
	INPUT_PORT = 0x00, //Read byte XXXX XXXX
	OUTPUT_PORT = 0x01, //Read/write byte 1111 1111
	POLARITY_INVERSION = 0x02, //Read/write byte 0000 0000
	CONFIG = 0x03 //Read/write byte 1111 1111
}pca9538_regs_t;

typedef enum{
	LOW = 0,
	HIGH = 1
}what_bytes_t;

HAL_StatusTypeDef PCA9538_read_register(uint16_t addr, pca9538_regs_t reg, uint8_t* buf);
HAL_StatusTypeDef PCA9538_write_register(uint16_t addr, pca9538_regs_t reg, uint8_t* buf);
HAL_StatusTypeDef PCA9538_read_config(uint16_t addr, uint8_t* buf);
HAL_StatusTypeDef PCA9538_check_default_config(uint16_t addr);
HAL_StatusTypeDef PCA9538_read_inputs(uint16_t addr, uint8_t* buf);

#endif /* PCA9538_H_ */
