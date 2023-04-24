**求个START**

## 一. 硬件设计

**主控** : STM32G431CBT6

**稳压芯片**: AMS1117-3.3

**升压芯片**: MT3608(5V升压12V,最大电流支持2A)

**电流采样芯片**: INV199A1DCKR(两相)

**电机驱动芯片**: DRV8313

采用type-c接口供电以及进行usb通讯，2.54弯针接口进行ST-Link下载程序，另外提供了一个PH2.0-3接口(本人用来驱动ws2812)，采用两层板设计。

<img src="https://gitee.com/whpUp/4008_FOC_HID/raw/master/4.Image/pcb%E6%8F%8F%E8%BF%B0%E5%9B%BE-%E6%AD%A3%E9%9D%A2.png" alt="pcb描述图-反面" style="zoom: 33%;" />

<img src="https://gitee.com/whpUp/4008_FOC_HID/raw/master/4.Image/pcb%E6%8F%8F%E8%BF%B0%E5%9B%BE-%E5%8F%8D%E9%9D%A2.png" alt="pcb描述图-正面" style="zoom:33%;" />

<img src="https://gitee.com/whpUp/4008_FOC_HID/raw/master/4.Image/%E6%95%B4%E4%BD%93%E5%9B%BE.jpg" alt="整体图" style="zoom: 25%;" />

## 二. 软件设计

##### (1).STM32平台软件设计

###### 1. AS5600参数校准

通过IIC接口读取0x0F和0x0E两个寄存器，可以得到电机的机械角度，此时电机的零角度与AS5600读出的零角度可能不对应，需要进行校准。

将电机旋转到你预想0°的位置，设置foc角度为0°，可以将Uq设置大一点，然后上电，可以看到电机有个微小的偏移，此时读出AS5600的角度值X1，作为**机械角度零偏值**。然后将foc角度设置为90°，上电，再次读出AS5600的角度值X2，那么就可以确定电机的**极对数** = (360 / ((X2 -X1)*4))。电角度和机械角度的转换关系就可以确定下来了。



##### (2). QT平台软件设计

