# 运行报错
```text
JNI DETECTED ERROR IN APPLICATION: JNI GetMethodID called with pending exception java.lang.NoSuchMethodError: no non-static method "Lcom/example/binny/firstjin/Student;.<setAge>(I)V"
```
### 原代码
```
//2 获取类信息
    jmethodID method_init_id = e->GetMethodID(clazz, "<init>", "()V");//构造函数
    jmethodID method_set_id = e->GetMethodID(clazz, "<setAge>", "(I)V");//set方法
    jmethodID method_get_id = e->GetMethodID(clazz, "<getAge>", "()I");//get方法
```
### 修正
```
//2 获取类信息
    jmethodID method_init_id = e->GetMethodID(clazz, "<init>", "()V");//构造函数
    jmethodID method_set_id = e->GetMethodID(clazz, "setAge", "(I)V");//set方法
    jmethodID method_get_id = e->GetMethodID(clazz, "getAge", "()I");//get方法
``` 

# 什么是signature

Signature：签名，是java 与c/c++相互调用的时候，表示函数参数的描述符。
规则：
1、函数名；
2、输入参数放在()内，输出参数放在()外；
3、多个参数之间按顺序切用;分割。

Java中的原始类型及对应的signature

| Java类型 | 符号 |
| :-: | :-: |
| boolean | Z |
| byte | B |
| char | C |
| short | S |
| int | I |
| long | L |
| float | F |
| double | D |
| void | V |
| 类 |   L包路径/类名|
|数组|[|
例子：

（[Student;)LStudent;
```
Student[]method_name(Student[] s)
```
([Ljava/lang/String;)[Ljava/lang/Object
```
Object[]method_name(String[] s)
```
([I;Ljava/lang/String;[LStudent;)Ljava/lang/Object
```
Object[]method_name(int[] i,String s,Student[] stu)
```
