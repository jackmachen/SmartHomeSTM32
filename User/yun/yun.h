
#ifndef __YUN_H
#define	__YUN_H

//��½���˷������е����ܼҾӰ���ϵͳ����豸
#define DEVICEID        "11706"//�豸id
#define APIKEY          "13345ad14"//�豸����APIKEY
#define INPUTID_1       "10646"//���ڸ��豸�µ��¶Ƚӿ�id���������ɡ�����Ҫ�ģ�
#define INPUTID_2       "9780"//���ڸ��豸�µ�ʪ�Ƚӿ�id����Ҫ�������������--ƽ̨���������Ϊ��ʪ�ȡ������ݽӿڣ�ģ������##############
#define INPUTID_3       "9781"//���ڸ��豸�µ�����ӿ�id����Ҫ�������������--ƽ̨���������Ϊ������״���������ݽӿڣ�ģ������##############
#define INPUTID_4       "9909"//���ڸ��豸�µĴ����ӿ�id����Ҫ�������������--ƽ̨���������Ϊ������״���������ݽӿڣ�ģ������##############
#define ALERT_1         "1643"//���ڸ��豸�µ��������������ӿ�id����Ҫ�������������--�������Ϊ������״�����ı�����
                                    //ʾ���Ƿ�����-����ѡ����������Դ����������״���������ͷ�ʽ�����ʼ�����#######






/*���͵�¼��Ϣ*/
void checkin(void);

/*�˳���¼*/
void checkout(void);

/*��鵱ǰ��¼״̬*/
void check_status(void);

/*����ָ�Ŀ�굥λ*/
void say(char *toID, char *content);

/*�ϴ�һ���ӿڵ�ʵʱ����*/
void update1(char *did, char *inputid, float value);

/*�ϴ������ӿڵ�ʵʱ����*/
void update2(char *did, char *inputid1, float value1, char *inputid2, float value2); 

/*�ϴ�����������һ���ӿڵ�ʵʱ����*/
void update_zhen(char *did, char *inputid, int value);

/*�ϴ������ӿڵ�ʵʱ����*/
void update3(char *did, char *inputid1, float value1, char *inputid2, float value2, char *inputid3, int a); 

/*�ϴ��ĸ��ӿڵ�ʵʱ����*/
void update4(char *did, char *inputid1, float value1, char *inputid2, float value2, char *inputid3, int a, char *inputid4, int b); 

/*����һ�������ӿڵı�����Ϣ*/
void alert(char *did, char *alert);

#endif
