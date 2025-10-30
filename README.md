<style>
.highlight{
  color: white;
  background: linear-gradient(90deg, #ff6b6b, #4ecdc4);
  padding: 5px;
  border-radius: 5px;
}

.mint_green{
  color: white;
  background: #adcdadf2; 
  padding: 5px;
  border-radius: 5px;
}

.red {
  color: #ff0000;
}
.green {
  color:rgb(10, 162, 10);
}
.blue {
  color:rgb(17, 0, 255);
}

.wathet {
  color:rgb(0, 132, 255);
}
</style>

---

## <font size=3>一、ADC128s102硬件使用说明</font>
<font size=2>

```bash
create_at： 2025/10/30
aliases：   1.平台：STM32F407IGT6
```


该版本使用模拟SPI的方式编写ADC128S102的底层驱动代码。从数据手册看，DOUT数据前四位是0（芯片特性）后12位是采样数据，DIN在第六个时间点开始输入的ADC2,1,0指的是上位机要求的通道地址。所有数据都是上升沿采样下降沿输出。

我们写的是主机（MCU驱动器部分）所以DIN（对于ADC来说是输入，对于MCU来说是输出）在下降沿赋值，DOUT（对于ADC来说是输出，对于MCU来说是输入）所以在上升沿采样。



![ADC128S102时序图](./images/adc128s102_pic1.png)



**ADC通道地址选择**


| 位序号（先出 MSB） | 含义       |
| ------------------ | ---------- |
| BIT7               | Don’t care |
| BIT6               | Don’t care |
| BIT5               | ADD2       |
| BIT4               | ADD1       |
| BIT3               | ADD0       |
| BIT2 … BIT0        | Don’t care |

如上表所示，ADC128S102的“有效通道地址”只占 BIT5~BIT3，其余 5 位随意。由于 ADC128S102 的“命令帧”是 16 位，数据手册里画的那 8 位只是 高字节（D15~D8），后面还有 低字节（D7~D0） 没画全，因此必须 连续送够 16 个 SCLK 上升沿 才能拿到 12 位转换结果。

![ADC128S102时序图](./images/adc128s102_pic2.png)


**电路原理图参考**

| 芯片引脚 | MCU 引脚 | 功能                    |
| -------- | -------- | ----------------------- |
| CS       | PI0      | 片选                    |
| SCLK     | PI1      | 时钟                    |
| DOUT     | PI2      | 数据输出（接 MCU MISO） |
| DIN      | PI3      | 数据输入（接 MCU MOSI） |

![ADC128S102原理图](./images/adc128s102_pic3.png)


</font>






