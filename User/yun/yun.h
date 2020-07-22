
#ifndef __YUN_H
#define	__YUN_H

//登陆个人服务器中的智能家居安防系统设计设备
#define DEVICEID        "11706"//设备id
#define APIKEY          "13345ad14"//设备密码APIKEY
#define INPUTID_1       "10646"//属于该设备下的温度接口id（已添加完成。不需要改）
#define INPUTID_2       "9780"//属于该设备下的湿度接口id（需要改正这里的数字--平台上添加名称为”湿度“的数据接口，模拟量）##############
#define INPUTID_3       "9781"//属于该设备下的烟雾接口id（需要改正这里的数字--平台上添加名称为”烟雾状况“的数据接口，模拟量）##############
#define INPUTID_4       "9909"//属于该设备下的窗帘接口id（需要改正这里的数字--平台上添加名称为”窗帘状况“的数据接口，模拟量）##############
#define ALERT_1         "1643"//属于该设备下的烟雾传感器报警接口id（需要改正这里的数字--添加名称为”窗帘状况“的报警提
                                    //示。是否启用-“不选”。数据来源——”烟雾状况“。发送方式：“邮件”）#######






/*发送登录信息*/
void checkin(void);

/*退出登录*/
void checkout(void);

/*检查当前登录状态*/
void check_status(void);

/*发送指令到目标单位*/
void say(char *toID, char *content);

/*上传一个接口的实时数据*/
void update1(char *did, char *inputid, float value);

/*上传两个接口的实时数据*/
void update2(char *did, char *inputid1, float value1, char *inputid2, float value2); 

/*上传整数型数据一个接口的实时数据*/
void update_zhen(char *did, char *inputid, int value);

/*上传三个接口的实时数据*/
void update3(char *did, char *inputid1, float value1, char *inputid2, float value2, char *inputid3, int a); 

/*上传四个接口的实时数据*/
void update4(char *did, char *inputid1, float value1, char *inputid2, float value2, char *inputid3, int a, char *inputid4, int b); 

/*发送一个报警接口的报警信息*/
void alert(char *did, char *alert);

#endif
