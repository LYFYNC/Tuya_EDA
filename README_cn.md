# 桌面温湿度天气时钟

[[English]](README.md)

[TOC]



# 介绍

### 1.简述

硬件方案：主控采用W601芯片，温湿度采集使用SHT30，联网模块使用涂鸦智能的WBR3蓝牙WiFi模组<br>可获取网络时间和天气数据,单按键触摸芯片使用TTP233D，采用2.4寸显示屏，驱动为ST7789V

软件方案：使用RTThread操作系统，图形界面使用LVGL

### 2.功能

显示屏显示从涂鸦模组获取的实时时间和天气预报

显示屏显示SHT30获取的室内温湿度

支持涂鸦客户端查看当前室内温湿度，电量等参数

### 3.涂鸦模组

使用涂鸦模组可以快速开发一款产品，只需在涂鸦IoT平台创建一款产品，按照操作步骤完成产品的功能<br>和APP界面设计，本产品采用涂鸦标准模组MCU SDK开发，使用涂鸦SDK能轻易的对接涂鸦的智能模组<br>完成产品的功能，涂鸦提供丰富的对接文档和工具帮助缩短开发周期

### 4.文档

此项目后期会有连载文章一步一步教大家如何开发

###  链接

立创EDA[PCB工程][https://oshwhub.com/xiaobaigou/tuya-eda]

在W601上使用RTThread操作系统请参考正点原子的[W601 IoT开发板][http://www.openedv.com/docs/boards/iot/zdyz_w601.html]

移植和使用LVGL请参考正点原子[littleVGL在线学习和资料][http://www.openedv.com/forum.php?mod=viewthread&tid=311917&extra=page%3D1%26filter%3Ddigest%26digest%3D1]

[涂鸦智能][https://www.tuya.com/cn]

[littleVGL][https://littlevgl.cn/]

