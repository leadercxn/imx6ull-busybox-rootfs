# 应用层APP传递到底层的协议


## 协议
* 控制协议总模型
    | 子命令个数 | 子命令1 | 子命令2 | 子命令3 | ... |
    |    1B    |   nB   |   nB   |   nB   | ... |

    * 子命令单元
    | cmd  | 该子命令附带长度 data_len  | data  |
    |  1B  |           1B            |   nB  |

### 字符设备 && 设备树led（没走数据协议）
* 控制协议
    |   led_sw  |
    |     1B    |

### 定时器实验
* cmd 类型
    ```
        typedef enum
        {
            CMD_START ,
            CMD_STOP ,
            CMD_MODIFY,
        } cmd_e ;
    ```





















