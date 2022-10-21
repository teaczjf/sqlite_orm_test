/**
 * @file sqlorm_xpro_define.h
 * @brief
 * @author 钟建福 (983851264@qq.com)
 * @version 1.0
 * @date 2022-03-14
 * 基于sqlite_orm
 * 定义与协议相关的表项的结构体
 * @copyright Copyright (c) 2022  杭州领克信息科技有限公司
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2022-03-14 <td>1.0     <td>钟建福     <td>内容
 * </table>
 */
#include <string>

/**
 * @brief SQLORM_XPRO_DEVINFO
 * AA项目_BBB设备信息总表
 */
struct SQLORM_XPRO_DEVINFO
{
    int ID = 0;
    std::string DEV_NAME;           //设备名：AA_BBB:AA项目_BBB设备
    std::string DEV_CMD_TABLE_NAME; // AA项目_BBB设备指令总表的名字
    std::string COMUNITATE_MODE;    //通讯方式 TCP_SERVER、TCP_CLIENT、UDP_SERVE、UDPMC 。。。(后面还可以扩展串口)
    std::string TCP_IP;             // TCP IP地址
    std::string TCP_PORT;           // TCP 端口号
    std::string UDP_IP_SRC;         // UDP本地IP
    std::string UDP_PORT_SRC;       // UDP本地端口号
    std::string UDP_IP_DST;         // UDP目标IP地址
    std::string UDP_PORT_DST;       // UDP目标端口号
    std::string UDPMC_IP;           // UDP组播 绑定的网卡ip
    std::string UDPMC_IP_TX;        // UDP组播 用于发送的IP组播地址
    std::string UDPMC_PORT_TX;      // UDP组播 用于发送的IP组播端口号
    std::string UDPMC_IP_RX;        // UDP组播 用于接收的IP组播地址
    std::string UDPMC_PORT_RX;      // UDP组播 用于接收的IP组播端口号
};