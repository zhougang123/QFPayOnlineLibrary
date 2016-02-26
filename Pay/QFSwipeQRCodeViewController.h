//
//  QFSwipeQRCodeViewController.h
//  Demo
//
//  Created by mac on 16/2/17.
//  Copyright © 2016年 qfpay. All rights reserved.
//

#import <UIKit/UIKit.h>

void QFAlert(NSString *title, NSString *msg, NSString *buttonText, void (^cancelBlock) ());

@interface QFSwipeQRCodeViewController : UIViewController

@property (nonatomic, strong)NSString *leftTitle;

@property (nonatomic, strong)NSString *centerTitle;

@property (nonatomic, strong)UIImage  *guideImage;

@property (nonatomic, strong)UIColor  *naviBarBackgroundColor;

@property (nonatomic, copy)void (^fetchQRCodeBlock)(NSString *QRCode);

@property (nonatomic, copy)void (^fetchQRCodeFailedBlock)(NSString *errorMsg);

@end
