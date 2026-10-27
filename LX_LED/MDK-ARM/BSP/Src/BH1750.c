#include "BH1750.h"

typedef struct BH1750_device
{
	char name[10];
	
	I2C_HandleTypeDef *i2c_handle;
	uint8_t address;
	
	uint8_t buffer[20];
}BH1750_device_t;

static BH1750_device_t bh1750_dev;


// 配置SCDx4的相关信息
static void BH1750_init_dev_struct(BH1750_device_t *dev, char *name, I2C_HandleTypeDef *i2c_handle)
{
	if (i2c_handle == NULL)
	{
		//printf("BH1750的i2c配置失败\r\n");
		return;
	}
	strcpy(dev->name, name);
	dev->i2c_handle = i2c_handle;
	dev->address = BH1750_ADDRESS;
}


// 对传感器写入指令
static HAL_StatusTypeDef BH1750_Write(uint8_t cmd, BH1750_device_t *dev)
{
	return HAL_I2C_Master_Transmit(dev->i2c_handle, dev->address, &cmd, 1, 100);
}

static void BH1750_init_dev(BH1750_device_t *dev)
{
	if (BH1750_Write(POWER_ON, &bh1750_dev) != HAL_OK)
	{
		//printf("BH1750上电失败\r\n");
		
		return;
	}
	if (BH1750_Write(RESET, &bh1750_dev) != HAL_OK)
	{
		//printf("BH1750复位失败\r\n");
		
		return;
	}
	if (BH1750_Write(CONTINUOUSLY_H_RESOLUTION_MODE, &bh1750_dev) != HAL_OK)
	{
		//printf("BH1750发送采集指令失败");
		
		return;
	}
}

// 读取传感器数据
static HAL_StatusTypeDef BH1750_Read(BH1750_device_t *dev, uint8_t size)
{
	return HAL_I2C_Master_Receive(dev->i2c_handle, dev->address, dev->buffer, size, 100);
}

int get_lx(void)
{
	if (BH1750_Read(&bh1750_dev, 2) != HAL_OK)
	{
		//printf("BH1750读取数据失败\r\n");
		
		return -1;
	}
	int data = 0;
	data = ((bh1750_dev.buffer[0] << 8) + bh1750_dev.buffer[1]) / 1.2;
	
	return data;
}

// SCDx4初始化
void BH1750_INIT(void)
{
	BH1750_init_dev_struct(&bh1750_dev, "BH1750", &hi2c3);
	BH1750_init_dev(&bh1750_dev);
}