#include "main.h"

#include "context.h"
#include "console.h"
#include "pca9538.h"

extern I2C_HandleTypeDef hi2c1;

HAL_StatusTypeDef PCA9538_read_register(uint16_t addr, pca9538_regs_t reg, uint8_t* buf) {
	return HAL_I2C_Mem_Read(&hi2c1, addr | 1, reg, 1, buf, 1, 100);
}


HAL_StatusTypeDef PCA9538_write_register(uint16_t addr, pca9538_regs_t reg, uint8_t* buf) {
	return HAL_I2C_Mem_Write(&hi2c1, addr & 0xFFFE, reg, 1, buf, 1, 10);
}

HAL_StatusTypeDef PCA9538_read_config(uint16_t addr, uint8_t* buf) {
	HAL_StatusTypeDef ret = HAL_OK;
	uint8_t *buf_ptr = buf;
	uint8_t i;

	for( i=0; i<4; i++ ) {
		ret = PCA9538_read_register(addr, i, buf_ptr++);

		if(ret!=HAL_OK)
			return ret;
	}

	return ret;
}

HAL_StatusTypeDef PCA9538_check_default_config(uint16_t addr) {
	uint8_t buf[4];
	HAL_StatusTypeDef ret = PCA9538_read_config(addr, buf);

	if (ret != HAL_OK) {
		send_message(context_get_console(), "Can't read default config\n");
	} else if (buf[1] != 0xFF && buf[2] != 0xFF && buf[3] != 0xFF) {
		const char nul[] = { 0 };
		send_message(context_get_console(), "Non-reset config\n");
		send_messagen(context_get_console(), (char*) buf, 4);
		send_messagen(context_get_console(), nul, 1);

		ret = HAL_ERROR;
	}

	return ret;
}

HAL_StatusTypeDef PCA9538_read_inputs(uint16_t addr, uint8_t* buf) {
	return PCA9538_read_register(addr, INPUT_PORT, buf);
}
