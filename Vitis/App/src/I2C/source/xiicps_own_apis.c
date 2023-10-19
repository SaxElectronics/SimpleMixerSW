
#include <xiicps_driver.h>


void I2C_ClearHoldBit(u32 BaseAddr)
{
    u32 currentRegValue = XIicPs_ReadReg(BaseAddr, (u32)XIICPS_CR_OFFSET);
    u32 newValue = currentRegValue & (~(u32)XIICPS_CR_HOLD_MASK);
    XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET, newValue);
}
