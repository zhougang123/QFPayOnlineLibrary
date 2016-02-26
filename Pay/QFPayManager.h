//
//  QFPayManager.h
//  Demo
//
//  Created by mac on 16/2/19.
//  Copyright © 2016年 qfpay. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "QFSwipeQRCodeViewController.h"

#import "FixNilBug.h"

#pragma mark - 用户信息

@interface QFUserInfo : NSObject

@property (nonatomic, copy) NSString *userID;           //用户系统编号
@property (nonatomic, copy) NSString *loginAccount;      //登录的手机号
@property (nonatomic, copy) NSString *loginPassword;    //登录的密码
@property (nonatomic, copy) NSString *merchantName;     //商户的名字
@property (nonatomic, copy) NSString *groupID;          //商户的渠道id，感觉就是业务员的标示id
@property (nonatomic, copy) NSString *userCurrentState; //账号当前状态
@property (nonatomic, copy) NSString *operatorID;       //操作员id
@property (nonatomic, copy) NSArray  *allOperatorID;    //所有操作员的id
@property (nonatomic, copy) NSString *auditState;       //审核状态
@property (nonatomic, copy) NSString *joinedDate;       //商户加入的日期
//商户绑定收款银行卡的信息
@property (nonatomic, copy) NSString *branchBankCode;   //支行编码
@property (nonatomic, copy) NSString *bankCardNO;           //银行卡号
@property (nonatomic, copy) NSString *bankCardUserName;     //开户人姓名

@end




#pragma mark - 订单信息

@interface QFTradeLastestInfo : NSObject
@property (nonatomic, copy) NSString *serverTime;
@property (nonatomic, copy) NSString *todayStatAllAmount;
@property (nonatomic, copy) NSString *todayStatCount;

@end
typedef NS_ENUM(NSInteger, QFPayOrderResultType)
{
    QFPayOrderResultTypeSuccess, //支付成功
    QFPayOrderResultTypeFailed,  //支付失败
    QFPayOrderResultTypeWaitingPay, //等待支付结果
    QFPayOrderResultTypeRefundSuccess,//退款成功
    QFPayOrderResultTypeRefundFailed,//退款失败
    QFPayOrderResultTypePrecreateOrderFail,//预下单失败
    QFPayOrderResultTypeCloseSuccess,
    QFPayOrderResultTypeCloseFailed,
    QFPayOrderResultTypePreAuthSuccess//预授权已完成
    
};


@interface QFOrderInfo : NSObject

@property (nonatomic, copy  ) NSString             *busicd;//业务代码
@property (nonatomic, copy  ) NSString             *cardexpire;
@property (nonatomic, copy  ) NSString             *channelID;//渠道id
@property (nonatomic, copy  ) NSString             *cancelState;//撤销状态

@property (nonatomic, copy  ) NSString             *clientSN;//客户端流水号
@property (nonatomic, copy  ) NSString             *respMsg;//返回消息
@property (nonatomic, copy  ) NSString             *payAmount;//金额
@property (nonatomic, copy  ) NSString             *userStateID;//账号状态
@property (nonatomic, copy  ) NSString             *userID;//userID
@property (nonatomic, copy  ) NSString             *systemSN;//系统流水号
@property (nonatomic, copy  ) NSString             *currentCurrency;//当前币种
@property (nonatomic, copy  ) NSString             *clientTime;//客户端交易时间
@property (nonatomic, copy  ) NSString             *systemTime;//系统交易时间
@property (nonatomic, copy  ) NSString             *timeStamp;//时间戳
@property (nonatomic, copy  ) NSString             *mechantName;//商户名字

//note
@property (nonatomic, copy  ) NSString             *noteOpenID;
@property (nonatomic, copy  ) NSString             *noteBankType;
@property (nonatomic, copy  ) NSString             *noteIsSubscribe;
@property (nonatomic, copy  ) NSString             *notePayTime;
@property (nonatomic, copy  ) NSString             *notePrepayID;
@property (nonatomic, copy  ) NSString             *noteSubIsSubscribe;
@property (nonatomic, copy  ) NSString             *noteSubOpenID;
@property (nonatomic, copy  ) NSString             *noteTradeType;
@property (nonatomic, copy  ) NSString             *noteTransactionID;

@property (nonatomic, copy  ) NSString             *QRCodeURL;//

@property (nonatomic, copy  ) UIImage              *QRCodeImage;

@property (nonatomic, assign) QFPayOrderResultType orderResultType;//订单状态
@end


typedef NS_ENUM(NSInteger, APIEnvironmentType){
    APIEnvironmentTypeLandRelease,     //大陆线上 默认
    APIEnvironmentTypeOverseaRelease,  //海外线上
    APIEnvironmentTypeOffline          //成都线下
};

typedef NS_ENUM(NSInteger, QFPayManagerStatus){
    QFPayManagerStatusCollectFuncationNormal,//收款功能正常使用
    QFPayManagerStatusCollectFuncationError, //收款功能不能正常使用
    QFPayManagerStatusLoginRequired          //需要重新登录
};


@interface QFPayManager : NSObject

@property (nonatomic, assign) APIEnvironmentType apiEnvironmentType;//配置api请求的服务器

@property (nonatomic, assign) QFPayManagerStatus payManagerStatus;  //调用支付以前请先检查工作状态

+ (instancetype)shared;

/***
 ***QFPayManager初始化, 调用之前请先配置api请求的服务器， 在程序启动的时候调用
 ***/

- (void)payManagerInit;




/***
 ***主账号登录，登录一次，只要不退出登录、出现网络异常或删除app的情况，在app重新启动、激活都可以无需调用登录接口
 ***@account 手机号
 ***@pwd     密码
 ***return   userInfo用户信息
 ***/
- (void)payManagerLoginWithAccount:(NSString *)account
                          password:(NSString *)pwd
                           success:(void (^)(QFUserInfo *userInfo))successBlock
                            failed:(void(^)(NSString *errorMsg))failedBlock;
/***
 ***操作员账号登录
 ***@account 手机号
 ***@operatorID  操作员编号  为4位如：0005
 ***@pwd     密码
 ***return   userInfo用户信息
 ***/
- (void)payManagerLoginWithMaserAccount:(NSString *)account
                             operatorID:(NSString *)operatorID
                               password:(NSString *)pwd
                                success:(void (^)(QFUserInfo *userInfo))successBlock
                                 failed:(void (^)(NSString *errorMsg))failedBlock;

/***
 ***退出登录
 ***会清除掉缓存的所有登录账号相关的数据
 ***/
- (void)payManagerLogout;


/***
 ***获取二维码
 ***@swipeVC， QFSwipeQRCodeViewController 扫描二维码，这个页面可以定制颜色和title，详见相关属性设置
 ***@QRCode  扫描成功返回二维码
 ***/
- (void)fetchQRCodeWithController:(QFSwipeQRCodeViewController *)swipeVC
                         complete:(void (^)(NSString *QRCode)) completeBlock
                      failedBlock:(void (^)(NSString *errorMsg))failedBlock;

#pragma mark - 微信支付
/***
 ***微信刷卡支付
 ***@amount 收款的金额
 ***@qrQRCode 扫描获取到的二维码
 ***/
- (void)WXPaySiwpeWithAmount:(NSString *)amount
                      QRCode:(NSString *)qrQRCode
                     success:(void (^)(QFOrderInfo *orderIno))successBlock
                     waiting:(void (^)(QFOrderInfo *orderIno))waitingBlock
                      failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;


/***
 ***微信刷卡支付
 ***@amount 收款的金额
 ***@swipeVC 二维码扫描界面，可以定制
 ***/
- (void)WXPaySiwpeWithAmount:(NSString *)amount
             swipeController:(QFSwipeQRCodeViewController *)swipeVC
                     success:(void (^)(QFOrderInfo *orderIno))successBlock
                     waiting:(void (^)(QFOrderInfo *orderIno))waitingBlock
                      failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;


/***
 ***微信正扫,将金额提交到服务器预下单, 等待支付结果，若果没有支付需要关闭订单
 ***@amount 收款金额
 ***/
- (void)WXPayPrecreateOrderWithAmount:(NSString *)amount
                   createOrderSuccess:(void (^)(QFOrderInfo *orderIno))createSuccessBlock
                       collectSuccess:(void (^)(QFOrderInfo *orderIno))collectSuccessBlock
                              waiting:(void (^)(QFOrderInfo *orderIno))waitingBlock
                               failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;

/***
 ***微信退款,需要验证密码
 ***@orderInfo 传预下单返回的订单信息 QFOrderInfo
 ***/
- (void)WXPayCloseOrderWithOrderInfo:(QFOrderInfo *)orderInfo
                             success:(void (^)(QFOrderInfo *orderIno))successBlock
                              failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;
/***
 ***微信退款,需要验证密码
 ***@password 密码验证
 ***@orderInfo 传流水调用返回的订单信息 QFOrderInfo
 ***/

- (void)WXPayRefundWithAuthPassword:(NSString *)password
                          orderInfo:(QFOrderInfo *)orderInfo
                            success:(void (^)(QFOrderInfo *orderIno))successBlock
                             failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;



#pragma mark - 支付宝
/***
 ***支付宝支付
 ***/

/***
 ***支付宝刷卡支付
 ***@amount 收款的金额
 ***@qrQRCode 扫描获取到的二维码
 ***/
- (void)AliPayWihtAmount:(NSString *)amount
                  QRCode:(NSString *)qrQRCode
                 success:(void (^)(QFOrderInfo *orderIno))successBlock
                 waiting:(void (^)(QFOrderInfo *orderIno))waitingBlock
                  failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;

/***
 ***支付宝刷卡收款
 ***@amount 收款的金额
 ***@swipeVC 二维码扫描界面，可以定制
 ***/
- (void)AliPayWihtAmount:(NSString *)amount
         swipeController:(QFSwipeQRCodeViewController *)swipeVC
                 success:(void (^)(QFOrderInfo *orderIno))successBlock
                 waiting:(void (^)(QFOrderInfo *orderIno))waitingBlock
                  failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;


/***
 ***支付宝正扫 预下单
 ***@amount 收款的金额
 ***createSuccessBlock 预下单成功的回调
 ***collectSuccessBlock 收款成功的回调
 ***waitingBlock   轮询的回调
 ***/
- (void)AliPayPrecreateOrderWithAmount:(NSString *)amount
                    createOrderSuccess:(void (^)(QFOrderInfo *orderIno))createSuccessBlock
                        collectSuccess:(void (^)(QFOrderInfo *orderIno))collectSuccessBlock
                               waiting:(void (^)(QFOrderInfo *orderIno))waitingBlock
                                failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;


/***
 ***支付宝退款,需要验证密码
 ***@orderInfo 传预下单返回的订单信息 QFOrderInfo
 ***/
- (void)AlipayRefundWithAuthPassword:(NSString *)password
                           orderInfo:(QFOrderInfo *)orderInfo
                             success:(void (^)(QFOrderInfo *orderIno))successBlock
                              failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;


/***
 ***支付宝关闭订单
 ***@orderInfo 传预下单返回的订单信息 QFOrderInfo
 ***/
- (void)AliPayCloseOrderWithOrderInfo:(QFOrderInfo *)orderInfo
                              success:(void (^)(QFOrderInfo *orderIno))successBlock
                               failed:(void (^)(QFOrderInfo *orderIno, NSString *errorMsg))failedBlock;


/***
 ***获取订单列表
 ***/
- (void)qfTradeListWithPageNumber:(NSInteger )pageNumber
                  startDateString:(NSString *)startDateStr
                    endDateString:(NSString *)endDateStr
                          success:(void (^)(NSArray *allDateArray, NSDictionary *tradeOrdersDict, QFTradeLastestInfo *tradeLastestInfo))successBlock
                           failed:(void (^)(NSString *errorMsg))failedBlock;


@end



