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





##### (2). QT平台软件设计

